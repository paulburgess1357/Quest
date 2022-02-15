#pragma once
#include "QuestWindow/Include/Window.h"

namespace QuestWindow::Window {
	using Window = QuestWindow::Template::TWindow<QuestWindow::OpenGL::OGLWindow, GLFWwindow>;
	using KeyboardInput = QuestWindow::Input::InputManager<QuestWindow::Input::Keyboard>;
	using Keyboard = QuestWindow::Input::Keyboard;
	using MouseInput = QuestWindow::Input::MouseManager;
} // namespace QuestEngine::Window
