#pragma once
#include <glm/glm.hpp>
#include "Component.h"
namespace dae
{
	class GameObject;
	class Transform final : public Component
	{
	public:
		Transform(GameObject* owner);
		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetWorldPosition();

		void SetWorldPosition(const glm::vec3& pos);
		std::type_index GetType() const override;
	private:

		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};
	};
}
