#pragma once
#include <utility>

namespace QuestWindow {
	namespace Template {

		template <typename T, typename WindowType>
		class TWindow {

		public:
			template<typename... Args>
			explicit TWindow(Args&&... args)
				:m_window{ std::forward<Args>(args)... } {
			}

			void clear_buffer() const {
				m_window.clear_buffer();
			}

			void set_viewport(const int width, const int height) const {
				m_window.set_viewport(width, height);
			}

			void swap_buffer() const {
				m_window.swap_buffer();
			}

			[[nodiscard]] bool close_window() const {
				return m_window.close_window();
			}

			[[nodiscard]] WindowType* get_window() const {
				return m_window.get_window();
			}

		private:
			T m_window;
		};

	} // namespace Template
} // namespace QuestWindow