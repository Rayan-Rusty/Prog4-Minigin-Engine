#pragma once
#include <memory>
#include <string>
#include <vector>
#include "GameObject.h"
#include "EventQueue/EventBus.h"

namespace dae
{
	class TextComponent;
	class Scene final
	{
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(const GameObject& object);
		void RemoveAll();

		EventBus& GetEventBus();
		void StoreSystem(std::unique_ptr<IEventListener> system);

		void Clear();


		void Update(float deltaTime);
		void RemoveGameObject();
		void Render() const;

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		friend class SceneManager;
		explicit Scene() = default;

		std::vector < std::unique_ptr<GameObject>> m_objects{};
		std::vector <std::unique_ptr<IEventListener>> m_listeners{};
		EventBus m_eventBus;

	};

}
