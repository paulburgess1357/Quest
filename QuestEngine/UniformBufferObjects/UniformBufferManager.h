#pragma once
#include "QuestEngine/Using/UniformBufferObjects.h"
#include "QuestEngine/Camera/Camera.h"
#include "QuestEngine/Camera/ProjectionMatrix.h"

namespace QuestEngine::UniformBufferObjects {

	class UniformBufferManager {

	public:
		UniformBufferManager();
		void set_ubos(const Camera::Camera& camera, const Camera::ProjectionMatrix& projection_matrix) const;
		void set_matrices_ubo(UniformBufferObjects::UniformBufferObject& matrices);
	private:
		void set_matrices(const Camera::Camera& camera, const Camera::ProjectionMatrix& projection_matrix) const;
		UniformBufferObjects::UniformBufferObject* m_matrices;

	};

} // QuestEngine::UniformBufferObjects