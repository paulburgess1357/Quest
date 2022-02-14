#pragma once
#include "QuestGLCore/OpenGLTypes/OpenGLFunctionResolution.h"
#include <glad/glad.h>

namespace QuestGLCore::Texture {

	template<GLenum TextureType>
	class BlankTextureCreator {

	public:
		BlankTextureCreator() = default;
		virtual ~BlankTextureCreator() = default;
		BlankTextureCreator(const BlankTextureCreator& source) = delete;
		BlankTextureCreator(BlankTextureCreator&& source) = delete;
		BlankTextureCreator& operator=(const BlankTextureCreator& rhs) = delete;
		BlankTextureCreator& operator=(BlankTextureCreator&& rhs) = delete;

		[[nodiscard]] TextureHandle generate_texture(const int width, const int height) const {
			TextureHandle handle{ TextureType };
			handle.bind();
			set_parameters();
			load_texture(width, height);
			handle.unbind();
			return handle;
		}

		void rescale_texture(const TextureHandle& handle, const int width, const int height) const {
			handle.bind();
			load_texture(width, height);
			handle.unbind();
		}

	protected:
		virtual void set_parameters() const = 0;
		virtual void load_texture(const int width, const int height) const = 0;
	};

	// ============================== Framebuffer ==============================

	// Standard Framebuffer
	template<GLenum TextureType>
	class StandardBlankFramebufferTextureCreator final : public BlankTextureCreator<TextureType> {

	public:
		StandardBlankFramebufferTextureCreator()
			:BlankTextureCreator<TextureType>() {
		}
		void set_parameters() const override {
			glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		void load_texture(const int width, const int height) const override {
			// Typically: glTexImage2D when TextureType = GL_TEXTURE_2D
			const auto glTextureFunction = OGLResolution::OglTextureFunctionResolution::get_function<TextureType>();
			glTextureFunction(TextureType, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}
	};

	// HD16F Framebuffer
	template<GLenum TextureType>
	class HD16FBlankFramebufferTextureCreator final : public BlankTextureCreator<TextureType> {

	public:
		HD16FBlankFramebufferTextureCreator()
			:BlankTextureCreator<TextureType>() {
		}
		void set_parameters() const override {
			glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		void load_texture(const int width, const int height) const override {
			// Typically: glTexImage2D when TextureType = GL_TEXTURE_2D
			const auto glTextureFunction = OGLResolution::OglTextureFunctionResolution::get_function<TextureType>();
			glTextureFunction(TextureType, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
		}
	};

	// HD32F Framebuffer
	template<GLenum TextureType>
	class HD32FBlankFramebufferTextureCreator final : public BlankTextureCreator<TextureType> {

	public:
		HD32FBlankFramebufferTextureCreator()
			:BlankTextureCreator<TextureType>(){
		}
		void set_parameters() const override {
			glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		void load_texture(const int width, const int height) const override {
			// Typically: glTexImage2D when TextureType = GL_TEXTURE_2D
			const auto glTextureFunction = OGLResolution::OglTextureFunctionResolution::get_function<TextureType>();
			glTextureFunction(TextureType, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
		}
	};

} // namespace QuestGLCore::Texture