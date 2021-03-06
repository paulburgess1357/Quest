#pragma once
#include "QuestGLCore/Handle/Typedefs.h"

namespace QuestGLCore::Traits {

	class BufferTraits{

	public:
		explicit BufferTraits()
			:m_target{ 0 } {
		}

		explicit BufferTraits(const GLenum target)
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

		void bind(const Typedefs::GLHandle& ogl_handle) const {
			glBindBuffer(m_target, ogl_handle);
		}

		void unbind() const {
			glBindBuffer(m_target, 0);
		}

		[[nodiscard]] GLenum get_target() const {
			return m_target;
		}

	private:
		GLenum m_target;

	};

} // QuestGLCore::Traits