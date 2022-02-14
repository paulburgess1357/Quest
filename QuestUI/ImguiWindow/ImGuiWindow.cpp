#include "pch.h"
#include "ImGuiWindow.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace QuestUI::OpenGL {

	bool ImguiWindow::m_created{ false };

	ImguiWindow::ImguiWindow(GLFWwindow* window)
		:m_window{ window },
		m_imgui_io{ nullptr }{
		create();
	}

	ImguiWindow::~ImguiWindow() {
		destroy();
	}

	void ImguiWindow::create() {
		if(!m_created) {
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			// Configuration
			m_imgui_io = &ImGui::GetIO();
			m_imgui_io->ConfigWindowsMoveFromTitleBarOnly = true;
			m_imgui_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			m_imgui_io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

			ImGui_ImplGlfw_InitForOpenGL(m_window, true);
			ImGui_ImplOpenGL3_Init("#version 330"); //TODO query this
			m_created = true;
		}
	}

	void ImguiWindow::destroy() {
		if(m_created) {
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
			m_created = false;
		}
	}

	void ImguiWindow::begin_render() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Allow docking within main window:
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	}

	void ImguiWindow::end_render() const {
		// End render for the main window & context
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// End render for ImGui context (viewports)
		if(m_imgui_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();

			// Switch back to the main OpenGL context
			glfwMakeContextCurrent(m_window);

		}

	}

	void ImguiWindow::show_demo() {
		ImGui::ShowDemoWindow();
	}

	//bool ImguiWindow::ui_using_inputs() {
	//	return ui_using_mouse() || ui_using_keyboard();
	//}

	//bool ImguiWindow::ui_using_mouse() {
	//	return m_imgui_io->WantCaptureMouse;
	//}

	//bool ImguiWindow::ui_using_keyboard() {
	//	return m_imgui_io->WantCaptureKeyboard;
	//}

} // namespace QuestUI::Imgui