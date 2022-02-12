#pragma once
#include "QuestWindow/Include/Window.h"
#include "QuestUI/ImguiWindow/ImGuiWindow.h"
#include "imgui.h"

namespace QuestUITest::Examples {

	void basic_example() {
		QuestWindow::OpenGL::OGLWindow window{ 1920, 1080 };
		QuestUI::ImGuiLib::ImguiWindow imgui_window;
		imgui_window.create(window.get_window());

		while (!window.close_window()) {
			window.clear_buffer();
			// Important: Imgui begin and end render need to be after everything else has finished!  For example, if you are drawing to a texture that you want imgui to use.
			imgui_window.begin_render();
			// imgui calls go here
			ImGui::ShowDemoWindow();
			imgui_window.end_render();

			window.poll_events();
			window.swap_buffer();
		}
		imgui_window.shutdown();
	}

} // namespace namespace QuestUITest::Examples