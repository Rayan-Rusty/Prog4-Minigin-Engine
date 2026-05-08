//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_TILEMAPCOMPONENT_H
#define MINIGIN_TILEMAPCOMPONENT_H
#include <string>

#include "Component.h"

namespace game
{
    class TilemapComponent : public dae::Component
    {
    public:

        enum class TileType
        {
            Dirt,
            Empty,
            Rock
        };

        void LoadFromFile(const std::string& path);
        void Clear();

        TileType GetTile(int x, int y) const;
        void SetTile(int x, int y, TileType type);
        bool IsBlocked(int x, int y) const;

    private:
        int m_Width{};
        int m_Height{};
        float m_TileSize{16.f};
    };
}

#endif //MINIGIN_TILEMAPCOMPONENT_H