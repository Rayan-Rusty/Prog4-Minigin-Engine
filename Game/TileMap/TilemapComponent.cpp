//
// Created by omen on 08/05/2026.
//

#include "TilemapComponent.h"

#include <iostream>
#include <SDL3/SDL.h>

#include "CollisionComponent.h"
#include "IObserver.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Layers/GameLayers.h"

#include "SpriteAnimationComponent.h"
#include "Utils.h"
#include "Blocks/BlockBehaviour.h"
#include "Blocks/States/BlockDestroyedState.h"

DigDug::TilemapComponent::TilemapComponent(dae::GameObject* pOwner)
    :BaseTilemapLoader(pOwner)
{
}

DigDug::TilemapComponent::~TilemapComponent()
{

}

void DigDug::TilemapComponent::Notify(Event event, dae::GameActor *actor)
{
    if (event == dae::IObserver::Event::TileDestroyed && actor->GetOwner()->GetTag() == static_cast<int>(GameTag::Tilemap))
        {


        auto grid = WorldToGrid(actor->GetOwner()->GetTransform().GetWorldPosition());
        if (grid.x < 0 || grid.x >= m_WidthTiles) return;
        if (grid.y < 0 || grid.y >= m_HeightTiles) return;

        int index = grid.y * m_WidthTiles + grid.x;
        m_TileData[index].isDestroyed = true;
        m_RawTiles[index] = 0;
    };


}

glm::vec3 DigDug::TilemapComponent::GridToWorld(const glm::ivec2 &gridPos) const
{
    glm::vec3 tilemapPos = GetOwner()->GetTransform().GetWorldPosition();
    return {
        tilemapPos.x + gridPos.x * m_TileWidth,
        tilemapPos.y + gridPos.y * m_TileHeight,
        0.f
    };
}

glm::ivec2 DigDug::TilemapComponent::WorldToGrid(const glm::vec3 &worldPos) const
{
    glm::vec3 tilemapPos = GetOwner()->GetTransform().GetWorldPosition();
    return {
        static_cast<int>(std::floor((worldPos.x - tilemapPos.x) / m_TileWidth)),
        static_cast<int>(std::floor((worldPos.y - tilemapPos.y) / m_TileHeight))
    };
}

bool DigDug::TilemapComponent::isTileOpen(int x, int y) const
{
    return (GetRawValue(x, y) == 0);
}



int DigDug::TilemapComponent::GetLayerForWorldPos(const glm::vec3 &worldPos) const
{
    glm::vec3 tilemapPos = GetOwner()->GetTransform().GetWorldPosition();
    int gridY = static_cast<int>(std::round((worldPos.y - tilemapPos.y) / m_TileHeight));
    // divide gridY into bands, e.g. every N rows = one layer
    return gridY / 4;
}


void DigDug::TilemapComponent::OnAllTilesLoaded()
{

    const auto& scale = GetOwner()->GetTransform().GetScale();
    m_TileWidth  = (m_texture->GetSize().x / 2.f) * scale.x;
    m_TileHeight = (m_texture->GetSize().y / 4.f) * scale.y;

    const auto& tilemapPos = GetOwner()->GetTransform().GetWorldPosition();
    auto* scene = dae::SceneManager::GetInstance().GetActiveScene();

    m_TileData.resize(m_WidthTiles * m_HeightTiles);

    for (int y = 0; y < m_HeightTiles; y++)
    {
        for (int x = 0; x < m_WidthTiles; x++)
        {
            uint8_t value = m_RawTiles[y * m_WidthTiles + x];

            float worldX = tilemapPos.x + x * m_TileWidth;
            float worldY = tilemapPos.y + y * m_TileHeight;
            int layer = GetLayerForWorldPos(glm::vec3{worldX, worldY, 0});
            auto tile = Utils::CreateTile(worldX, worldY, m_TileWidth, m_TileHeight, layer);

            int index = y * m_WidthTiles + x;

            if (value == 0)
                if (auto* bb = tile->GetComponent<DigDug::BlockBehaviour>())
                    bb->ChangeState(std::make_unique<BlockDestroyedState>());;


            m_TileData[index] = {x, y, false, tile.get()};

            tile->GetActor()->AddObserver(this);

            scene->Add(std::move(tile));



        }
    }



}


void DigDug::TilemapComponent::AddTexture(const std::string &path)
{
    m_texture = dae::ResourceManager::GetInstance().LoadTexture(path) ;

}

void DigDug::TilemapComponent::Update(float ) {

}


void DigDug::TilemapComponent::OnMapSizeKnown(int width, int height)
{
    m_RawTiles.resize(width * height, 0);
}


uint8_t DigDug::TilemapComponent::GetRawValue(int x, int y) const
{
    if (x < 0 || x >= m_WidthTiles || y < 0 || y >= m_HeightTiles)
        return 0;

    int index = y * m_WidthTiles + x;
    if (m_TileData[index].isDestroyed)
        return 0;

    return m_RawTiles[y * m_WidthTiles + x];
}

void DigDug::TilemapComponent::Clear()
{


    m_Tiles.clear();
    m_RawTiles.clear();
    m_TileData.clear();
}


void DigDug::TilemapComponent::OnTileFound(uint8_t value, int x, int y)
{
    m_RawTiles[y * m_WidthTiles + x] = value;
}




