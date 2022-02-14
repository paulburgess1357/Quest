#pragma once
#include "QuestGLCore/Framebuffer/Typedefs.h"
#include "QuestGLCore/Texture/Typedefs.h"
#include "QuestGLCore/Texture/BlankTextureCreator.h"
#include "QuestUtility/Include/Logger.h"

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

			// Writing to all color attachments by default
			// This has no effect if the Framebuffer is initialized with 0
			// attachment nums
			set_all_color_attachments_to_write_to();
		}

		void bind_scene_attachment() const {
			// By default the main scene will be used for color attachment 0;
			// color attachment 0, tex unit 0
			bind_color_attachment(0, 0);
		}

		void bind() const {
			m_framebuffer_handle.bind();
		}

		void unbind() const {
			m_framebuffer_handle.unbind();
		}

		void clear_buffer() const {
			bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			unbind();
		}

		void create_color_attachments(const int width, const int height, const int quantity) {
			for (int i = 0; i < quantity; i++) {
				create_color_attachment(width, height);
			}
		}

		void rescale_attachments(const int width, const int height) const {
			rescale_color_attachments(width, height);
			rescale_renderbuffer_attachment(width, height);
			glViewport(0, 0, width, height);
		}

		void set_single_color_attachment_to_write_to(const unsigned int color_attachment_num) const {
			// Output information from fragment shader into a single specified color attachment.
			// When this is set, any previous color attachments that are being written to will no
			// longer be written to.  Only the single specified color attachment will be used.
			// https://stackoverflow.com/questions/51030120/concept-what-is-the-use-of-gldrawbuffer-and-gldrawbuffers/51030343

			const unsigned int attachment_num = static_cast<unsigned int>(m_color_attachment_handles.size());
			QUEST_ASSERT(color_attachment_num <= attachment_num - 1, "You are setting a framebuffer color attachment to write to that has not yet been created (or is too high based on the current attachment number)!");

			if(color_attachment_num <= attachment_num - 1) {
				bind();
					const GLenum buffers[]{ GL_COLOR_ATTACHMENT0 + color_attachment_num };
					glDrawBuffers(1, buffers);
				unbind();
			}
		}

		void set_all_color_attachments_to_write_to() const {
			// Sets all currently existing color attachments to be used in the fragment shader.
			// If you add a color attachment after this call, you will need to call this function
			// again.
			const unsigned int attachment_num = static_cast<unsigned int>(m_color_attachment_handles.size());
			if(attachment_num > 0) {
				std::vector<GLenum> all_buffers;
				for (unsigned int i = 0; i < attachment_num; i++) {
					all_buffers.push_back(GL_COLOR_ATTACHMENT0 + i);
				}
				bind();
					glDrawBuffers(static_cast<GLsizei>(attachment_num), all_buffers.data());
				unbind();
			}
		}

		void bind_color_attachment(const size_t attachment_num, const GLuint tex_unit) const {
			// Bind color attachment (e.g. for working with the texture data in a post process shader)
			// Note that this does not require the framebuffer to be bound, as we are simply extracting
			// the already drawn data from the texture.  This means the framebuffer must have been
			// previously bound prior to writing to this texture.
			glActiveTexture(GL_TEXTURE0 + tex_unit);
			m_color_attachment_handles.at(attachment_num).bind();
		}

	private:
		void create_color_attachment(const int width, const int height) {
			auto texture_handle = m_blank_texture_creator.generate_texture(width, height);

			const auto framebuffer_target = m_framebuffer_handle.get_trait().get_target();
			// Typically glFramebufferTexture2D & GL_TEXTURE_2D
			const auto glTextureFunction = OGLResolution::OglFramebufferFunctionResolution::get_function<TextureType>();

			bind();
				glTextureFunction(framebuffer_target, GL_COLOR_ATTACHMENT0 + m_color_attachment_num, TextureType, texture_handle.get_handle(), 0);
			unbind();

			m_color_attachment_handles.push_back(std::move(texture_handle));
			++m_color_attachment_num;
		}

		void rescale_color_attachments(const int width, const int height) const {
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
				const auto glTextureFunction = OGLResolution::OglFramebufferFunctionResolution::get_function<TextureType>();
				bind();
					glTextureFunction(framebuffer_target, GL_COLOR_ATTACHMENT0 + color_attachment_num, TextureType, color_attachment.get_handle(), 0);
				unbind();
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

			bind();
				glFramebufferRenderbuffer(framebuffer_target, GL_DEPTH_STENCIL_ATTACHMENT, renderbuffer_target, m_renderbuffer_handle.get_handle());
			unbind();
		}

		void rescale_renderbuffer_attachment(const int width, const int height) const {
			m_renderbuffer_handle.bind();
				glRenderbufferStorage(m_renderbuffer_handle.get_trait().get_target(), GL_DEPTH24_STENCIL8, width, height);
			m_renderbuffer_handle.unbind();
		}

		void check_for_completeness() const {
			bind();
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
				QUEST_FATAL("Framebuffer completeness check failed! Error: {}", error);
			}
			unbind();
		}

		FramebufferHandle m_framebuffer_handle;
		RenderbufferHandle m_renderbuffer_handle; // Stencil & depth
		std::vector<Texture::TextureHandle> m_color_attachment_handles; // Color

		FramebufferType<TextureType> m_blank_texture_creator;
		unsigned int m_color_attachment_num;
	};

} // namespace QuestGLCore::Framebuffer