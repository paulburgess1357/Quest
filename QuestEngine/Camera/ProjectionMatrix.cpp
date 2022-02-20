#include "pch.h"
#include "ProjectionMatrix.h"
#include <glm/gtc/matrix_transform.hpp>
#include "QuestUtility/Include/Logger.h"

namespace QuestEngine::Camera {

	float ProjectionMatrix::DEFAULT_FOV { 60.0f };
	float ProjectionMatrix::DEFAULT_ZNEAR { 0.1f };
	float ProjectionMatrix::DEFAULT_ZFAR { 2000.0f };

	ProjectionMatrix::ProjectionMatrix(const float aspect_ratio)
		:m_projection_matrix{ 1.0f }{
		set_projection_matrix(aspect_ratio);
	}

	void ProjectionMatrix::set_projection_matrix(const float aspect_ratio) {
		m_projection_matrix = glm::perspective(glm::radians(DEFAULT_FOV),
			aspect_ratio,
			DEFAULT_ZNEAR, DEFAULT_ZFAR);
			QUEST_TRACE("Setting projection matrix based on aspect ratio: {}", aspect_ratio)
	}

	glm::mat4 ProjectionMatrix::get_projection_matrix() const {
		return m_projection_matrix;
	}

} // namespace QuestEngine::Camera