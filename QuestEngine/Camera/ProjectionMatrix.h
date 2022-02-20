#pragma once
#include <glm/glm.hpp>

namespace QuestEngine::Camera {

	class ProjectionMatrix {

	public:
		ProjectionMatrix(const float aspect_ratio);
		[[nodiscard]] glm::mat4 get_projection_matrix() const;

	private:
		void set_projection_matrix(const float aspect_ratio);
		glm::mat4 m_projection_matrix;

		static float DEFAULT_FOV;
		static float DEFAULT_ZNEAR;
		static float DEFAULT_ZFAR;
	};

} // namespace QuestEngine::Camera