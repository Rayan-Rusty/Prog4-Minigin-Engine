#include "SceneManager.h"

#include "CollisionManager.h"
#include "InputManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	GetActiveScene()->Update(deltaTime);
	if (m_PendingSceneChange)
	{
		m_PendingSceneChange = false;
		SetActiveScene(m_PendingSceneIndex);
	}
}

void dae::SceneManager::Render()
{
	GetActiveScene()->Render();
}

dae::Scene& dae::SceneManager::CreateScene()
{

	m_scenes.emplace_back(std::make_unique<Scene>());
	m_SceneInitialization.emplace_back(nullptr); // placeholder
	return *m_scenes.back();
}

void dae::SceneManager::SetActiveScene(size_t index)
{
	//TODO load new scene
	//TODO unload previous scene


	if (index >= m_scenes.size())
		return;

	size_t previousIndex = m_activeSceneIndex;



	m_activeSceneIndex = index;
	if (m_SceneInitialization[index])
		m_SceneInitialization[index]();

	if (previousIndex != index)
		m_scenes[previousIndex]->Clear();
}

void dae::SceneManager::SetPendingScene(size_t index)
{
	m_PendingSceneIndex = index;
	m_PendingSceneChange = true;
}

dae::Scene* dae::SceneManager::GetActiveScene() const
{
	return m_scenes[m_activeSceneIndex].get();
}

void dae::SceneManager::ClearScene(size_t index)
{
	if (index >= m_scenes.size())
		return;
	m_scenes[index]->Clear();
}
dae::EventBus &dae::SceneManager::GetEventBus()
{
	return GetActiveScene()->GetEventBus();
}

void dae::SceneManager::RegisterScene(size_t index, std::function<void()> initFunc)
{
	if (index >= m_scenes.size())
	{
		m_scenes.resize(index + 1);
		m_SceneInitialization.resize(index + 1 , nullptr);
	}

	if (!m_scenes[index])
		m_scenes[index] = std::make_unique<dae::Scene>();


	m_SceneInitialization[index] = std::move(initFunc);

}
