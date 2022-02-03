#include "pch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace QuestEngine::Camera {

	Camera::Camera(const glm::vec3& camera_position, const glm::vec3& pt_to_look_at_in_world)
		:m_camera_position{ camera_position },
		m_camera_forward{ 1.0f },
		m_camera_right{ 1.0f },
		m_camera_up{ 0.0f, 1.0f, 0.0f },
		m_world_up{ 0.0f, 1.0f, 0.0f },
		m_view_matrix{ 1.0f } {
		init_camera(pt_to_look_at_in_world);
	}

	void Camera::init_camera(const glm::vec3& pt_to_look_at_in_world) {
		m_camera_forward = glm::normalize(pt_to_look_at_in_world - m_camera_position);
		m_camera_right = glm::normalize(glm::cross(m_world_up, m_camera_forward));
		m_camera_up = glm::normalize(glm::cross(m_camera_forward, m_camera_right));
		set_view_matrix();
	}

	glm::mat4 Camera::get_view_matrix() const {
		return m_view_matrix;
	}

	void Camera::set_view_matrix() {
		m_view_matrix = glm::lookAt(
			m_camera_position,
			m_camera_position + m_camera_forward,
			m_camera_up
		);
	}

} // namespace QuestEngine::Camera
