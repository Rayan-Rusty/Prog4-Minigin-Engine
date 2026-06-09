//
// Created by omen on 05/05/2026.
//

#ifndef MINIGIN_UTILS_H
#define MINIGIN_UTILS_H


#include "GameObject.h"


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
    //void DebugObject();
}


#endif //MINIGIN_UTILS_H