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
		static void show_demo();
		static void show_viewport(void* handle);
		void end_render() const;

		//static bool ui_using_inputs();
		//static bool ui_using_mouse();
		//static bool ui_using_keyboard();

	private:
		static bool m_created;
		GLFWwindow* m_window;
		ImGuiIO* m_imgui_io;
	};

} // namespace QuestUI::Imgui