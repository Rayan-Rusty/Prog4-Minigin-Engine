#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for (auto& component : m_components)
		component->Update(deltaTime);
}

void dae::GameObject::Render() const
{
	for (auto& component : m_components)
		component->Render();
}


void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

dae::Transform &dae::GameObject::GetTransform()
{
	return m_transform;
}

