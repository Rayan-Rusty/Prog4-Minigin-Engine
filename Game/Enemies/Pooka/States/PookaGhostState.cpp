//
// Created by omen on 06/05/2026.
//

#include "PookaGhostState.h"

#include "CollisionComponent.h"
#include "PookaBehaviour.h"
#include "SceneManager.h"
#include "SpriteAnimationComponent.h"
#include "GameLayers.h"
#include "PookaMovement.h"


void DigDug::PookaGhostState::Enter(PookaBehaviour& Data )
{
    m_timer = 0;
    auto* obj = Data.GetOwner();

    auto playerObjs = dae::SceneManager::GetInstance().GetActiveScene()
                  ->GetObjectByTag(static_cast<int>(GameTag::Player));
    if (!playerObjs.empty())
        m_pPlayer = playerObjs[0];


    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    {
        std::vector<SDL_FRect> ghostState =
        {
            {48, 0, 16, 16},
            { 64, 0, 16, 16}

        };

        spriteComp->SetAnimation( ghostState, 0.2f , true);
    }

}

std::unique_ptr<State<DigDug::PookaBehaviour>> DigDug::PookaGhostState::Update(float DeltaTime , PookaBehaviour &Data)
{

    auto pos    = Data.GetOwner()->GetTransform().GetWorldPosition();
    auto target = m_pPlayer->GetTransform().GetWorldPosition();

    glm::vec2 dir = glm::normalize(glm::vec2(target) - glm::vec2(pos));
    pos.x += m_Speed * dir.x * DeltaTime;
    pos.y += m_Speed * dir.y * DeltaTime;
    Data.GetOwner()->GetTransform().SetWorldPosition(pos);

    if (!m_pTilemap)
    {
        auto tilemapObjs = dae::SceneManager::GetInstance().GetActiveScene()
                           ->GetObjectByTag(static_cast<int>(GameTag::TilemapComponent));
        if (!tilemapObjs.empty())
            m_pTilemap = tilemapObjs[0]->GetComponent<TilemapComponent>();
    }

    if (m_pTilemap)
    {
        auto grid = m_pTilemap->WorldToGrid(pos);
        if (m_pTilemap->isTileOpen(grid.x, grid.y))
            return std::make_unique<PookaNormalState>();
    }

    return nullptr;
}


void DigDug::PookaGhostState::Exit(PookaBehaviour&   )
{
    // auto* obj = Data.GetOwner();
    // if (auto* col = obj->GetComponent<dae::CollisionComponent>())
    //     col->SetEnabled(false);

}

std::type_index DigDug::PookaGhostState::GetType() const
{
    return std::type_index(typeid(PookaGhostState));
}
