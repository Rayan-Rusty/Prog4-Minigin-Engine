#pragma once
#include <string>
#include <memory>
#include "Transform.h"
#include "Component.h"
namespace dae
{

	class Texture2D;
	class GameObject final
	{
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};
		std::vector<std::unique_ptr<Component>> m_components;

	public:
		virtual void Update(float deltaTime);
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		Transform& GetTransform();

		//component Functions they have to be
		template<typename T>
		void AddComponent(std::unique_ptr<T>&& component)
		{
			m_components.push_back(std::move(component));
		}
		template<typename T>
		T* GetComponent()
		{
			for (auto& c : m_components)
				if (auto ptr = dynamic_cast<T*>(c.get()))
					return ptr;
			return nullptr;
		}

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	};
}
