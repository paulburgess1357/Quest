#pragma once
#include "QuestGLCore/Handle/Typedefs.h"

namespace QuestGLCore::Traits {

	struct ShaderProgramTraits {

		static Typedefs::GLHandle create() {
			const Typedefs::GLHandle shader_handle{ glCreateProgram() };
			return shader_handle;
		}

		static void destroy(const Typedefs::GLHandle& shader_handle) {
			glDeleteProgram(shader_handle);
		}

		static void bind(const Typedefs::GLHandle& shader_handle) {
			glUseProgram(shader_handle);
		}

		static void unbind() {
			glUseProgram(0);
		}

	};	

} // QuestGLCore::Traits
