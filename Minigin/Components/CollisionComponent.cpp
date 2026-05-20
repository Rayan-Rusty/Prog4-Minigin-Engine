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
        //Rect bounds = GetBounds();

    }
#endif


}


// dae::Rect dae::CollisionComponent::GetBounds() const
// {
//     const auto& worldPos = GetOwner()->GetTransform().GetWorldPosition();
//     const auto& scale = GetOwner()->GetTransform().GetScale();
//
//     Rect worldBounds;
//     worldBounds.pos.x = worldPos.x + m_Offset.x;
//     worldBounds.pos.y = worldPos.y + m_Offset.y;
//     worldBounds.size.x = m_Width * scale.x;
//     worldBounds.size.y = m_Height * scale.y;
//
//     return worldBounds;
// }

std::type_index dae::CollisionComponent::GetType() const
{
    return typeid(dae::CollisionComponent);
}


bool dae::CollisionComponent::Intersect(const CollisionComponent *other) const
{
    if (!other)
        return false;
    //return CheckOverlap(this->GetBounds(), other->GetBounds());
    return true;
}
