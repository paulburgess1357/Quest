#pragma once
#include "QuestGLCore/Handle/Typedefs.h"

namespace QuestGLCore::Traits {

	template<GLenum Target>
	struct BufferTraits {

		static Typedefs::GLHandle create() {
			Typedefs::GLHandle vbo{ };
			glGenBuffers(1, &vbo);
			return vbo;
		}

		static void destroy(const Typedefs::GLHandle& ogl_handle) {
			glDeleteBuffers(1, &ogl_handle);
		}

		static void bind(const Typedefs::GLHandle& ogl_handle) {
			glBindBuffer(Target, ogl_handle);
		}

		static void unbind() {
			glBindBuffer(Target, 0);
		}

	};

} // QuestGLCore::Traits