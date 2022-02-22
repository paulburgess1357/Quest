#pragma once
// ReSharper disable once CppUnusedIncludeDirective
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
			static void poll_events();

			[[nodiscard]] static int get_width();
			[[nodiscard]] static int get_height();
			[[nodiscard]] static float get_aspect_ratio();

		protected:
			static void initialize();
			void create_window();
			void set_callbacks() const;
			GLFWwindow* m_window;
			static int m_width;
			static int m_height;

		private:
			// Forced single window
			static bool m_window_exists;
			static void check_window_exists();
			static float m_aspect_ratio;
		};

	} // namespace Interface
} // namespace QuestWindow