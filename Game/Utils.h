//
// Created by omen on 05/05/2026.
//

#ifndef MINIGIN_UTILS_H
#define MINIGIN_UTILS_H


#include "GameObject.h"


namespace Utils
{
    std::unique_ptr<dae::GameObject> CreateAnimatedSpriteObject( const std::string& TexturePath , int rows , int cols);
    std::unique_ptr<dae::GameObject> CreateTextObject( std::string& TexturePath);
    std::unique_ptr<dae::GameObject> CreateBackgroundObject(std::string& TexturePath);
    std::unique_ptr<dae::GameObject> CreateUIElement(std::string& TexturePath);

    //void DebugObject();
}


#endif //MINIGIN_UTILS_H