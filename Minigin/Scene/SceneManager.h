#pragma once
#include <vector>

#include <memory>
#include "Scene.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene();

		void Update(float deltaTime);
		void Render();

		// this way the game can switch scenes
		void SetActiveScene(size_t index);
		void SetPendingScene(size_t index);
		Scene* GetActiveScene() const;
		void ClearScene(size_t index);
		EventBus& GetEventBus();


		void RegisterScene(size_t index, std::function<void()> initFunc);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		size_t m_activeSceneIndex{0}; // cant go below 0
		size_t m_PendingSceneIndex{2}; // cant go below 0
		std::vector<std::function<void()>> m_SceneInitialization;

		std::vector<std::unique_ptr<Scene>> m_scenes{};
		bool m_PendingSceneChange = {false};


	};
}
