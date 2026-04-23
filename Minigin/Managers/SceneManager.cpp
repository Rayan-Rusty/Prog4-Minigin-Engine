#include "SceneManager.h"
#include "../Scene.h"

void dae::SceneManager::Update(float deltaTime) const
{
	GetActiveScene()->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	GetActiveScene()->Render();
}

dae::Scene& dae::SceneManager::CreateScene()
{

	m_scenes.emplace_back(new Scene());

	return *m_scenes.back();
}

void dae::SceneManager::SetActiveScene(size_t index)
{
	m_activeSceneIndex = index;
}

dae::Scene* dae::SceneManager::GetActiveScene() const
{
	return m_scenes[m_activeSceneIndex].get();
}
