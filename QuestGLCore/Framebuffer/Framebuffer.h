#pragma once
#include "QuestGLCore/Framebuffer/Typedefs.h"
#include "QuestGLCore/Texture/Typedefs.h"
#include "QuestGLCore/Texture/BlankTextureCreator.h"

// Framebuffer must be bound
//   - glFramebufferTexture1D/2D/3D etc.
//   - glFramebufferRenderbuffer

// Renderbuffer must be bound
//   - glRenderbufferStorage

// Texture must be bound
//   - glTexImage1D/2D/3D etc.

namespace QuestGLCore::Framebuffer {

	template <template<GLenum> class FramebufferType, GLenum TextureType>
	class Framebuffer {

	public:
		explicit Framebuffer(const int width, const int height, const int color_attachment_num)
			:m_framebuffer_handle{ GL_FRAMEBUFFER },
			m_renderbuffer_handle{ GL_RENDERBUFFER },
			m_color_attachment_num{ 0 }{
			create_color_attachments(width, height, color_attachment_num);
			create_renderbuffer_attachment(width, height);
			check_for_completeness();
			glViewport(0, 0, width, height);
		}
		void bind() const {
			m_framebuffer_handle.bind();
		}
		void unbind() const {
			m_framebuffer_handle.unbind();
		}

		void create_color_attachments(const int width, const int height, const int quantity) {
			for (int i = 0; i < quantity; i++) {
				create_color_attachment(width, height);
			}
		}

		void rescale_attachments(const int width, const int height) {
			rescale_color_attachments(width, height);
			rescale_renderbuffer_attachment(width, height);
			glViewport(0, 0, width, height);
		}

	private:
		void create_color_attachment(const int width, const int height) {
			auto texture_handle = m_blank_texture_creator.generate_texture(width, height);

			const auto framebuffer_target = m_framebuffer_handle.get_trait().get_target();
			// Typically glFramebufferTexture2D & GL_TEXTURE_2D
			auto glTextureFunction = OGLResolution::OglFramebufferFunctionResolution::get_function<TextureType>();

			m_framebuffer_handle.bind();
				glTextureFunction(framebuffer_target, GL_COLOR_ATTACHMENT0 + m_color_attachment_num, TextureType, texture_handle.get_handle(), 0);
			m_framebuffer_handle.unbind();

			m_color_attachment_handles.push_back(std::move(texture_handle));
			++m_color_attachment_num;
		}

		void rescale_color_attachments(const int width, const int height) {
			// Color attachments are created starting from 0 (see create color attachment).  This takes each texture handle and updates
			// each color attachment to be resized.  We don't need to store 'm_color_attachment_num' because we store the handles
			// in a vector, so the order starting from 0 is maintained.  E.g. <texture handle for attachment 0, texture handle for attachment 1, etc.>
			unsigned int color_attachment_num{ 0 };
			const auto framebuffer_target = m_framebuffer_handle.get_trait().get_target();

			for (const auto& color_attachment : m_color_attachment_handles) {
				// Texture rescale handles its own bind()
				m_blank_texture_creator.rescale_texture(color_attachment.get_handle(), width, height);
				// Get texture creation function and use to update width and height
				// Typically glFramebufferTexture2D & GL_TEXTURE_2D
				auto glTextureFunction = OGLResolution::OglFramebufferFunctionResolution::get_function<TextureType>();
				m_framebuffer_handle.bind();
					glTextureFunction(framebuffer_target, GL_COLOR_ATTACHMENT0 + color_attachment_num, TextureType, color_attachment.get_handle(), 0);
				m_framebuffer_handle.unbind();
				++color_attachment_num;
			}

		}

		void create_renderbuffer_attachment(const int width, const int height) const {
			// Depth and stencil attachments (24bit depth; 8bit stencil); Write-only 
			const auto renderbuffer_target = m_renderbuffer_handle.get_trait().get_target();
			const auto framebuffer_target = m_framebuffer_handle.get_trait().get_target();

			m_renderbuffer_handle.bind();
				glRenderbufferStorage(renderbuffer_target, GL_DEPTH24_STENCIL8, width, height);
			m_renderbuffer_handle.unbind();

			m_framebuffer_handle.bind();
				glFramebufferRenderbuffer(framebuffer_target, GL_DEPTH_STENCIL_ATTACHMENT, renderbuffer_target, m_renderbuffer_handle.get_handle());
			m_framebuffer_handle.unbind();
		}

		void rescale_renderbuffer_attachment(const int width, const int height) const {
			m_renderbuffer_handle.bind();
				glRenderbufferStorage(m_renderbuffer_handle.get_trait().get_target(), GL_DEPTH24_STENCIL8, width, height);
			m_renderbuffer_handle.unbind();
		}

		void check_for_completeness() const {
			m_framebuffer_handle.bind();
			const GLenum framebuffer_status = glCheckFramebufferStatus(m_framebuffer_handle.get_trait().get_target());
			if (framebuffer_status != GL_FRAMEBUFFER_COMPLETE) {
				std::string error;
				switch (framebuffer_status) {
					case GL_FRAMEBUFFER_UNDEFINED:
						error = "GL_FRAMEBUFFER_UNDEFINED";
						break;
					case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
						error = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
						break;
					case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
						error = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
						break;
					case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
						error = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
						break;
					case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
						error = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
						break;
					case GL_FRAMEBUFFER_UNSUPPORTED:
						error = "GL_FRAMEBUFFER_UNSUPPORTED";
						break;
					case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
						error = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
						break;
					case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
						error = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS ";
						break;
					default:
						error = "Unknown Framebuffer Error!";
						break;
					}
				QUEST_ERROR("Framebuffer completeness check failed! Error: {}", error);
			}
			m_framebuffer_handle.unbind();
		}

		FramebufferHandle m_framebuffer_handle;
		RenderbufferHandle m_renderbuffer_handle; // Stencil & depth
		std::vector<Texture::TextureHandle> m_color_attachment_handles; // Color

		FramebufferType<TextureType> m_blank_texture_creator;
		unsigned int m_color_attachment_num;

	};

} // namespace QuestGLCore::Framebuffer