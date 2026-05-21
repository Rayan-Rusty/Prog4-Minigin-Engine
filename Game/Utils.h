//
// Created by omen on 05/05/2026.
//

#ifndef MINIGIN_UTILS_H
#define MINIGIN_UTILS_H


#include "../Minigin/GameObject/GameObject.h"


namespace Utils
{
    std::unique_ptr<dae::GameObject> CreateAnimatedSpriteObject( const std::string& TexturePath , int rows , int cols);
    std::unique_ptr<dae::GameObject> CreatePlayerCharacter( const std::string& TexturePath , int rows , int cols);
    std::unique_ptr<dae::GameObject> CreateTextObject( const std::string& TexturePath);
    std::unique_ptr<dae::GameObject> CreateBackgroundObject(const std::string& TexturePath);
    std::unique_ptr<dae::GameObject> CreateUIElement(const std::string& TexturePath);

    //void DebugObject();
}


#endif //MINIGIN_UTILS_H