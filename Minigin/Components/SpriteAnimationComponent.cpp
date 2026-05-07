//
// Created by omen on 23/04/2026.
//

#include "SpriteAnimationComponent.h"

#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Managers/ResourceManager.h"


dae::SpriteAnimationComponent::SpriteAnimationComponent(GameObject *owner, int rows , int columns, const std::string& TextureFile)
    : Component(owner) , m_Texture(nullptr), m_Rows(rows), m_Cols(columns)
{
    m_Texture = ResourceManager::GetInstance().LoadTexture(TextureFile);

}

dae::SpriteAnimationComponent::~SpriteAnimationComponent()
{

}

void dae::SpriteAnimationComponent::Update(float deltaTime)
{
    m_Timer += deltaTime;

    if (m_Timer >= m_FrameTime)
    {
        m_Timer = 0.f;
        m_CurrentFrame++;

        if (m_CurrentFrame >= m_Rows * m_Cols)
            m_CurrentFrame = 0;

        auto texSize = m_Texture->GetSize();

        float frameWidth = texSize.x / m_Cols;
        float frameHeight = texSize.y / m_Rows;

        int row = m_CurrentFrame / m_Cols;
        int col = m_CurrentFrame % m_Cols;

        m_Src.x = col * frameWidth;
        m_Src.y = row * frameHeight;
        m_Src.w = frameWidth;
        m_Src.h = frameHeight;
    }
}

std::type_index dae::SpriteAnimationComponent::GetType() const
{
    return typeid(SpriteAnimationComponent);
}


const SDL_FRect &dae::SpriteAnimationComponent::GetSourceRect() const {
    return m_Src;
}
