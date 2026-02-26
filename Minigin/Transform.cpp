#include "Transform.h"
#include "GameObject.h"

dae::Transform::Transform(GameObject *owner)
	: Component(owner)
{

}


void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_localPosition = pos;
	GetOwner()->SetPositionDirty();
}

const glm::vec3& dae::Transform::GetLocalPosition() const
{
	return m_localPosition;
}

const glm::vec3& dae::Transform::GetWorldPosition()
{

	return m_worldPosition;
}

void dae::Transform::SetWorldPosition(const glm::vec3& pos)
{
	m_worldPosition = pos;
}


std::type_index dae::Transform::GetType() const {
	return std::type_index(typeid(Transform));
}
