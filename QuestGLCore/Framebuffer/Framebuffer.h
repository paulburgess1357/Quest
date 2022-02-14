#pragma once
#include "QuestGLCore/Framebuffer/Typedefs.h"
#include "QuestGLCore/Texture/Typedefs.h"
#include "QuestGLCore/Texture/BlankTextureCreator.h"

namespace QuestGLCore::Framebuffer {

	template <template<GLenum> class FramebufferType, GLenum TextureType>
	class Framebuffer {

	public:
		explicit Framebuffer()
			:m_framebuffer_handle{ GL_FRAMEBUFFER },
			m_renderbuffer_handle{ GL_RENDERBUFFER },
			color_attachment_num{ 0 }{
		}
		void bind() const {
			m_framebuffer_handle.bind();
		}
		void unbind() const {
			m_framebuffer_handle.unbind();
		}

		void create_color_attachment(const int width, const int height) {
			//auto texture_handle = m_blank_texture_creator.generate_texture(width, height);
			//texture_handle.bind();

			// Typically glFramebufferTexture2D & GL_TEXTURE_2D
			//auto texture_function = OGLResolution::OglFramebufferFunctionResolution::get_function<TextureType>();
			//texture_function(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + color_attachment_num, TextureType, texture_handle.get_handle(), 0);

			//texture_handle.unbind();
			//m_color_attachment_handles.push_back(std::move(texture_handle));
			//++color_attachment_num;
		}

		void rescale_color_attachments(const int width, const int height) {
			for (const auto& color_attachments : m_color_attachment_handles) {
				// m_blank_texture_creator.rescale_texture(color_attachments.get_handle(), width, height);
			}
		}

	private:
		FramebufferHandle m_framebuffer_handle;
		RenderbufferHandle m_renderbuffer_handle; // Stencil & depth
		std::vector<Texture::TextureHandle> m_color_attachment_handles; // Color

		/*FramebufferType<TextureType> m_blank_texture_creator;*/
		unsigned int color_attachment_num;

	};

} // namespace QuestGLCore::Framebuffer