#pragma once
#include <vector>
//#include <string>
#include <memory>
#include "../Scene.h"
#include "../Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene();

		void Update(float deltaTime) const;
		void Render();

		// this way the game can switch scenes
		void SetActiveScene(size_t index);

		Scene* GetActiveScene() const;



	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_scenes{};
		size_t m_activeSceneIndex{0}; // cant go below 0
	};
}
