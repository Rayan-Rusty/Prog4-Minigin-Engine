#pragma once
#include <string>
#include <memory>
#include "Transform.h"
#include "Component.h"
namespace dae
{

	class Texture2D;
	class TextObject;
	class GameObject final
	{


	public:
		void Update(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);

		Transform& GetTransform();

		//component Functions they have to be - if necessary to have two of the same components maybe use pairs to ID them?
		template<typename T>
		void AddComponent(std::unique_ptr<T>&& component)
		{
			m_components.push_back(std::move(component));
		}
		template<typename T>
		T* GetComponent()
		{
			for (auto& component : m_components)
				if (component->GetType() == typeid(T))
					return static_cast<T*>(component.get());
			return nullptr;
		}

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		Transform m_transform{};

		std::vector<std::unique_ptr<Component>> m_components;
	};
}
