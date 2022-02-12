#pragma once
#include <GLFW/glfw3.h>

namespace QuestUI::ImGuiLib {

	class ImguiWindow {

	public:
		ImguiWindow();
		~ImguiWindow();

		void create(GLFWwindow* window);
		void shutdown();

		
		void begin_render();
		void end_render();
	};

} // namespace QuestUI::Imgui