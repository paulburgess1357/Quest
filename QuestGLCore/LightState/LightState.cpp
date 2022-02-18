#include "pch.h"
#include "LightState.h"

namespace QuestGLCore::LightState {

	void LightState::light_pass_start() {
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_ONE, GL_ONE);
	}

	void LightState::light_pass_end() {
		glEnable(GL_DEPTH_TEST);
	}


} // QuestGLCore::LightStateManager