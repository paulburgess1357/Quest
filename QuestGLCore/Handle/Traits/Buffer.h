#pragma once
#include "QuestGLCore/Handle/Typedefs.h"

namespace QuestGLCore::Traits {

	class BufferTraits{

	public:
		BufferTraits(const GLenum target)
			:m_target{ target } {
		}

		static Typedefs::GLHandle create() {
			Typedefs::GLHandle vbo{ };
			glGenBuffers(1, &vbo);
			return vbo;
		}

		static void destroy(const Typedefs::GLHandle& ogl_handle) {
			glDeleteBuffers(1, &ogl_handle);
		}

		void bind(const Typedefs::GLHandle& ogl_handle) {
			glBindBuffer(m_target, ogl_handle);
		}

		void unbind() {
			glBindBuffer(m_target, 0);
		}

	private:
		const GLenum m_target;

	};

} // QuestGLCore::Traits