#pragma once
#include "QuestWindow/Template/TWindow.h"
#include "QuestWindow/OpenGL/OGLWindow.h"

#include "QuestWindow/Input/Keyboard.h"
#include "QuestWindow/Input/InputManager.h"

namespace QuestWindow {

	using Window = Template::TWindow<OpenGL::OGLWindow, GLFWwindow>;
	using KeyboardInput = Input::InputManager<Input::Keyboard>;
	using Keyboard = Input::Keyboard;

} // namespace QuestWindow