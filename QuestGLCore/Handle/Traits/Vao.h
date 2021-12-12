#pragma once
#include "QuestGLCore/Handle/Typedefs.h"

namespace QuestGLCore::Traits {

	struct VAOTraits {

		static Typedefs::GLHandle create() {
			Typedefs::GLHandle  vao{ };
			glGenVertexArrays(1, &vao);
			return vao;
		}

		static void destroy(const Typedefs::GLHandle& ogl_handle) {
			glDeleteVertexArrays(1, &ogl_handle);
		}

		static void bind(const Typedefs::GLHandle& ogl_handle) {
			glBindVertexArray(ogl_handle);
		}

		static void unbind() {
			glBindVertexArray(0);
		}

	};

} // QuestGLCore::Traits