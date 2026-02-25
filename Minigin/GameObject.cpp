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



void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_localTransform.SetPosition(pos);
	SetPositionDirty();
}

glm::vec3 dae::GameObject::GetLocalPosition() const
{
	return m_localTransform.GetPosition();
}

glm::vec3 dae::GameObject::GetWorldPosition()
{
	if (m_PositionDirty)
		UpdateWorldPosition();
	return m_worldTransform.GetPosition();
}

void dae::GameObject::SetPositionDirty() {
	m_PositionDirty  = true;
	for (auto& child : m_Children)
	{
		child->SetPositionDirty();
	}
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_PositionDirty) {

		if(!m_parent) {
			m_worldTransform = m_localTransform;
		}
		else {
			m_worldTransform.SetPosition( m_parent->GetWorldPosition() + m_localTransform.GetPosition());
		}

	}
	m_PositionDirty = false;
}


void dae::GameObject::SetParent(GameObject* parent , bool keepWorldPosition)
{
	if(IsChild(parent) || parent == this || m_parent == parent)
		return;
	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		SetPositionDirty();
	}
	if(m_parent) m_parent->RemoveChild(this);
	m_parent = parent;
	if(m_parent) m_parent->AddChild(this);
}

std::vector<dae::GameObject*>& dae::GameObject::GetChildren()
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
	//1. check if the new child is valid
	if (!child)
	{
		std::cerr << "AddChild: Child pointer is null.\n";
		return;
	}

	//2.add child to the children list
	m_Children.push_back(child);
	//3. update position and scale and rotation

}

void dae::GameObject::RemoveChild(GameObject* child)
{
	//1. check if the new child is valid
	if (!child)
	{
		std::cerr << "RemoveChild: Child pointer is null.\n";
		return;
	}
	//2.remove the given child from the children list

	auto it = std::find(m_Children.begin(), m_Children.end(), child);
	//3.


	if (it != m_Children.end())
	{
		(*it)->m_parent = nullptr;
		m_Children.erase(it);
	}
	else
	{
		std::cerr << "RemoveChild: Child not found.\n";
	}

}


