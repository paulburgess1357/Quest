#pragma once
#include "QuestGLCore/Typedefs/Typedefs.h"

namespace QuestGLCore::Traits {

	struct ShaderProgramTraits {

		static Typedefs::HandleTypedef create() {
			const Typedefs::HandleTypedef shader_handle{ glCreateProgram() };
			return shader_handle;
		}

		static void destroy(const Typedefs::HandleTypedef& shader_handle) {
			glDeleteProgram(shader_handle);
		}

	};

} // QuestGLCore::Traits