//
// Created by omen on 31/05/2026.
//

#include "BaseTilemapLoader.h"

#include <iostream>
#include <SDL3/SDL.h>

DigDug::BaseTilemapLoader::BaseTilemapLoader(dae::GameObject* pOwner)
    : Component(pOwner)
{
}
void DigDug::BaseTilemapLoader::LoadFromFile(const std::string& path)
{
    SDL_Surface* surface = SDL_LoadPNG(path.c_str());
    if (!surface) return;

    uint8_t* pixels = static_cast<uint8_t*>(surface->pixels);


    m_Height = surface->h;
    m_Width = surface->w;
    m_WidthTiles = surface->w / 16;
    m_HeightTiles = surface->h / 16;
    OnMapSizeKnown(m_WidthTiles, m_HeightTiles);

    for (int y = 0; y < m_HeightTiles; y++)
    {
        for (int x = 0; x < m_WidthTiles; x++)
        {
            int pixelIndex = (y * 16) * surface->pitch + (x * 16);
            uint8_t value = pixels[pixelIndex];
            OnTileFound(value, x, y);  // each derived class handles its own values
        }
    }

    for (int y = 0; y < m_HeightTiles; y++)
    {
        for (int x = 0; x < m_WidthTiles; x++)
        {
            int pixelIndex = (y * 16) * surface->pitch + (x * 16);
            std::cout << static_cast<int>(pixels[pixelIndex]) << " ";
        }
        std::cout << "\n";
    }

    SDL_DestroySurface(surface);
    OnAllTilesLoaded();
}

void DigDug::BaseTilemapLoader::OnMapSizeKnown(int , int ) {
}
