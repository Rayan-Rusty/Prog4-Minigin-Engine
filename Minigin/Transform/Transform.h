#pragma once
#include <glm/glm.hpp>
#include "Component.h"
namespace dae
{
	class GameObject;
	class Transform final : public Component
	{
	public:
		explicit Transform(GameObject* owner);
		~Transform() override = default;
		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetWorldPosition();

		void SetScale(const glm::vec3& scale);
		const glm::vec3& GetScale() const;

		void SetWorldPosition(const glm::vec3& pos);
		std::type_index GetType() const override;
	private:

		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};
		glm::vec3 m_scale{1.f,1.f,1.f};
	};
}
