#include "pch.h"
#include "ProjectionMatrix.h"
#include <glm/gtc/matrix_transform.hpp>
#include "QuestUtility/Include/Logger.h"

namespace QuestEngine::Camera {

	float ProjectionMatrix::DEFAULT_FOV { 60.0f };
	float ProjectionMatrix::DEFAULT_ZNEAR { 0.1f };
	float ProjectionMatrix::DEFAULT_ZFAR { 2000.0f };

	ProjectionMatrix::ProjectionMatrix(const int width, const int height)
		:m_projection_matrix{ 1.0f }{
		update_projection_matrix(width, height);
	}

	void ProjectionMatrix::update_projection_matrix(const int width, const int height) {
		m_projection_matrix = glm::perspective(glm::radians(DEFAULT_FOV),
			static_cast<float>(width) / static_cast<float>(height),
			DEFAULT_ZNEAR, DEFAULT_ZFAR);
			QUEST_TRACE("Setting projection matrix based on window dimensions: {}x{}", width, height)
	}

	glm::mat4 ProjectionMatrix::get_projection_matrix() const {
		return m_projection_matrix;
	}

} // namespace QuestEngine::Camera