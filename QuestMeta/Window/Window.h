#pragma once
// #include <GLFW/glfw3.h>
#include <iostream>
namespace QuestMeta {
	namespace Window {

		// Interface
		class IWindow {
		public:
			virtual ~IWindow()= default;
			virtual void swap_buffer() = 0;
		};

		// Implementation
		class OGLWindow : public IWindow {
		public:
			void swap_buffer() override {
				std::cout << "OGL Swapping Buffer" << std::endl;
			}
		protected:
			void test() {
				std::cout << "OGL running test" << std::endl;
			}
		};

		class VulkanWindow : public IWindow {
		public:
			void swap_buffer() override {
				std::cout << "Vulkan Swapping Buffer" << std::endl;
			}
			void test() {
				std::cout << "Vulkan running test" << std::endl;
			}
		};

		// Template implementation
		template<typename T>
		class Window {
		public:
			Window() = default;
			void swap_buffer() {
				m_window.swap_buffer();
				m_window.test();
			}
			//Window(const T& window)
			//	:m_window{ window } {
			//	m_window.swap_buffer();
			//}

		private:
			T m_window;

			



		};
	} // namespace Window
} // namespace QuestMeta