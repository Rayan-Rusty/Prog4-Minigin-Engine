//
// Created by omen on 31/05/2026.
//

#ifndef MINIGIN_BASETILEMAPLOADER_H
#define MINIGIN_BASETILEMAPLOADER_H
#include <string>
#include "Component.h"


namespace DigDug
{
    class BaseTilemapLoader : public dae::Component
    {
    public:
         explicit BaseTilemapLoader(dae::GameObject* pOwner);

        ~BaseTilemapLoader() override = default;
        void LoadFromFile(const std::string& path);

        virtual void OnMapSizeKnown(int width, int height);
       virtual void OnAllTilesLoaded() = 0;

        BaseTilemapLoader(const BaseTilemapLoader& other) = delete;
        BaseTilemapLoader(BaseTilemapLoader&& other) = delete;
        BaseTilemapLoader& operator=(const BaseTilemapLoader& other) = delete;
        BaseTilemapLoader& operator=(BaseTilemapLoader&& other) = delete;

    protected:
        int m_WidthTiles{0};
        int m_HeightTiles{0};

        int m_Width{0};
        int m_Height{0};
    private:
        virtual void OnTileFound(uint8_t value, int x, int y) = 0;

    };
}




#endif //MINIGIN_BASETILEMAPLOADER_H