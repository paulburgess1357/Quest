// ReSharper disable CppParameterNeverUsed
#include "pch.h"
#include "MouseManager.h"

namespace QuestWindow {
	namespace Input {

		MouseCoords MouseManager::m_coords{ 0.0, 0.0 };
		bool MouseManager::m_within_window = false;
		bool MouseManager::m_left_button_pressed = false;
		bool MouseManager::m_right_button_pressed = false;

		bool MouseManager::is_pressed(const Mouse mouse_button_id) {
			if (mouse_button_id == Mouse::LEFT_BUTTON) {
				return m_left_button_pressed;
			}
				return m_right_button_pressed;
		}

		MouseCoords MouseManager::get_coords() {
			return  m_coords;
		}

		bool MouseManager::is_within_window() {
			return m_within_window;
		}

		void MouseManager::mouse_button_callback(GLFWwindow* window, const int button, const int action, const int mods) {
			switch (action) {
				case GLFW_PRESS:
					set_press(button);
					break;
				case GLFW_RELEASE:
					set_release(button);
					break;
				default:
					break;
				}
		}

		void MouseManager::set_press(const unsigned int mouse_button_id) {
			if (mouse_button_id == GLFW_MOUSE_BUTTON_LEFT) {
				m_left_button_pressed = true;
			}

			if (mouse_button_id == GLFW_MOUSE_BUTTON_RIGHT) {
				m_right_button_pressed = true;
			}
		}

		void MouseManager::set_release(const unsigned int mouse_button_id) {
			if (mouse_button_id == GLFW_MOUSE_BUTTON_LEFT) {
				m_left_button_pressed = false;
			}

			if (mouse_button_id == GLFW_MOUSE_BUTTON_RIGHT) {
				m_right_button_pressed = false;
			}
		}

		void MouseManager::mouse_position_callback(GLFWwindow* window, const double x_pos, const double y_pos) {
			m_coords.m_pos_x = x_pos;
			m_coords.m_pos_y = y_pos;
		}

		// ReSharper disable once CppParameterMayBeConst
		void MouseManager::mouse_within_window_callback(GLFWwindow* window, int entered) {
			m_within_window = entered;
		}

	} // namespace Input
} // namespace QuestWindow