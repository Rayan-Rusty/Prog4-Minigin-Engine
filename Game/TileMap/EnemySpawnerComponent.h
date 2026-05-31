//
// Created by omen on 31/05/2026.
//

#ifndef MINIGIN_ENEMYSPAWNERCOMPONENT_H
#define MINIGIN_ENEMYSPAWNERCOMPONENT_H
#include <vector>

#include "BaseTilemapLoader.h"
#include "glm/vec2.hpp"

namespace dae {
    class Scene;
}

namespace DigDug
{
    class EnemySpawnerComponent final : public BaseTilemapLoader
    {
    public:
        EnemySpawnerComponent(dae::GameObject* pOwner , dae::Scene* scene);
        ~EnemySpawnerComponent();



        void OnAllTilesLoaded() override;
        void OnMapSizeKnown(int width, int height) override;

        std::type_index GetType() const override { return typeid(EnemySpawnerComponent); }
    private:

        void OnTileFound(uint8_t value, int x, int y) override;


        std::vector<glm::ivec2> m_positions;
        dae::Scene* m_pScene{nullptr};
        float m_TileSize{16.f};
    };
}



#endif //MINIGIN_ENEMYSPAWNERCOMPONENT_H