//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_TILEMAPCOMPONENT_H
#define MINIGIN_TILEMAPCOMPONENT_H
#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "BaseTilemapLoader.h"
#include "Component.h"
#include "IObserver.h"

#include "Texture2D.h"

namespace dae {
    class GameObject;

}

namespace DigDug
{


    struct TileData
    {
        int gridX;
        int gridY;
        bool isDestroyed;
        dae::GameObject* ptr{nullptr};
    };


    class TilemapComponent : public BaseTilemapLoader,  public dae::IObserver
    {
    public:

        TilemapComponent(dae::GameObject* pOwner);
        ~TilemapComponent() override;

        void Notify(Event event, dae::GameActor *actor) override;

        glm::vec3 GridToWorld(const glm::ivec2& gridPos) const;
        glm::ivec2 WorldToGrid(const glm::vec3& worldPos) const;
        bool isTileOpen(int x, int y) const;
        float GetTileWidth()  const { return m_TileWidth; }
        float GetTileHeight() const { return m_TileHeight; }
        int GetWidthTiles()  const { return m_WidthTiles; }
        int GetHeightTiles() const { return m_HeightTiles; }

        void OnAllTilesLoaded() override;
        void AddTexture(const std::string& path);

        void Update(float deltaTime) override;



        std::type_index GetType() const override { return typeid(TilemapComponent); }


        void OnMapSizeKnown(int width, int height) override;


        int GetLayerForWorldPos(const glm::vec3& worldPos) const;
        uint8_t GetRawValue(int x , int y)const ;

        void Clear();
    private:



        void OnTileFound(uint8_t value, int x, int y) override;


        std::vector<uint8_t> m_Tiles;

        std::shared_ptr<dae::Texture2D> m_texture;

        std::vector<uint8_t>m_RawTiles;

        std::vector<TileData> m_TileData;

        float m_TileWidth{0.f};
        float m_TileHeight{0.f};
        std::vector<glm::vec3> m_pendingDestructions;

    };
}

#endif //MINIGIN_TILEMAPCOMPONENT_H