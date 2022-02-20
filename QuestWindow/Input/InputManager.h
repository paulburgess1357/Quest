// ReSharper disable CppParameterNeverUsed
#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>

namespace QuestWindow {
	namespace Input {

		template<typename T>
		class InputManager {

		public:
			InputManager() = delete;

			[[nodiscard]] static bool is_pressed(const T key_id) {
				const auto it = m_key_pressed_map.find(key_id);
				if (it != m_key_pressed_map.end()) {
					return it->second.first;
				}
				return false;
			}

			[[nodiscard]] static bool is_initial_press(const T key_id) {
				const auto it = m_key_pressed_map.find(key_id);
				if (it != m_key_pressed_map.end()) {
					const bool return_value = it->second.second;
					it->second.second = false;
					return return_value;
				}
				return false;
			}

		private:
			static void set_press(const T key_id) {
				m_key_pressed_map[key_id].first = true;
				m_key_pressed_map[key_id].second = true;
			}

			static void set_release(const T key_id) {
				m_key_pressed_map[key_id].first = false;
			}

			// ReSharper disable once CppParameterMayBeConst
			static void window_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
				switch (action) {
					case GLFW_PRESS:
						set_press(static_cast<T>(key));
						break;
					case GLFW_RELEASE:
						set_release(static_cast<T>(key));
						break;
					default:
						break;
					}
			}

			// key id, is_pressed
			// key_id; <current press, initial press>
			static std::unordered_map<T, std::pair<bool, bool>> m_key_pressed_map;

			// Required access for callbacks
			friend Interface::IWindow;
		};

		template <typename T>
		std::unordered_map<T, std::pair<bool, bool>> InputManager<T>::m_key_pressed_map;  // NOLINT(clang-diagnostic-exit-time-destructors)

	} // namespace Input
} // namespace QuestWindow