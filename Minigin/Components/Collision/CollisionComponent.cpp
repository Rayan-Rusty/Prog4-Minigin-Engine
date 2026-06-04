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

    SDL_FRect worldBounds;
    worldBounds.x = worldPos.x;
    worldBounds.y = worldPos.y;
    worldBounds.w = m_Width * scale.x;
    worldBounds.h = m_Height * scale.y;
    //
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
    m_bounds.h = height;
    m_bounds.w = width;
}


