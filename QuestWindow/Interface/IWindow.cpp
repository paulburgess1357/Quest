#include "pch.h"
#include "IWindow.h"
#include "IWindowException.h"

#include "Input/InputManager.h"
#include "Input/MouseManager.h"
#include "Input/Keyboard.h"

#include "QuestUtility/Include/Logger.h"

namespace QuestWindow::Interface {

	bool IWindow::m_window_exists{ false };
	int IWindow::m_width { 0 };
	int IWindow::m_height { 0 };
	float IWindow::m_aspect_ratio{ 16.0f / 9.0f };

	IWindow::IWindow(const int width, const int height)
		:m_window{ nullptr }{
		check_window_exists();
		initialize();
		m_window_exists = true;
		m_width = width;
		m_height = height;
	}

	IWindow::~IWindow() {
		if(m_window != nullptr) {
			QUEST_TRACE("Destroying Window")
			glfwDestroyWindow(m_window);
			m_window_exists = false;
		}
	}

	IWindow::IWindow(IWindow&& source) noexcept
		:m_window{ source.m_window} {
		source.m_window = nullptr;
	}

	IWindow& IWindow::operator=(IWindow&& rhs) noexcept{
		if(this != &rhs) {
			this->m_window = rhs.m_window;
			rhs.m_window = nullptr;
		}
		return *this;
	}

	void IWindow::initialize() {
		QUEST_TRACE("Initializing GLFW")
		if (!glfwInit()) {
			throw IWindowInitException();
		}
	}

	void IWindow::create_window() {
		QUEST_TRACE("Creating Window")
		m_window = glfwCreateWindow(m_width, m_height, "Quest Engine", nullptr, nullptr);
		if (m_window == nullptr) {
			glfwTerminate();
			throw IWindowCreationException();
		}
	}

	void IWindow::set_callbacks() const {
		glfwSetInputMode(m_window, GLFW_STICKY_KEYS, true);
		glfwSetInputMode(m_window, GLFW_STICKY_MOUSE_BUTTONS, true);

		// VSync
		glfwSwapInterval(false);

		// Base Callbacks
		glfwSetKeyCallback(m_window, Input::InputManager<Input::Keyboard>::window_callback);
		glfwSetMouseButtonCallback(m_window, Input::MouseManager::mouse_button_callback);
		glfwSetCursorPosCallback(m_window, Input::MouseManager::mouse_position_callback);
		glfwSetCursorEnterCallback(m_window, Input::MouseManager::mouse_within_window_callback);
	}

	void IWindow::swap_buffer() const {
		glfwSwapBuffers(m_window);
	}

	void IWindow::poll_events() {
		glfwPollEvents();
	}

	GLFWwindow* IWindow::get_window() const {
		return m_window;
	}

	bool IWindow::close_window() const {
		return glfwWindowShouldClose(m_window);
	}

	void IWindow::check_window_exists() {
		if(m_window_exists) {
			throw IWindowExistsException();
		}
	}

	int IWindow::get_width() {
		return m_width;
	}

	int IWindow::get_height() {
		return m_height;
	}

	float IWindow::get_aspect_ratio() {
		return m_aspect_ratio;
	}

} // namespace QuestWindow::Interface
