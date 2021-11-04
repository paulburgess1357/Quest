#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace QuestWindow {
	namespace Interface {

		class IWindow {

		public:
			IWindow(const int width, const int height);
			~IWindow();

			IWindow(const IWindow& source) = delete;
			IWindow& operator=(const IWindow& rhs) = delete;

			IWindow(IWindow&& source) noexcept;
			IWindow& operator=(IWindow&& rhs) noexcept;

			void swap_buffer() const;
			[[nodiscard]] GLFWwindow* get_window() const;
			[[nodiscard]] bool close_window() const;

		protected:
			static void initialize();
			void create_window(const int width, const int height);
			void set_callbacks() const;
			GLFWwindow* m_window;

		private:
			// No singleton; Just forcing a single window:
			static bool m_window_exists;
			static void check_window_exists();


		};

	} // namespace Interface
} // namespace QuestWindow