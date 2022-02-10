#pragma once
#include "QuestGLCore/Handle/Typedefs.h"

namespace QuestGLCore::Traits {

	class TextureTraits {

	public:
		explicit TextureTraits()
			:m_target{ 0 } {
		}

		explicit TextureTraits(const GLenum target)
			:m_target{ target } {
		}

		static Typedefs::GLHandle create() {
			Typedefs::GLHandle texture_handle{ };
			glGenTextures(1, &texture_handle);
			return texture_handle;
		}

		static void destroy(const Typedefs::GLHandle& ogl_handle) {
			glDeleteTextures(1, &ogl_handle);
		}

		void bind(const Typedefs::GLHandle& ogl_handle) const {
			glBindTexture(m_target, ogl_handle);
		}

		void unbind() const {
			glBindBuffer(m_target, 0);
		}

	private:
		GLenum m_target;

	};

} // QuestGLCore::Traits 