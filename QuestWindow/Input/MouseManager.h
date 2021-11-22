#pragma once
#include "Mouse.h"
#include <glm/glm.hpp>

namespace QuestWindow {
	namespace Input {

		class MouseManager {

		public:
			MouseManager() = delete;
			static bool is_pressed(const Mouse mouse_button_id);
			static bool is_within_window();
			static glm::vec2 get_coords();

		private:
			static void set_press(const unsigned int mouse_button_id);
			static void set_release(const unsigned int mouse_button_id);

			static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			static void mouse_position_callback(GLFWwindow* window, double x_pos, double y_pos);
			static void mouse_within_window_callback(GLFWwindow* window, int entered);

			static bool m_within_window;
			static glm::vec2 m_coords;
			static bool m_left_button_pressed;
			static bool m_right_button_pressed;

			// Required access for callbacks
			friend Interface::IWindow;
		};

	} // namespace Input
} // namespace QuestWindow