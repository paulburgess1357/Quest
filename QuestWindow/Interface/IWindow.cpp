#include "pch.h"
#include "IWindow.h"
#include "IWindowException.h"
#include <iostream>

namespace QuestWindow {
	namespace Interface {

		IWindow::IWindow(const int width, const int height)
			:m_window{ nullptr } {
			initialize();
		}

		IWindow::~IWindow() {
			if(m_window != nullptr) {
				glfwDestroyWindow(m_window);
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
			std::cout << "Initializing GLFW" << std::endl;
			if (!glfwInit()) {
				throw IWindowInitException();
			}
		}

		void IWindow::create_window(const int width, const int height) {
			std::cout << "Creating Window" << std::endl;
			m_window = glfwCreateWindow(width, height, "Quest Engine", nullptr, nullptr);
			if (m_window == nullptr) {
				glfwTerminate();
				throw IWindowCreationException();
			}
		}

		void IWindow::set_callbacks() const {
			glfwSetInputMode(m_window, GLFW_STICKY_KEYS, true);
			glfwSetInputMode(m_window, GLFW_STICKY_MOUSE_BUTTONS, true);

			// VSync
			glfwSwapInterval(true);

			// Base Callbacks
			//glfwSetKeyCallback(m_window, InputManager<Keyboard>::window_callback);
			//glfwSetMouseButtonCallback(m_window, MouseManager::mouse_button_callback);
			//glfwSetCursorPosCallback(m_window, MouseManager::mouse_position_callback);
			//glfwSetCursorEnterCallback(m_window, MouseManager::mouse_within_window_callback);
		}

		void IWindow::swap_buffer() const {
			glfwSwapBuffers(m_window);
		}

		GLFWwindow* IWindow::get_window() const {
			return m_window;
		}

		bool IWindow::close_window() const {
			return glfwWindowShouldClose(m_window);
		}

	}
}