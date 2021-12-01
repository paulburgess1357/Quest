#pragma once
#include "QuestGLCore/Typedefs/Typedefs.h"

namespace QuestGLCore::Traits {

	struct BufferTraits {

		static Typedefs::HandleTypedef create() {
			Typedefs::HandleTypedef vbo{ };
			glGenBuffers(1, &vbo);
			return vbo;
		}

		static void destroy(const Typedefs::HandleTypedef& ogl_handle) {
			glDeleteBuffers(1, &ogl_handle);
		}

	};

} // QuestGLCore::Traits