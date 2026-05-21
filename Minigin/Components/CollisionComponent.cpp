//
// Created by omen on 15/05/2026.
//

#include "CollisionComponent.h"

#include "../GameObject/GameObject.h"
#include "../Rendering/Renderer.h"
#include "Utils.h"

dae::CollisionComponent::CollisionComponent(GameObject* owner)
    : Component(owner)
{

}

dae::CollisionComponent::~CollisionComponent()
{
}

void dae::CollisionComponent::Update(float)
{

}

void dae::CollisionComponent::Render() const
{


#ifdef _DEBUG
    if (m_Enabled)
    {
        SDL_FRect bounds = GetBounds();

    }
#endif


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
