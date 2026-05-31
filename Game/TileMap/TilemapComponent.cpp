//
// Created by omen on 08/05/2026.
//

#include "TilemapComponent.h"

#include <iostream>
#include <SDL3/SDL.h>

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

DigDug::TilemapComponent::TilemapComponent(dae::GameObject* pOwner)
    :BaseTilemapLoader(pOwner)
{

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

    for (int y = 0; y < m_Height; y++)
    {
        for (int x = 0; x < m_Width; x++)
        {
            uint8_t value = m_RawTiles[y * m_Width + x];

            Tile tile{x, y};
            tile.isDestroyed = value == 0; // flips it
            if (!tile.isDestroyed)
            {
                tile.frameIndex = 0; // solid/filled block
            }
            else
            {
                tile.orientation = DetermineOrientation(x, y);
                switch (tile.orientation)
                {
                    case TileOrientation::Horizontal:  tile.frameIndex = 1; break;
                    case TileOrientation::Vertical:    tile.frameIndex = 2; break;
                    case TileOrientation::Middle:      tile.frameIndex = 3; break;
                    case TileOrientation::EdgeLeft:    tile.frameIndex = 5; break;
                    case TileOrientation::EdgeRight:   tile.frameIndex = 6; break;
                    case TileOrientation::EdgeBottom:  tile.frameIndex = 7; break;
                    case TileOrientation::EdgeTop:     tile.frameIndex = 8; break;

                    default:                          tile.frameIndex = 1; break;
                }
            }

            m_RenderTiles.push_back(tile);
        }
    }


    const auto& scale = GetOwner()->GetTransform().GetScale();
    m_TileWidth = m_texture->GetSize().x * scale.x;
    m_TileHeight = m_texture->GetSize().y * scale.y;
    std::cout << "Tilemap: " << m_RenderTiles.size() << " visible tiles" << std::endl;
}


void DigDug::TilemapComponent::AddTexture(const std::string &path)
{
    m_texture = dae::ResourceManager::GetInstance().LoadTexture(path) ;

}

void DigDug::TilemapComponent::Clear()
{

}

void DigDug::TilemapComponent::OnMapSizeKnown(int width, int height)
{
    m_RawTiles.resize(width * height, 0);
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
    if (x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return 0;
    return m_RawTiles[y * m_Width + x];
}

void DigDug::TilemapComponent::OnTileFound(uint8_t value, int x, int y)
{
    m_RawTiles[y * m_Width + x] = value;
}


