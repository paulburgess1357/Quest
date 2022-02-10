#include "pch.h"
#include "UniformBufferManager.h"

namespace QuestEngine::UniformBufferObjects {

	UniformBufferManager::UniformBufferManager(UniformBufferObjects::UniformBufferObject& matrices)
		:m_matrices{ &matrices }{
	}

	void UniformBufferManager::run(Camera::Camera& camera, Camera::ProjectionMatrix& projection_matrix) const {
		set_matrices(camera, projection_matrix);
	}

	void UniformBufferManager::set_matrices(Camera::Camera& camera, Camera::ProjectionMatrix& projection_matrix) const {
		m_matrices->send_data_to_buffer(projection_matrix.get_projection_matrix() * camera.get_view_matrix());
	}



} // QuestEngine::UniformBufferObjects