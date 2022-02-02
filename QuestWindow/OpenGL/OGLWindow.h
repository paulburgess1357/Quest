#pragma once
#include "QuestWindow/Interface/IWindow.h"

namespace QuestWindow {
	namespace OpenGL {

		class OGLWindow final : public QuestWindow::Interface::IWindow {

		public:
			OGLWindow(const int width, const int height);
			OGLWindow(const int width, const int height, const int major_version, const int minor_version);
			static void clear_buffer();
			static void set_viewport(const int width, const int height);

		private:
			void initialize(const int major_version, const int minor_version);
			void set_ogl_callbacks() const;
			static void framebuffer_callback(GLFWwindow* window, const int width, const int height);

		};

	} // namespace OpenGL
} // namespace QuestWindow