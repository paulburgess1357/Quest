#pragma once
#include "QuestEngine/Using/Window.h"
#include <glm/glm.hpp>

namespace QuestEngine::Camera {

	class ProjectionMatrix {

	public:
		ProjectionMatrix(const Window::Window& window);
		[[nodiscard]] glm::mat4 get_projection_matrix();

	private:
		void set_projection_matrix();

		const Window::Window& m_window;
		int m_window_width;
		int m_window_height;
		glm::mat4 m_projection_matrix;

		static float DEFAULT_FOV;
		static float DEFAULT_ZNEAR;
		static float DEFAULT_ZFAR;
	};

} // namespace QuestEngine::Camera