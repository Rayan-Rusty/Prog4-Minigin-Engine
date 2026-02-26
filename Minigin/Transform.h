#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_position; }
		//TODO the World and Local transforms in GameObject need to be in here
		void SetPosition(float x, float y, float z = 0);
		void SetPosition(const glm::vec3& position);

	private:
		glm::vec3 m_position;
	};
}
