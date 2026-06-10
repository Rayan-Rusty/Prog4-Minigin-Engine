#include "PookaMovement.h"

#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "SpriteAnimationComponent.h"
#include "Layers/GameLayers.h"

DigDug::PookaMovement::PookaMovement(dae::GameObject *parent)
    : Component(parent)
{

    auto tilemapObjs = dae::SceneManager::GetInstance().GetActiveScene()
                   ->GetObjectByTag(static_cast<int>(GameTag::TilemapComponent));

    if (!tilemapObjs.empty())
        m_pSceneTileMap = tilemapObjs[0]->GetComponent<TilemapComponent>();

    auto playerObjs = dae::SceneManager::GetInstance().GetActiveScene()
                      ->GetObjectByTag(static_cast<int>(GameTag::Player));
    if (!playerObjs.empty())
        m_pPlayer = playerObjs[0];

    auto* col = GetOwner()->GetComponent<dae::CollisionComponent>();
    if (!col)
        return;

    col->SetOnCollision([this](dae::CollisionComponent* other)
    {
        if (other->GetOwner()->GetTag() != static_cast<int>(DigDug::GameTag::Tilemap))
            return;

        auto tileWorldPos = other->GetOwner()->GetTransform().GetWorldPosition();
        auto tileGrid     = m_pSceneTileMap->WorldToGrid(tileWorldPos);
        ChangeDirection(tileGrid);


    });
}

DigDug::PookaMovement::~PookaMovement()
{
}

void DigDug::PookaMovement::ChangeDirection(glm::ivec2 wallGrid)
{

    if (!m_pSceneTileMap) { m_Dir = -m_Dir; return; }

    glm::ivec2 enemyGrid = {
        wallGrid.x - static_cast<int>(m_Dir.x),
        wallGrid.y - static_cast<int>(m_Dir.y)
    };

    GetOwner()->GetTransform().SetWorldPosition(
        m_pSceneTileMap->GridToWorld(enemyGrid)
    );


    auto playerGrid = m_pSceneTileMap->WorldToGrid(
        m_pPlayer->GetTransform().GetWorldPosition()
    );


    std::vector<glm::vec2> directions = {{ 1,0 }, { -1,0 }, { 0,1 }, { 0,-1 }};

    glm::vec2 bestDir = m_Dir;
    int bestDist      = INT_MAX;

    for (auto& d : directions)
    {
        int nx   = enemyGrid.x + static_cast<int>(d.x);
        int ny   = enemyGrid.y + static_cast<int>(d.y);
        bool open = m_pSceneTileMap->isTileOpen(nx, ny);
        int dist  = std::abs(nx - playerGrid.x) + std::abs(ny - playerGrid.y);
        bool isReverse = (d == -m_Dir);
        int penalized  = isReverse ? dist + 1000 : dist;


        if (!open) continue;
        if (penalized < bestDist)
        {
            bestDist = penalized;
            bestDir  = d;
        }
    }



    m_Dir        = bestDir;
    m_FacingLeft = (m_Dir.x < 0);

    if (auto* sprite = GetOwner()->GetComponent<dae::SpriteAnimationComponent>())
        sprite->SetFlipHorizontal(m_FacingLeft);
}

void DigDug::PookaMovement::Update(float deltaTime)
{
    auto* transform = &GetOwner()->GetTransform();

    if (!transform) return;

    auto pos = transform->GetWorldPosition();
    pos.x += m_Speed * m_Dir.x * deltaTime;
    pos.y += m_Speed * m_Dir.y * deltaTime;

    transform->SetWorldPosition(pos);

    auto currentGrid = m_pSceneTileMap->WorldToGrid(pos);
    if (currentGrid == m_lastGrid) return;
    m_lastGrid = currentGrid;

    // Check if the tile ahead has open neighbours besides the axis we're on
    glm::ivec2 ahead = {
        currentGrid.x + static_cast<int>(m_Dir.x),
        currentGrid.y + static_cast<int>(m_Dir.y)
    };

    // Perpendicular directions only
    std::vector<glm::vec2> perpendiculars;
    if (m_Dir.x != 0)  // moving horizontally → check up/down
        perpendiculars = {{ 0,1 }, { 0,-1 }};
    else                // moving vertically → check left/right
        perpendiculars = {{ 1,0 }, { -1,0 }};

    bool isIntersection = false;
    for (auto& p : perpendiculars)
    {
        if (m_pSceneTileMap->isTileOpen(
            currentGrid.x + static_cast<int>(p.x),
            currentGrid.y + static_cast<int>(p.y)))
        {
            isIntersection = true;
            break;
        }
    }

    if (isIntersection)
        ChangeDirection(ahead);


}

std::type_index DigDug::PookaMovement::GetType() const
{
    return typeid(PookaMovement);
}
void DigDug::PookaMovement::CheckWallCollision() {
}
