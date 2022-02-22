#include "pch.h"
#include "GraphicsState.h"

namespace QuestGLCore::Graphics {

	void State::light_pass_start() {
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);
	}

	void State::light_pass_end() {
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}

	void State::set_viewport(const GLint x, const GLint y, const GLsizei width, const GLsizei height) {
		glViewport(x, y, width, height);
	}

} // QuestGLCore::LightStateManager