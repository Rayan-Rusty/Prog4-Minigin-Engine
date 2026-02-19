#pragma once
#include <string>
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <format>
#include <iostream>
#include <type_traits>

namespace dae
{

	class Texture2D;
	class TextComponent;
	class GameObject final
	{


	public:
		void Update(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);

		Transform& GetTransform();

		//component Functions - if necessary to have two of the same components maybe use pairs to ID them not sure if i should do this yet?
		template<typename T>
		void AddComponent(std::unique_ptr<T>&& component)
		{
			//safety checks
			//https://en.cppreference.com/w/cpp/types/is_base_of.html
			// a helper function for checking wether its the derived class of a base class in this case Component
			static_assert(std::is_base_of_v<Component, T>, "T needs to inherit from component"); //compile time

			if (!component)
			{
				std::cout << "GameObject::AddComponent: Component is a nullptr." << std::endl;
				return;
			}


			m_components.emplace_back(std::move(component));
			std::cout << std::format("The following component was added: {}\n", typeid(T).name());
		}

		//cash it with an ID so you dotn need to iterate constantly
		template<typename T>
		T* GetComponent()
		{
			for (auto& component : m_components)
				if (component->GetType() == typeid(T)) //this way i avoid a dynamic cast
					return static_cast<T*>(component.get());
			return nullptr;
		}

		//https://www.geeksforgeeks.org/cpp/std-remove-if-algorithm-in-cpp-stl/
		// this is an example I found of std::remove-if in which it uses a lambda too

		template<typename T>
		void RemoveComponent()
		{
			//removes components that are the same type as the given one
			auto iteration = std::remove_if(m_components.begin(), m_components.end(),
				[](const std::unique_ptr<Component>& component)
				{
					return component->GetType() == typeid(T);
				});

			m_components.erase(iteration, m_components.end()); // now it removes every similar type from the vector

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
