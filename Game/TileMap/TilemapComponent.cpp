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
    auto players = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByTag(static_cast<int>(GameTag::Player));

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
    const float division{16.f};
    const auto& scale = GetOwner()->GetTransform().GetScale();
    m_TileWidth  = (m_texture->GetSize().x / division) * scale.x;
    m_TileHeight = m_texture->GetSize().y * scale.y;

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
            auto tile = Utils::CreateTile(worldX, worldY, m_TileWidth, m_TileHeight );

            int index = y * m_WidthTiles + x;

            if (value == 0)
            {
                m_TileData[index] = {x, y, true, tile.get()};
                tile->GetComponent<DigDug::BlockBehaviour>()->ChangeState(std::make_unique<BlockDestroyedState>());

            }
            else
            {
                m_TileData[index] = {x, y, false, tile.get()};
            }


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








int DigDug::TilemapComponent::BitmaskToFrame(int mask)
{
    switch (mask)
    {
        case 0:  return 13;
        case 1:  return 6;  // left only       -> EdgeRight
        case 2:  return 5;  // right only      -> EdgeLeft
        case 3:  return 1;  // left + right    -> horizontal
        case 4:  return 7;  // up only         -> EdgeBottom
        case 5:  return 9;  // left + up       -> CornerLeftUp
        case 6:  return 10; // right + up      -> CornerRightUp
        case 7:  return 3;  // left+right+up   -> TTop
        case 8:  return 8;  // down only       -> EdgeTop
        case 9:  return 12; // left + down     -> CornerLeftDown
        case 10: return 11; // right + down    -> CornerRightDown
        case 11: return 4;  // left+right+down -> TBottom
        case 12: return 2;  // up + down       -> vertical
        case 13: return 9;  // left+up+down    -> TLeft  (reuse or add frame)
        case 14: return 10; // right+up+down   -> TRight (reuse or add frame)
        case 15: return 13; // all open        -> Empty/cross
        default: return 13;
    }
}

uint8_t DigDug::TilemapComponent::GetRawValue(int x, int y) const
{
    if (x < 0 || x >= m_WidthTiles || y < 0 || y >= m_HeightTiles)
        return 0;

    int index = y * m_WidthTiles + x;
    if (m_TileData[index].isDestroyed)
        return 0;

    return m_RawTiles[y * m_WidthTiles + x];;
}

int DigDug::TilemapComponent::GetBitmask(int x, int y)
{
    int mask = 0;
    if (GetRawValue(x - 1, y) == 0) mask |= 1;  // left
    if (GetRawValue(x + 1, y) == 0) mask |= 2;  // right
    if (GetRawValue(x, y - 1) == 0) mask |= 4;  // up
    if (GetRawValue(x, y + 1) == 0) mask |= 8;  // down
    return mask;
}

void DigDug::TilemapComponent::OnTileFound(uint8_t value, int x, int y)
{
    m_RawTiles[y * m_WidthTiles + x] = value;
}

void DigDug::TilemapComponent::CheckNeighbours(int x, int y)
{
    int neighbours[4][2] = {
        {x - 1, y},
        {x + 1, y},
        {x, y - 1},
        {x, y + 1}
    };

    for (auto& neighbour : neighbours)
    {
        int nx = neighbour[0];
        int ny = neighbour[1];

        if (nx < 0 || nx >= m_WidthTiles || ny < 0 || ny >= m_HeightTiles) continue;

        int neighbourIndex = ny * m_WidthTiles + nx;
        if (m_TileData[neighbourIndex].isDestroyed) continue;

        if (auto spriteComp = m_TileData[neighbourIndex].ptr->GetComponent<dae::SpriteAnimationComponent>())
        {
            int frame = BitmaskToFrame(GetBitmask(nx, ny));
            float frameWidth  = m_texture->GetSize().x / 16.f;
            float frameHeight = m_texture->GetSize().y;
            spriteComp->SetAnimation({{ frame * frameWidth, 0, frameWidth, frameHeight }}, 0.f, false);
        }
    }

}


