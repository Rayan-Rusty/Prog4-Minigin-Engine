//
// Created by omen on 08/05/2026.
//

#include "TilemapComponent.h"

#include <iostream>
#include <SDL3/SDL.h>

#include "../../Minigin/GameObject/GameObject.h"
#include "../../Minigin/Rendering/Renderer.h"
#include "../../Minigin/Textures/ResourceManager.h"

DigDug::TilemapComponent::TilemapComponent(dae::GameObject* pOwner)
    :Component(pOwner)
{

}


void DigDug::TilemapComponent::LoadFromFile(const std::string &path)
{



    SDL_Surface* surface = SDL_LoadPNG(path.c_str());
    if (!surface)
    {
        std::cout << "Failed to load PNG: " << SDL_GetError() << std::endl;
        return;
    }

    uint8_t* pixels = (uint8_t*)surface->pixels;

    m_Width = surface->w / 16;
    m_Height = surface->h / 16;

    m_Tiles.resize(m_Width * m_Height);

    int count = 0;
    for (int y = 0; y < m_Height; y ++) {
        for (int x = 0; x < m_Width; x ++) {

            int pixelX = x * 16;
            int pixelY = y * 16;

            int pixelIndex = pixelY * surface->pitch + pixelX;

            uint8_t value = pixels[pixelIndex];

            int tileIndex = y * m_Width + x;

            m_Tiles[tileIndex] = value;

            std::cout << (int)value << " ";
            count++;
        }

        std::cout << std::endl;
    }

    std::cout <<"total:" <<count<< std::endl;
    RebuildRenderData();
    SDL_DestroySurface(surface);

}

void DigDug::TilemapComponent::Render() const
{
    if (!m_texture || m_Tiles.empty()) return;

    const auto& position = GetOwner()->GetTransform().GetWorldPosition();
    const auto& scale = GetOwner()->GetTransform().GetScale();
    SDL_FRect dst{};
    SDL_FRect src{0, 0, m_texture->GetSize().x, m_texture->GetSize().y};

    dst.w = m_texture->GetSize().x * scale.x;
    dst.h = m_texture->GetSize().y * scale.y;


    for (const auto& tile : m_RenderTiles)
    {
        dst.x = position.x + (tile.x * dst.w);
        dst.y = position.y + (tile.y * dst.h);

        dae::Renderer::GetInstance().RenderTexture(*m_texture, dst, src);
    }
}


void DigDug::TilemapComponent::RebuildRenderData()
{
    for (int y = 0; y < m_Height; y++)
    {
        for (int x = 0; x < m_Width; x++)
        {
            if (m_Tiles[y * m_Width + x] == 1)
            {
                m_RenderTiles.push_back({x, y});
            }
        }
    }



    if (m_texture)
    {
        const auto& scale = GetOwner()->GetTransform().GetScale();
        m_TileWidth = m_texture->GetSize().x * scale.x;
        m_TileHeight = m_texture->GetSize().y * scale.y;
    }

    std::cout << "Tilemap: " << m_RenderTiles.size() << " visible tiles" << std::endl;

}

void DigDug::TilemapComponent::AddTexture(const std::string &path)
{


    m_texture = dae::ResourceManager::GetInstance().LoadTexture(path) ;

}

void DigDug::TilemapComponent::Clear()
{

}
