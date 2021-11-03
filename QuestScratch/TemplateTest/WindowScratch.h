#pragma once
// #include <GLFW/glfw3.h>
#include <iostream>

namespace TemplateTest {

	// Interface
	class IWindow {
	public:
		virtual ~IWindow() = default;
		virtual void swap_buffffer() = 0;
	};

	// Implementation
	class OGLWindow : public IWindow {
	public:
		void swap_buffffer() override {
			std::cout << "OGL Swapping Buffer" << std::endl;
		}
		// protected:
		void test() {
			std::cout << "OGL running test" << std::endl;
		}
	};

	class VulkanWindow : public IWindow {
	public:
		void swap_buffffer() override {
			std::cout << "Vulkan Swapping Buffer" << std::endl;
		}
		void test() {
			std::cout << "Vulkan running test" << std::endl;
		}
	};

	// Template implementation
	template<typename T>
	class Window : public IWindow {
	public:
		Window() = default;
		void swap_buffer() {
			m_window.swap_buffer();
			m_window.test();
		}

	private:
		T m_window;
	};

} // namespace TemplateTest