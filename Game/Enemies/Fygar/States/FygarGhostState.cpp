//
// Created by omen on 08/05/2026.
//

#include "FygarGhostState.h"

#include "FygarBehaviour.h"
#include "FygarNormalState.h"

#include "SceneManager.h"
#include "GameObject.h"
#include "SpriteAnimationComponent.h"
#include "Layers/GameLayers.h"
#include "TilemapComponent.h"


void DigDug::FygarGhostState::Enter(FygarBehaviour &Data)
{
    m_timer = 0;
    auto* obj = Data.GetOwner();

    auto playerObjs = dae::SceneManager::GetInstance().GetActiveScene()
                  ->GetObjectByTag(static_cast<int>(GameTag::Player));
    if (!playerObjs.empty())
        m_pPlayer = playerObjs[0];

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    {
        std::vector<SDL_FRect> ghostFrames =
        {
            {96, 0, 16, 16},
            {112 , 0 , 16, 16}
        };

        spriteComp->SetAnimation( ghostFrames, 0.2f , true);
    }

}

std::unique_ptr<State<DigDug::FygarBehaviour>> DigDug::FygarGhostState::Update(float DeltaTime , FygarBehaviour &Data)
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
            return std::make_unique<FygarNormalState>();
    }

    return nullptr;

}


void DigDug::FygarGhostState::Exit(FygarBehaviour &) {

}

std::type_index DigDug::FygarGhostState::GetType() const
{
    return std::type_index(typeid(FygarGhostState));
}
