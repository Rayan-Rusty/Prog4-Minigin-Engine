#include <string>
#include "GameObject.h"


#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for (auto& component : m_components)
		component->Update(deltaTime);

	for (auto& child : m_Children)
		child->Update(deltaTime);
}

void dae::GameObject::Render() const
{
	for (auto& component : m_components)
		component->Render();


}

bool dae::GameObject::GetShouldDelete()
{
	return m_ShouldDelete;
}



void dae::GameObject::SetDeletion(bool value)
{
	m_ShouldDelete = value;
}




void dae::GameObject::SetPositionDirty() {
	m_positionIsDirty  = true;
	for (auto& child : m_Children)
	{
		child->SetPositionDirty();
	}
}

const glm::vec3& dae::GameObject::GetWorldPosition() {
	if (m_positionIsDirty) {
		UpdateWorldPosition();
	}
	return m_Transform.GetWorldPosition();
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_positionIsDirty) {

		if(!m_parent) {
			m_Transform.SetWorldPosition( m_Transform.GetLocalPosition());
		}
		else {
			m_Transform.SetWorldPosition( m_parent->GetWorldPosition() + m_Transform.GetLocalPosition());
		}

	}
	m_positionIsDirty = false;
}


void dae::GameObject::SetParent(GameObject* parent , bool keepWorldPosition)
{
	if(IsChild(parent) || parent == this || m_parent == parent)
		return;
	if (!parent)
	{
		m_Transform.SetLocalPosition(m_Transform.GetWorldPosition());

	}
	else
	{
		if (keepWorldPosition)
			m_Transform.SetLocalPosition(m_Transform.GetWorldPosition() - parent->m_Transform.GetWorldPosition());
		SetPositionDirty();
	}
	if(m_parent)
		m_parent->RemoveChild(this);

	m_parent = parent;
	m_parent->AddChild(this);
}

const std::vector<dae::GameObject*>& dae::GameObject::GetChildren()
{
	return m_Children;
}
bool dae::GameObject::IsChild(GameObject* parent)
{
	if (parent == nullptr)
		return false;

	for (auto* child : m_Children)
	{
		if (child == parent)
			return true;
	}

	return false;

}

//############################
//		private functions - added commentary form the powerpoint to make sure each step is easy to understand
//############################
void dae::GameObject::AddChild(GameObject* child)
{
	m_Children.push_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{

	auto iteration = std::find(m_Children.begin(), m_Children.end(), child);
	m_Children.erase(iteration);

}


