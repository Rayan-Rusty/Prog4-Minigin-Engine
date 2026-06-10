//
// Created by omen on 15/05/2026.
//

#include "CollisionComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "Utils.h"

dae::CollisionComponent::CollisionComponent(GameObject* owner)
    : Component(owner)
{
    m_Width = 16;
    m_Height = 16;
}

dae::CollisionComponent::~CollisionComponent()
{
}

void dae::CollisionComponent::Update(float)
{

}

void dae::CollisionComponent::Render() const
{

    if (!m_Enabled) return;

    SDL_FRect b = GetBounds();

    dae::Renderer::GetInstance().RenderDebugRect(b, {255, 0, 0, 255});

}



std::type_index dae::CollisionComponent::GetType() const
{
    return typeid(dae::CollisionComponent);
}

SDL_FRect dae::CollisionComponent::GetBounds() const
{
    const auto& worldPos = GetOwner()->GetTransform().GetWorldPosition();
    const auto& scale = GetOwner()->GetTransform().GetScale();

    float scaledW = m_Width  * std::abs(scale.x);
    float scaledH = m_Height * std::abs(scale.y);

    float scaledOffsetX = m_OffsetX * std::abs(scale.x);
    float scaledOffsetY = m_OffsetY * std::abs(scale.y);

    SDL_FRect worldBounds;
    worldBounds.x = worldPos.x + scaledOffsetX;
    worldBounds.y = worldPos.y + scaledOffsetY;
    worldBounds.w = scaledW;
    worldBounds.h = scaledH;


    return worldBounds;
}


bool dae::CollisionComponent::Intersect(const CollisionComponent *other) const
{
    if (!other)
        return false;

    return CheckOverlap(this->GetBounds(), other->GetBounds());

}

void dae::CollisionComponent::SetSize(float width, float height)
{
    m_Width  = width;
    m_Height = height;
}


