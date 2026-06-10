#include <algorithm>
#include "Scene.h"

#include "CollisionManager.h"

using namespace dae;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(const GameObject& object)
{
	m_objects.erase(
		std::remove_if(
			m_objects.begin(),
			m_objects.end(),
			[&object](const auto& ptr) { return ptr.get() == &object; }
		),
		m_objects.end()
	);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}

	CollisionManager::GetInstance().Update();
	m_eventBus.ProcessEvents();
}

void Scene::RemoveGameObject()
{
	//erasing objects correctly
	m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
		[](const std::unique_ptr<GameObject>& object)
		{
			return object->GetShouldDelete();
		}
	),
	m_objects.end());
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void Scene::SortByLayer()
{
	std::stable_sort(m_objects.begin(), m_objects.end(),
		[](const auto& a , const auto& b)
		{
			return a->GetLayer() < b->GetLayer();
		}
		);
}

EventBus &Scene::GetEventBus() {
	return m_eventBus;
}

void Scene::StoreSystem(std::unique_ptr<IEventListener> system)
{
	m_eventBus.AddListener(system.get());
	m_listeners.emplace_back(std::move(system));
}

void Scene::Clear()
{
	m_objects.clear();
	m_listeners.clear();

    //m_eventBus.Clear();
}

std::vector<GameObject *> Scene::GetObjectByTag(int tag)
{
	std::vector<GameObject*> objects;
	for (const auto& object : m_objects)
	{
		if (object != nullptr && object->GetTag() == tag)
			objects.emplace_back(object.get());
	}

	return objects;
}
