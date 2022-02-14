#pragma once
#include "QuestGLCore/Handle/Typedefs.h"

namespace QuestGLCore::Traits {

	class RenderbufferTraits {

	public:
		explicit RenderbufferTraits()
			:m_target{ 0 } {
		}

		explicit RenderbufferTraits(const GLenum target)
			:m_target{ target } {
		}

		static Typedefs::GLHandle create() {
			Typedefs::GLHandle rbo{ };
			glGenRenderbuffers(1, &rbo);
			return rbo;
		}

		static void destroy(const Typedefs::GLHandle& ogl_handle) {
			glDeleteRenderbuffers(1, &ogl_handle);
		}

		void bind(const Typedefs::GLHandle& ogl_handle) const {
			glBindRenderbuffer(m_target, ogl_handle);
		}

		void unbind() const {
			glBindRenderbuffer(m_target, 0);
		}

		[[nodiscard]] GLenum get_target() const {
			return m_target;
		}

	private:
		GLenum m_target;

	};

} // QuestGLCore::Traits