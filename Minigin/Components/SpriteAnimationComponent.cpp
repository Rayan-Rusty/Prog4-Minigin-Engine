//
// Created by omen on 23/04/2026.
//

#include "SpriteAnimationComponent.h"

#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"



dae::SpriteAnimationComponent::SpriteAnimationComponent(GameObject *owner, int  , int )
    : Component(owner)
{


}

dae::SpriteAnimationComponent::~SpriteAnimationComponent() = default;

void dae::SpriteAnimationComponent::Update(float deltaTime)
{
    auto renderComp = GetOwner()->GetComponent<RenderComponent>();
    if (!renderComp) return;


    m_Timer += deltaTime;
    if (m_CurrentAnim.spritesFrames.empty())
        return;

    if (m_Timer >= m_FrameTime)
    {
        m_Timer = 0.f;
        m_CurrentFrameIndex++;

        if (m_CurrentFrameIndex >= m_CurrentAnim.spritesFrames.size())
        {
            if (m_CurrentAnim.looping)
                m_CurrentFrameIndex  = 0;
            else
                m_CurrentFrameIndex = static_cast<int>(m_CurrentAnim.spritesFrames.size() - 1);
        }


    }



    m_Src = m_CurrentAnim.spritesFrames[m_CurrentFrameIndex].src;
}

std::type_index dae::SpriteAnimationComponent::GetType() const
{
    return typeid(SpriteAnimationComponent);
}


const SDL_FRect &dae::SpriteAnimationComponent::GetSourceRect() const {
    return m_Src;
}

void dae::SpriteAnimationComponent::SetFlipHorizontal(bool flip)
{
    m_FlipHorizontal = flip;
}

bool dae::SpriteAnimationComponent::GetFlipHorizontal()
{
    return m_FlipHorizontal;
}

void dae::SpriteAnimationComponent::SetFlipVertical(bool flip)
{
    m_FlipVertical = flip;
}

bool dae::SpriteAnimationComponent::GetFlipVertical()
{
    return m_FlipVertical;
}

void dae::SpriteAnimationComponent::SetAnimation(const std::vector<SDL_FRect>& Sizes, float duration , bool looping)
{
    m_Timer = 0.f;
    m_CurrentFrameIndex = 0;
    m_CurrentAnim.spritesFrames.clear();
    for (const SDL_FRect& source : Sizes)
    {
        m_CurrentAnim.spritesFrames.push_back({source , duration});
    }

    m_CurrentAnim.looping = looping;
}

