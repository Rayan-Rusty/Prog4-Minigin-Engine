//
// Created by omen on 05/05/2026.
//

#ifndef MINIGIN_UTILS_H
#define MINIGIN_UTILS_H


#include "GameObject.h"
#include "TilemapComponent.h"


namespace Utils
{
    std::unique_ptr<dae::GameObject> CreateAnimatedSpriteObject( const std::string& TexturePath , int rows , int cols , int layer = 0 , int tag = 0);
    std::unique_ptr<dae::GameObject> CreatePlayerCharacter( const std::string& TexturePath , int rows , int cols);
    std::unique_ptr<dae::GameObject> CreateTextObject( const std::string& TexturePath);
    std::unique_ptr<dae::GameObject> CreateBackgroundObject(const std::string& TexturePath);
    std::unique_ptr<dae::GameObject> CreateUIElement(const std::string& TexturePath);
    std::unique_ptr<dae::GameObject> CreateFygar();
    std::unique_ptr<dae::GameObject> CreatePooka();
    std::unique_ptr<dae::GameObject> CreatePlayer();

    std::unique_ptr<dae::GameObject> CreateEnemy(const std::string& TexturePath, int rows, int cols);
    std::unique_ptr<dae::GameObject> CreateTilemap(const std::string& texturePath, const std::string& dataPath);

    std::unique_ptr<dae::GameObject> CreateTile(float worldX, float worldY, float w, float h);
    std::unique_ptr<dae::GameObject> CreateMenuMarker();


    bool IsIntersection(DigDug::TilemapComponent* tilemap, glm::ivec2 currentGrid, glm::vec2 currentDir);
    glm::vec2 PickBestDirection(DigDug::TilemapComponent* tilemap , dae::GameObject* player, glm::ivec2 fromGrid, glm::vec2 currentDir);
    //void DebugObject();
}


#endif //MINIGIN_UTILS_H