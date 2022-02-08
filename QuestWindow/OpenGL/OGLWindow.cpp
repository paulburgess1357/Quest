#include "pch.h"
#include "OGLWindow.h"
#include "OGLWindowException.h"
#include "OGLDebugContext.h"
#include "QuestUtility/Include/Logger.h"

namespace QuestWindow {
	namespace OpenGL {

		OGLWindow::OGLWindow(const int width, const int height)
			:IWindow{ width, height } {
			initialize(4, 3);
		}

		OGLWindow::OGLWindow(const int width, const int height, const int major_version, const int minor_version)
			:IWindow{ width, height } {
			initialize(major_version, minor_version);
		}

		void OGLWindow::initialize(const int major_version, const int minor_version) {

			// GLFW Hints (Must be prior to window creation)
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_SAMPLES, 4);

			// GLFW OpenGL Debug Context
			InitGLFWOpenGLDebugContext()

			// Create Window (Must be after hints)
			IWindow::create_window();

			// Set Context
			glfwMakeContextCurrent(m_window);

			// Load GLAD
			QUEST_TRACE("Initializing GLAD")
			if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
				throw OGLGladException();
			}
			// The results of glGetString mess up with SPD Logger hence the following conversion:
			auto result = std::string{ reinterpret_cast<const char*>(glGetString(GL_VERSION)) };
			QUEST_TRACE("OpenGL Version: {}", result)

			// GLFW OpenGL Debug Context (Must be after GLAD); OpenGL 4.3 Minimum
			InitOpenGLErrorCheck()

			// Set OGL Settings
			glViewport(0, 0, m_width, m_height);
			glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glEnable(GL_FRAMEBUFFER_SRGB);
			glEnable(GL_MULTISAMPLE);
			glEnable(GL_CULL_FACE);
			glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

			// Set Overall Callbacks
			IWindow::set_callbacks();

			// Set OGL Specific Callbacks
			set_ogl_callbacks();
		}

		void OGLWindow::set_ogl_callbacks() const {
			glfwSetFramebufferSizeCallback(m_window, framebuffer_callback);
		}

		// ReSharper disable once CppParameterNeverUsed
		void OGLWindow::framebuffer_callback(GLFWwindow* window, const int width, const int height) {
			set_viewport(width, height);
			m_width = width;
			m_height = height;
		}

		void OGLWindow::set_viewport(const int width, const int height) {
			glViewport(0, 0, width, height);
		}

		void OGLWindow::clear_buffer() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

	} // namespace OpenGL
} // namespace QuestWindow