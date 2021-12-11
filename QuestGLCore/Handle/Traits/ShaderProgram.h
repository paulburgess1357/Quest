#pragma once
#include "QuestGLCore/Handle/Typedefs.h"

namespace QuestGLCore::Traits {

	struct ShaderProgramTraits {

		static Typedefs::HandleTypedef create() {
			const Typedefs::HandleTypedef shader_handle{ glCreateProgram() };
			return shader_handle;
		}

		static void destroy(const Typedefs::HandleTypedef& shader_handle) {
			glDeleteProgram(shader_handle);
		}

		static void bind(const Typedefs::HandleTypedef& shader_handle) {
			glUseProgram(shader_handle);
		}

		static void unbind() {
			glUseProgram(0);
		}

	};	

} // QuestGLCore::Traits
