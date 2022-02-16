#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace QuestEngine::ECS::Components {

	struct TransformComponent {
		explicit TransformComponent(const glm::vec3& world_position) {
			m_model_matrix = glm::translate(m_model_matrix, world_position);

		}
		glm::mat4 m_model_matrix { 1.0f };
		glm::mat3 m_normal_matrix{ 1.0f };
	};

} // namespace QuestEngine::ECS::Components