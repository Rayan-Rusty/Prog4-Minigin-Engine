//
// Created by omen on 31/05/2026.
//

#include "EnemySpawnerComponent.h"

#include <memory>

#include "GameObject.h"
#include "PookaBehaviour.h"
#include "Scene.h"
#include "Utils.h"

DigDug::EnemySpawnerComponent::EnemySpawnerComponent(dae::GameObject *pOwner, dae::Scene* scene)
    : BaseTilemapLoader(pOwner) , m_pScene(scene)
{

}

DigDug::EnemySpawnerComponent::~EnemySpawnerComponent()
{

}

void DigDug::EnemySpawnerComponent::OnAllTilesLoaded()
{
    constexpr  float tileSize = 16.f;
    constexpr  float scale = 2.f;

    for (const auto& pos : m_positions)
    {
        auto enemy = Utils::CreateAnimatedSpriteObject("Sprites/PookaSprites.png", 6, 7);
        enemy->GetTransform().SetWorldPosition(glm::vec3{
            pos.x * tileSize * scale ,
            pos.y * tileSize * scale,
            0
        });
        enemy->GetTransform().SetScale(glm::vec3{scale, scale, scale});

        auto pookaAI = std::make_unique<PookaBehaviour>(enemy.get());
        enemy->AddComponent(std::move(pookaAI));

        m_pScene->Add(std::move(enemy));

    }
}

void DigDug::EnemySpawnerComponent::OnMapSizeKnown(int , int   )
{
    m_positions.clear();
}

void DigDug::EnemySpawnerComponent::OnTileFound(uint8_t value, int x, int y)
{
    if (value == 1)
        m_positions.emplace_back(x, y);

}
