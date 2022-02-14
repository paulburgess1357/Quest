#pragma once
#include "QuestGLCore/Handle/Typedefs.h"

namespace QuestGLCore::Traits {

	class FramebufferTraits {

	public:
		explicit FramebufferTraits()
			:m_target{ 0 } {
		}

		explicit FramebufferTraits(const GLenum target)
			:m_target{ target } {
		}

		static Typedefs::GLHandle create() {
			Typedefs::GLHandle fbo{ };
			glGenFramebuffers(1, &fbo);
			return fbo;
		}

		static void destroy(const Typedefs::GLHandle& ogl_handle) {
			glDeleteFramebuffers(1, &ogl_handle);
		}

		void bind(const Typedefs::GLHandle& ogl_handle) const {
			glBindFramebuffer(m_target, ogl_handle);
		}

		void unbind() const {
			glBindFramebuffer(m_target, 0);
		}

	private:
		GLenum m_target;

	};

} // QuestGLCore::Traits