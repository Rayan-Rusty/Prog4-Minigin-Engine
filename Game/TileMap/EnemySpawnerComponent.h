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

            auto tilemapObjs = m_pScene->GetObjectByTag(
    static_cast<int>(DigDug::GameTag::TilemapComponent)
);

            glm::vec3 tilemapPos{0, 0, 0};
            if (!tilemapObjs.empty())
                tilemapPos = tilemapObjs[0]->GetTransform().GetWorldPosition();

            for (const auto& pos : m_positions)
            {
                auto enemy = TEnemyTraits::Create();

                enemy->GetTransform().SetWorldPosition(glm::vec3{
                    tilemapPos.x + pos.x * tileSize * scale,
                    tilemapPos.y + pos.y * tileSize * scale,
                    0.f
                });

                enemy->GetTransform().SetScale(glm::vec3{scale, scale, scale});
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