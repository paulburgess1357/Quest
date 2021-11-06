#include "pch.h"
#include "IWindow.h"
#include "IWindowException.h"
#include <iostream>

#include "Input/InputManager.h"
#include "Input/Keyboard.h"

namespace QuestWindow {
	namespace Interface {

		bool IWindow::m_window_exists = false;

		IWindow::IWindow(const int width, const int height)
			:m_window{ nullptr } {
			check_window_exists();
			initialize();
			m_window_exists = true;
		}

		IWindow::~IWindow() {
			if(m_window != nullptr) {
				std::cout << "Destroying Window" << std::endl;
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
			glfwSetKeyCallback(m_window, Input::InputManager<Input::Keyboard>::window_callback);
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

		void IWindow::check_window_exists() {
			if(m_window_exists) {
				throw IWindowExistsException();
			}
		}

	}
}
