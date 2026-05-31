//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_TILEMAPCOMPONENT_H
#define MINIGIN_TILEMAPCOMPONENT_H
#include <memory>
#include <string>
#include <vector>

#include "BaseTilemapLoader.h"
#include "Component.h"
#include "Texture2D.h"

namespace dae {
    class GameObject;

}

namespace DigDug
{
    class TilemapComponent : public BaseTilemapLoader
    {
    public:


        TilemapComponent(dae::GameObject* pOwner);
        ~TilemapComponent() = default;



        void OnAllTilesLoaded() override;
        void AddTexture(const std::string& path);
        void Render() const override;
        void Clear();
        std::type_index GetType() const override { return typeid(TilemapComponent); }


        void OnMapSizeKnown(int width, int height) override;

        enum class TileType : uint8_t {
            Empty = 0,
            Block = 1,

        };
        enum class TileOrientation : uint8_t
        {
            Horizontal = 0,
            Vertical = 1,
            Middle = 2,
            MiddleUpside = 3,
            EdgeLeft = 4,
            EdgeRight = 5,
            EdgeTop = 6,
            EdgeBottom = 7
        };
        struct Tile
        {
       		int x{0};
            int y{0};
            bool isDestroyed{false};

            TileOrientation orientation{TileOrientation::Horizontal};
            TileType type{TileType::Block};
            int frameIndex{0};
        };



        TileOrientation DetermineOrientation(int x, int y);
        uint8_t GetRawValue(int x , int y);


    private:

        void OnTileFound(uint8_t value, int x, int y) override;


        std::vector<uint8_t> m_Tiles;
        std::vector<Tile> m_RenderTiles;
        std::shared_ptr<dae::Texture2D> m_texture;

        std::vector<uint8_t>m_RawTiles;

        float m_TileWidth{0.f};
        float m_TileHeight{0.f};
    };
}

#endif //MINIGIN_TILEMAPCOMPONENT_H