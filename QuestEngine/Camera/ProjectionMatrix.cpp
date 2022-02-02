#include "pch.h"
#include "ProjectionMatrix.h"
#include <glm/gtc/matrix_transform.hpp>
#include "QuestUtility/Include/Logger.h"

namespace QuestEngine::Camera {

	float ProjectionMatrix::DEFAULT_FOV { 60.0f };
	float ProjectionMatrix::DEFAULT_ZNEAR { 0.1f };
	float ProjectionMatrix::DEFAULT_ZFAR { 2000.0f };

	ProjectionMatrix::ProjectionMatrix(const Window::Window& window)
		:m_window{ window },
		m_window_width{ window.get_width() },
		m_window_height{ window.get_height() },
		m_projection_matrix{ 1.0f }{
		set_projection_matrix();
	}

	void ProjectionMatrix::set_projection_matrix() {
		m_projection_matrix = glm::perspective(glm::radians(DEFAULT_FOV),
			static_cast<float>(m_window_width) / static_cast<float>(m_window_height),
			DEFAULT_ZNEAR, DEFAULT_ZFAR);
		QUEST_TRACE("Setting projection matrix based on window dimensions: {}x{}", m_window_width, m_window_height)
	}

	glm::mat4 ProjectionMatrix::get_projection_matrix() {
		if (m_window.get_width() != m_window_width || m_window.get_height() != m_window_height) {
			m_window_width = m_window.get_width();
			m_window_height = m_window.get_height();
			set_projection_matrix();
		}
		return m_projection_matrix;
	}

} // namespace QuestEngine::Camera