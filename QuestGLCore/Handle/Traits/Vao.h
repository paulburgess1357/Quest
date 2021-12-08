#pragma once
#include "QuestGLCore/Handle/Typedefs.h"

namespace QuestGLCore::Traits {

	struct VAOTraits {

		static Typedefs::HandleTypedef create() {
			Typedefs::HandleTypedef  vao{ };
			glGenVertexArrays(1, &vao);
			return vao;
		}

		static void destroy(const Typedefs::HandleTypedef& ogl_handle) {
			glDeleteVertexArrays(1, &ogl_handle);
		}

	};

} // QuestGLCore::Traits