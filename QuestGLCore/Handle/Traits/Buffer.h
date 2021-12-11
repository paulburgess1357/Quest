#pragma once
#include "QuestGLCore/Handle/Typedefs.h"

namespace QuestGLCore::Traits {

	template<GLenum Target>
	struct BufferTraits {

		static Typedefs::HandleTypedef create() {
			Typedefs::HandleTypedef vbo{ };
			glGenBuffers(1, &vbo);
			return vbo;
		}

		static void destroy(const Typedefs::HandleTypedef& ogl_handle) {
			glDeleteBuffers(1, &ogl_handle);
		}

		static void bind(const Typedefs::HandleTypedef& ogl_handle) {
			glBindBuffer(Target, ogl_handle);
		}

		static void unbind() {
			glBindBuffer(Target, 0);
		}

	};

} // QuestGLCore::Traits