//
// Created by omen on 23/04/2026.
//

#include "SpriteAnimationComponent.h"

#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Managers/ResourceManager.h"


dae::SpriteAnimationComponent::SpriteAnimationComponent(GameObject *owner, int rows , int columns)
    : Component(owner) ,  m_Rows(rows), m_Cols(columns)
{


}

dae::SpriteAnimationComponent::~SpriteAnimationComponent()
{

}


void dae::SpriteAnimationComponent::SetAnimation(int row, int startCol, int endCol)
{
    m_CurrentAnim.row = row;
    m_CurrentAnim.startCol = startCol;
    m_CurrentAnim.endCol = endCol;
    m_CurrentFrame = startCol;
    m_Timer = 0.f;
}

void dae::SpriteAnimationComponent::Update(float deltaTime)
{
    auto renderComp = GetOwner()->GetComponent<RenderComponent>();
    if (!renderComp) return;


    m_Timer += deltaTime;

    if (m_Timer >= m_FrameTime)
    {
        m_Timer = 0.f;

        m_CurrentCol++;

        if (m_CurrentCol > m_CurrentAnim.endCol)
            m_CurrentCol = m_CurrentAnim.startCol;


        auto texSize = renderComp->GetTexture()->GetSize();

        float frameWidth = texSize.x / m_Cols;
        float frameHeight = texSize.y / m_Rows;

        int row = m_CurrentCol / m_Cols;
        int col = m_CurrentCol % m_Cols;

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
