//
// Created by omen on 05/05/2026.
//

#include "Utils.h"

#include "Components/RenderComponent.h"
#include "Components/SpriteAnimationComponent.h"


std::unique_ptr<dae::GameObject> Utils::CreateAnimatedSpriteObject(const std::string &TexturePath, int rows, int cols)
{
    auto obj = std::make_unique<dae::GameObject>();

    auto renderComp = std::make_unique<dae::RenderComponent>(obj.get());
    renderComp->SetTextureFilePath(TexturePath);

    obj->AddComponent(std::move(renderComp));

    obj->AddComponent(std::make_unique<dae::SpriteAnimationComponent>( obj.get(), rows , cols ));




    return obj;
}

