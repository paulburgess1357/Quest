#pragma once
#include "QuestEngine/Using/UniformBufferObjects.h"
#include "QuestEngine/Camera/Camera.h"
#include "QuestEngine/Camera/ProjectionMatrix.h"

namespace QuestEngine::UniformBufferObjects {

	class UniformBufferManager {

	public:
		explicit UniformBufferManager(UniformBufferObjects::UniformBufferObject& matrices);
		void set_ubos(Camera::Camera& camera, Camera::ProjectionMatrix& projection_matrix) const;
	private:
		void set_matrices(Camera::Camera& camera, Camera::ProjectionMatrix& projection_matrix) const;
		UniformBufferObjects::UniformBufferObject* m_matrices;

	};

} // QuestEngine::UniformBufferObjects