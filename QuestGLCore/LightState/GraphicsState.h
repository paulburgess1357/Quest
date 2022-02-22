#pragma once
#include <glad/glad.h>

namespace QuestGLCore::Graphics {

	class State {
	public:
		static void light_pass_start();
		static void light_pass_end();

		static void set_viewport(const GLint x, const GLint y, const GLsizei width, const GLsizei height);

	};

} // QuestGLCore::LightStateManager