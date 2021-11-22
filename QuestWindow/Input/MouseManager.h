#pragma once
#include "Mouse.h"

namespace QuestWindow {
	namespace Input {

		struct MouseCoords {
			MouseCoords(const double x, const double y)
				:m_pos_x{ x }, m_pos_y{ y } {
			}
			double m_pos_x = 0.0;
			double m_pos_y = 0.0;
		};

		class MouseManager {

		public:
			MouseManager() = delete;
			static bool is_pressed(const Mouse mouse_button_id);
			static bool is_within_window();
			static MouseCoords get_coords();

		private:
			static void set_press(const unsigned int mouse_button_id);
			static void set_release(const unsigned int mouse_button_id);

			static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			static void mouse_position_callback(GLFWwindow* window, double x_pos, double y_pos);
			static void mouse_within_window_callback(GLFWwindow* window, int entered);

			static bool m_within_window;
			static MouseCoords m_coords;
			static bool m_left_button_pressed;
			static bool m_right_button_pressed;

			// Required access for callbacks
			friend Interface::IWindow;
		};

	} // namespace Input
} // namespace QuestWindow