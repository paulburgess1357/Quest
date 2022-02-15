#pragma once
#include <glm/glm.hpp>

namespace QuestEngine::Camera {

	class ProjectionMatrix {

	public:
		ProjectionMatrix(const int width, const int height);
		[[nodiscard]] glm::mat4 get_projection_matrix() const;
		void update_projection_matrix(const int width, const int height);

	private:
		glm::mat4 m_projection_matrix;

		static float DEFAULT_FOV;
		static float DEFAULT_ZNEAR;
		static float DEFAULT_ZFAR;
	};

} // namespace QuestEngine::Camera