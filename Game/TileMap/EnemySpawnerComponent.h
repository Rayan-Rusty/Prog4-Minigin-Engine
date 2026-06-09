//
// Created by omen on 31/05/2026.
//

#ifndef MINIGIN_ENEMYSPAWNERCOMPONENT_H
#define MINIGIN_ENEMYSPAWNERCOMPONENT_H
#include <memory>
#include <vector>

#include "BaseTilemapLoader.h"
#include "CollisionManager.h"
#include "Utils.h"
#include "glm/vec2.hpp"
#include "Scene.h"
#include "Layers/GameLayers.h"


namespace dae {
    class CollisionComponent;
}

namespace DigDug
{
    template<typename TEnemyTraits>
    class EnemySpawnerComponent final : public BaseTilemapLoader
    {
    public:



        EnemySpawnerComponent(dae::GameObject* pOwner , dae::Scene* scene)
            : BaseTilemapLoader(pOwner) , m_pScene(scene)
        {}
        ~EnemySpawnerComponent() = default;



        void OnAllTilesLoaded() override
        {
            constexpr  float tileSize = 16.f;
            constexpr  float scale = 2.f;

            for (const auto& pos : m_positions)
            {

                auto enemy = Utils::CreateAnimatedSpriteObject
                (
                    TEnemyTraits::SpritePath()
                    ,TEnemyTraits::Cols()
                    , TEnemyTraits::Rows()
                    );

                enemy->GetTransform().SetWorldPosition(glm::vec3{
                    pos.x * tileSize * scale ,
                    pos.y * tileSize * scale,
                    0
                });

                enemy->GetTransform().SetScale(glm::vec3{scale, scale, scale});

                auto enemyAI = std::make_unique<typename TEnemyTraits::Behaviour>(enemy.get());
                enemy->AddComponent(std::move(enemyAI));

                auto col = std::make_unique<dae::CollisionComponent>(enemy.get());
                enemy->AddComponent(std::move(col));
                CollisionManager::GetInstance().Register(enemy->GetComponent<dae::CollisionComponent>());

                m_pScene->Add(std::move(enemy));

            }
        };

        void OnMapSizeKnown(int , int ) override
        {
            m_positions.clear();
        }

        std::type_index GetType() const override { return typeid(EnemySpawnerComponent); }
    private:

        void OnTileFound(uint8_t value, int x, int y) override
        {
            if (value == 1)
                m_positions.emplace_back(x, y);

        }


        std::vector<glm::ivec2> m_positions;
        dae::Scene* m_pScene{nullptr};
        float m_TileSize{16.f};

    };
}



#endif //MINIGIN_ENEMYSPAWNERCOMPONENT_H