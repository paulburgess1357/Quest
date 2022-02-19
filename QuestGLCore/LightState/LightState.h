#pragma once
#include "QuestGLCore/Shader/ShaderProgram.h"

namespace QuestGLCore::LightState {

	class LightState {
	public:
		static void light_pass_start();
		static void light_pass_end();
	};

} // QuestGLCore::LightStateManager