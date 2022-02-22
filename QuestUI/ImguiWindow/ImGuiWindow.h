#pragma once
#include <imgui.h>
#include <GLFW/glfw3.h>

namespace QuestUI::OpenGL {

	class ImguiWindow {

	public:
		explicit ImguiWindow(GLFWwindow* window);
		~ImguiWindow();

		ImguiWindow(const ImguiWindow& source) = delete;
		ImguiWindow(ImguiWindow&& source) = delete;
		ImguiWindow& operator=(const ImguiWindow& rhs) = delete;
		ImguiWindow& operator=(ImguiWindow&& rhs) = delete;

		void create();
		static void destroy();
		
		static void begin_render();
		static void show_metrics();
		static void show_demo();
		static void show_user_guide();

		void show_viewport(void* handle) const;
		[[nodiscard]] ImVec2 get_viewport_dimensions(const float window_section_width, const float window_section_height) const;


		void end_render() const;

		//static bool ui_using_inputs();
		//static bool ui_using_mouse();
		//static bool ui_using_keyboard();

	private:
		static bool m_created;
		GLFWwindow* m_window;
		ImGuiIO* m_imgui_io;

		const float aspect_ratio = 16.0f / 9.0f;

	};

} // namespace QuestUI::Imgui