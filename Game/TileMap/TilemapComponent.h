//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_TILEMAPCOMPONENT_H
#define MINIGIN_TILEMAPCOMPONENT_H
#include <memory>
#include <string>
#include <vector>

#include "Component.h"
#include "Texture2D.h"

namespace dae {
    class GameObject;
}

namespace DigDug
{
    class TilemapComponent : public dae::Component
    {
    public:


        TilemapComponent(dae::GameObject* pOwner);
        ~TilemapComponent() = default;

        void AddTexture(const std::string& path);

        void LoadFromFile(const std::string& path);
        void Render() const override;
        void Clear();
        std::type_index GetType() const override { return typeid(TilemapComponent); }
        // TileType GetTile(int x, int y) const;
        // void SetTile(int x, int y, TileType type);
        // bool IsBlocked(int x, int y) const;
        enum class TileType
        {
            Dirt = 0,
            Dug = 1
        };

        struct Tile
        {
       		int x , y;
            TileType  state;
            std::vector<std::shared_ptr<dae::Texture2D>> texture;
        };

    private:


        void RebuildRenderData();

        std::vector<uint8_t> m_Tiles;
        std::vector<Tile> m_RenderTiles;
        std::shared_ptr<dae::Texture2D> m_texture;
        int m_Width{0};
        int m_Height{0};

        float m_TileWidth{0.f};
        float m_TileHeight{0.f};
    };
}

#endif //MINIGIN_TILEMAPCOMPONENT_H