#include "pch.h"
#include "ImGuiWindow.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "QuestUI/Candy/Candy.h"

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
			m_imgui_io->FontGlobalScale = 1.8f; //TODO this probably isn't the best way to scale fone.

			ImGui_ImplGlfw_InitForOpenGL(m_window, true);
			ImGui_ImplOpenGL3_Init("#version 330");
			Candy::Theme_Nord();
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
		// If not rendering to a texture and specifying a proper viewport area,
		// the area will look dark (due to imgui transparent grey color over it)
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

	void ImguiWindow::show_user_guide() {
		ImGui::ShowUserGuide();
	}

	void ImguiWindow::show_metrics() {
		ImGui::ShowMetricsWindow();
	}

	void ImguiWindow::show_viewport(void* handle) const {
		if(ImGui::Begin("GameView")) {
			const ImVec2 window_section_size = ImGui::GetWindowSize();
			// Window size includes scrollbar (hence the -35 estimate)
			const ImVec2 viewport_size = get_desired_viewport_dimensions(window_section_size.x - 15, window_section_size.y - 35);
			// Center texture
			const ImVec2 viewport_position = {
				(window_section_size.x - viewport_size.x) * 0.5f,
				((window_section_size.y - viewport_size.y) * 0.5f) + 8,
			};
			ImGui::SetCursorPos(viewport_position);
			ImGui::Image(handle, viewport_size, { 0, 1}, { 1, 0 } ); //todo check these
		}

		ImGui::End();
	}

	ImVec2 ImguiWindow::get_desired_viewport_dimensions(const float window_section_width, const float window_section_height) const{

		// Returns the necessary viewport dimensions to maintain the aspect ratio

		float viewport_width = window_section_height * aspect_ratio;
		float viewport_height = window_section_width * 1.0f / aspect_ratio;

		if (window_section_height > viewport_height) {
			viewport_width = window_section_width;
		} else {
			viewport_height = window_section_height;
		}
		return { viewport_width, viewport_height };
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