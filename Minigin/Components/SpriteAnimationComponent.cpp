//
// Created by omen on 23/04/2026.
//

#include "SpriteAnimationComponent.h"

#include "Renderer.h"
#include "../GameObject.h"
#include "Managers/ResourceManager.h"


dae::SpriteAnimationComponent::SpriteAnimationComponent(GameObject *owner, int rows , int columns, const std::string& TextureFile)
    : Component(owner) , m_rows(rows), m_cols(columns), m_Texture(nullptr)
{
    m_Texture = ResourceManager::GetInstance().LoadTexture(TextureFile);
}

dae::SpriteAnimationComponent::~SpriteAnimationComponent()
{

}

void dae::SpriteAnimationComponent::Render() const
{
    if (m_Texture != nullptr)
        return;

    const auto& pos {GetOwner()->GetWorldPosition()};
    Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);

}

std::type_index dae::SpriteAnimationComponent::GetType() const
{
    return typeid(SpriteAnimationComponent);
}




