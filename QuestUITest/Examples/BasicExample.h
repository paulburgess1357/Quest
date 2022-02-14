#pragma once
#include "QuestWindow/Include/Window.h"
#include "QuestUI/ImguiWindow/ImGuiWindow.h"
namespace QuestUITest::Examples {

	void basic_example() {
		const QuestWindow::OpenGL::OGLWindow window{ 1920, 1080 };
		QuestUI::OpenGL::ImguiWindow imgui_window{window.get_window()};

		while (!window.close_window()) {
			window.clear_buffer();
			// Important: Imgui begin and end render need to be after everything else has finished!  For example, if you are drawing to a texture that you want imgui to use.
			QuestUI::OpenGL::ImguiWindow::begin_render();


			// imgui calls go here ==================
			QuestUI::OpenGL::ImguiWindow::show_demo();
			// =======================================

			QuestUI::OpenGL::ImguiWindow::end_render();

			window.poll_events();
			window.swap_buffer();
		}
	}

} // namespace namespace QuestUITest::Examples