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

			~TWindow() = default;

			TWindow(TWindow&& source) noexcept
				:m_window{ std::move(source.m_window) } {
			}

			TWindow& operator=(TWindow&& rhs) noexcept {
				m_window = std::move(rhs.m_window);
				return *this;
			}

			TWindow(const TWindow& source) = delete;
			TWindow& operator=(const TWindow& rhs) = delete;

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

			static void poll_events() {
				T::poll_events();
			}

			static int get_width() {
				return T::get_width();
			}

			static int get_height() {
				return T::get_height();
			}

		private:
			T m_window;
		};

	} // namespace Template
} // namespace QuestWindow