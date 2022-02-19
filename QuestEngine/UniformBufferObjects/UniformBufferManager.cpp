#include "pch.h"
#include "UniformBufferManager.h"

namespace QuestEngine::UniformBufferObjects {

	UniformBufferManager::UniformBufferManager()
		:m_matrices{ nullptr } {
	}

	void UniformBufferManager::set_ubos(const Camera::Camera& camera, const Camera::ProjectionMatrix& projection_matrix) const {
		set_matrices(camera, projection_matrix);
	}

	void UniformBufferManager::set_matrices_ubo(UniformBufferObjects::UniformBufferObject& matrices) {
		m_matrices = &matrices;
	}

	void UniformBufferManager::set_matrices(const Camera::Camera& camera, const Camera::ProjectionMatrix& projection_matrix) const {
		m_matrices->send_data_to_buffer(projection_matrix.get_projection_matrix(), 0);
		m_matrices->send_data_to_buffer(camera.get_view_matrix(), sizeof(glm::mat4));
	}

} // QuestEngine::UniformBufferObjects