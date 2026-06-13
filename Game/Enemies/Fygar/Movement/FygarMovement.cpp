#include "FygarMovement.h"

#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "FygarGhostState.h"
#include "GameObject.h"
#include "PookaGhostState.h"
#include "SceneManager.h"
#include "SpriteAnimationComponent.h"
#include "Layers/GameLayers.h"

DigDug::FygarMovement::FygarMovement(dae::GameObject *parent)
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

        auto* FygarBehaviour = GetOwner()->GetComponent<DigDug::FygarBehaviour>();
        if (FygarBehaviour && FygarBehaviour->GetState())
        {

            bool isGhost = (FygarBehaviour->GetState()->GetType() == typeid(FygarGhostState));


            if (other->GetOwner()->GetTag() == static_cast<int>(DigDug::GameTag::Tilemap) && isGhost)
                return;


            auto tileWorldPos = other->GetOwner()->GetTransform().GetWorldPosition();
            auto tileGrid     = m_pSceneTileMap->WorldToGrid(tileWorldPos);
            ChangeDirection(tileGrid);

        }



    });
}

DigDug::FygarMovement::~FygarMovement()
{
}

void DigDug::FygarMovement::ChangeDirection(glm::ivec2 wallGrid)
{

    if (!m_pSceneTileMap) { m_Dir = -m_Dir; return; }

    glm::ivec2 enemyGrid = {
        wallGrid.x - static_cast<int>(m_Dir.x),
        wallGrid.y - static_cast<int>(m_Dir.y)
    };

    GetOwner()->GetTransform().SetWorldPosition(
        m_pSceneTileMap->GridToWorld(enemyGrid)
    );

    m_Dir        = Utils::PickBestDirection(m_pSceneTileMap, m_pPlayer, enemyGrid, m_Dir);
    m_FacingLeft = (m_Dir.x < 0);

    GetOwner()->GetActor()->NotifyObservers(dae::IObserver::Event::EnemyHitWall);
    if (auto* sprite = GetOwner()->GetComponent<dae::SpriteAnimationComponent>())
        sprite->SetFlipHorizontal(m_FacingLeft);

}

void DigDug::FygarMovement::Update(float )
{
}

std::type_index DigDug::FygarMovement::GetType() const
{
    return typeid(FygarMovement);
}

void DigDug::FygarMovement::Move(float dt)
{
    auto* transform = &GetOwner()->GetTransform();
    if (!transform) return;

    auto pos = transform->GetWorldPosition();
    pos.x += m_Speed * m_Dir.x * dt;
    pos.y += m_Speed * m_Dir.y * dt;

    glm::vec3 tilemapPos = m_pSceneTileMap->GetOwner()->GetTransform().GetWorldPosition();
    float maxX = tilemapPos.x + (m_pSceneTileMap->GetWidthTiles()  - 1) * m_pSceneTileMap->GetTileWidth();
    float maxY = tilemapPos.y + (m_pSceneTileMap->GetHeightTiles() - 1) * m_pSceneTileMap->GetTileHeight();

    pos.x = std::clamp(pos.x, tilemapPos.x, maxX);
    pos.y = std::clamp(pos.y, tilemapPos.y, maxY);

    transform->SetWorldPosition(pos);

    auto currentGrid = m_pSceneTileMap->WorldToGrid(pos);
    if (currentGrid == m_lastGrid) return;
    m_lastGrid = currentGrid;
}



void DigDug::FygarMovement::SetSpeed(float speed)
{
    m_Speed = speed;
}

void DigDug::FygarMovement::CheckWallCollision() {
}
