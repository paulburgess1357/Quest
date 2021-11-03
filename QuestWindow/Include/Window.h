#pragma once
#include "QuestWindow/Template/TWindow.h"
#include "QuestWindow/OpenGL/OGLWindow.h"

namespace QuestWindow {
	using Window = Template::TWindow<OpenGL::OGLWindow, GLFWwindow>;
} // namespace QuestWindow