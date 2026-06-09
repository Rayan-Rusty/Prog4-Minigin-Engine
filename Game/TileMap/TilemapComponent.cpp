//
// Created by omen on 08/05/2026.
//

#include "TilemapComponent.h"

#include <iostream>
#include <SDL3/SDL.h>

#include "CollisionComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Layers/GameLayers.h"
#include "SceneManager.h"

DigDug::TilemapComponent::TilemapComponent(dae::GameObject* pOwner)
    :BaseTilemapLoader(pOwner)
{
    auto players = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByTag(static_cast<int>(GameTag::Player));
    for (const auto& player : players)
    {
        player->GetActor()->AddObserver(this);
    }
}

DigDug::TilemapComponent::~TilemapComponent()
{
    auto players = dae::SceneManager::GetInstance().GetActiveScene()->GetObjectByTag(static_cast<int>(GameTag::Player));
    for (const auto& player : players)
    {
        player->GetActor()->RemoveObserver(this);
    }
}

void DigDug::TilemapComponent::Notify(dae::IObserver::Event event, dae::GameActor* actor )
{
    if (event == dae::IObserver::Event::Collision)
    {
        if (actor->GetOwner()->GetTag() == static_cast<int>(DigDug::GameTag::Player))
        {
            const auto& actorPos {actor->GetOwner()->GetTransform().GetWorldPosition()};
            const auto& tilemapPos {GetOwner()->GetTransform().GetWorldPosition()};

            int gridX = static_cast<int>((actorPos.x - tilemapPos.x) / m_WidthTiles);
            int gridY = static_cast<int>((actorPos.y - tilemapPos.y) / m_HeightTiles);

            CollideAt(gridX, gridY);
        }

    }
}

void DigDug::TilemapComponent::Render() const
{
    if (!m_texture || m_RenderTiles.empty()) return;

    const auto& position = GetOwner()->GetTransform().GetWorldPosition();
    const auto& scale = GetOwner()->GetTransform().GetScale();

    float frameW = m_texture->GetSize().x / 9.f;
    float frameH = m_texture->GetSize().y;

    SDL_FRect dst{};
    dst.w = frameW * scale.x;
    dst.h = frameH * scale.y;

    for (const auto& tile : m_RenderTiles)
    {
        SDL_FRect src{};
        src.x = frameW * tile.frameIndex;
        src.w = frameW;
        src.h = frameH;
        dst.x = position.x + (tile.x * dst.w);
        dst.y = position.y + (tile.y * dst.h);
        dae::Renderer::GetInstance().RenderTexture(*m_texture, dst, src);
    }
}



void DigDug::TilemapComponent::OnAllTilesLoaded()
{

    for (int y = 0; y < m_HeightTiles; y++)
    {
        for (int x = 0; x < m_WidthTiles; x++)
        {
            uint8_t value = m_RawTiles[y * m_WidthTiles + x];

            Tile tile{x, y};
            tile.isDestroyed = value == 0; // flips it
            if (!tile.isDestroyed)
                tile.frameIndex = 0; // solid/filled block
            else
                tile.frameIndex = OrientationToFrame(DetermineOrientation(x, y));


            m_RenderTiles.push_back(tile);
        }
    }


    const auto& scale = GetOwner()->GetTransform().GetScale();
    m_TileWidth = m_texture->GetSize().x * scale.x;
    m_TileHeight = m_texture->GetSize().y * scale.y;

    auto col = GetOwner()->GetComponent<dae::CollisionComponent>();
    if (col)
    {
        std::cout << "Collision added \n";
        col->SetSize(m_WidthTiles * m_TileWidth , m_HeightTiles * m_TileHeight);

    }

}


void DigDug::TilemapComponent::AddTexture(const std::string &path)
{
    m_texture = dae::ResourceManager::GetInstance().LoadTexture(path) ;

}



void DigDug::TilemapComponent::OnMapSizeKnown(int width, int height)
{
    m_RawTiles.resize(width * height, 0);
}

void DigDug::TilemapComponent::CollideAt(int gridX, int gridY)
{
    if (gridX < 0 || gridX >= m_WidthTiles || gridY < 0 || gridY >= m_HeightTiles) return;

    int index = gridY * m_WidthTiles + gridX;
    if (m_RawTiles[index] == 0) return;

    m_RawTiles[index] = 0;
    auto& tile = m_RenderTiles[index];
    tile.isDestroyed = true;

    // reorient this tile and its neighbours
    for (auto [nx, ny] : { std::pair{gridX,gridY}, {gridX-1,gridY}, {gridX+1,gridY}, {gridX,gridY-1}, {gridX,gridY+1} })
    {
        if (nx < 0 || nx >= m_WidthTiles || ny < 0 || ny >= m_HeightTiles) continue;
        if (m_RawTiles[ny * m_WidthTiles + nx] != 0) continue;
        m_RenderTiles[ny * m_WidthTiles + nx].frameIndex = OrientationToFrame(DetermineOrientation(nx, ny));
    }

}

int DigDug::TilemapComponent::OrientationToFrame(TileOrientation orientation)
{
    switch (orientation)
    {
        case TileOrientation::Horizontal:  return 1;
        case TileOrientation::Vertical:    return 2;
        case TileOrientation::Middle:      return 3;
        case TileOrientation::EdgeLeft:    return 5;
        case TileOrientation::EdgeRight:   return 6;
        case TileOrientation::EdgeBottom:  return 7;
        case TileOrientation::EdgeTop:     return 8;
        default:                           return 1;
    }
}

DigDug::TilemapComponent::TileOrientation DigDug::TilemapComponent::DetermineOrientation(int x, int y)
{
    bool left  = GetRawValue(x - 1, y) == 0;
    bool right = GetRawValue(x + 1, y) == 0;
    bool up    = GetRawValue(x, y - 1) == 0;
    bool down  = GetRawValue(x, y + 1) == 0;

    if (left && right && up) return TileOrientation::Middle;

    if (right && !left) return TileOrientation::EdgeLeft;
    if (left && !right) return TileOrientation::EdgeRight;

    if (up && !down) return TileOrientation::EdgeBottom;
    if (down && !up) return TileOrientation::EdgeTop;


    // middle of tunnels
    if (left || right) return TileOrientation::Horizontal;
    if (up || down)    return TileOrientation::Vertical;

    return TileOrientation::Horizontal;
}

uint8_t DigDug::TilemapComponent::GetRawValue(int x, int y)
{
    if (x < 0 || x >= m_WidthTiles || y < 0 || y >= m_HeightTiles)
        return 0;
    return m_RawTiles[y * m_WidthTiles + x];
}

void DigDug::TilemapComponent::OnTileFound(uint8_t value, int x, int y)
{
    m_RawTiles[y * m_WidthTiles + x] = value;
}


