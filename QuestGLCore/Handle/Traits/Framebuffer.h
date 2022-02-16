#pragma once
#include "QuestGLCore/Handle/Typedefs.h"
#include <glad/glad.h>

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

		void bind_draw(const Typedefs::GLHandle& ogl_handle) const {
			glBindFramebuffer(m_draw_target, ogl_handle);
		}

		void unbind_draw() const {
			glBindFramebuffer(m_draw_target, 0);
		}

		void bind_read(const Typedefs::GLHandle& ogl_handle) const {
			glBindFramebuffer(m_read_target, ogl_handle);
		}

		void unbind_read() const {
			glBindFramebuffer(m_read_target, 0);
		}

		[[nodiscard]] GLenum get_target() const {
			return m_target;
		}

	private:
		GLenum m_target;
		GLenum m_read_target { GL_READ_FRAMEBUFFER };
		GLenum m_draw_target { GL_DRAW_FRAMEBUFFER };

	};

} // QuestGLCore::Traits