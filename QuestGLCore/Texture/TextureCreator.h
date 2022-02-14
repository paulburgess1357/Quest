#pragma once
#include "QuestGLCore/Texture/TextureFormat.h"
#include "QuestGLCore/Texture/Typedefs.h"
#include "QuestUtility/ImageLoading/IImageLoader.h"
#include "QuestUtility/ImageLoading/StandardImageLoader.h"
#include "QuestUtility/ImageLoading/HDRImageLoader.h"
#include "QuestGLCore/OpenGLTypes/OpenGLFunctionResolution.h"
#include <glad/glad.h>

namespace QuestGLCore::Texture {

	template<GLenum TextureType>
	class TextureCreator {

	public:
		explicit TextureCreator(const QuestUtility::ImageLoading::IImageLoaderFromFile& image_loader, const bool apply_linear_correction)
			:m_apply_linear_correction{ apply_linear_correction } {
			set_texture_metadata(image_loader);
		}
		virtual ~TextureCreator() = default;
		TextureCreator(const TextureCreator& source) = delete;
		TextureCreator(TextureCreator&& source) = delete;
		TextureCreator& operator=(const TextureCreator& rhs) = delete;
		TextureCreator& operator=(TextureCreator&& rhs) = delete;

		[[nodiscard]] TextureHandle generate_texture() const {
			TextureHandle handle { TextureType };
			handle.bind();
			set_parameters();
			load_texture();
			handle.unbind();
			return handle;
		}

	protected:
		virtual void set_parameters() const = 0;
		virtual void load_texture() const = 0;

		int m_color_channel_num{ 0 };
		int m_width{ 0 };
		int m_height{ 0 };
		GLint m_internal_format{ 0 };
		GLint m_pixel_format{ 0 };
		bool m_apply_linear_correction{ false };

	private:
		void set_texture_metadata(const QuestUtility::ImageLoading::IImageLoaderFromFile& image_loader) {
			m_color_channel_num = image_loader.get_color_channel_num();
			m_width = image_loader.get_width();
			m_height = image_loader.get_height();
			m_internal_format = TextureFormat::get_internal_format(m_color_channel_num);
			m_pixel_format = TextureFormat::get_pixel_format(m_color_channel_num);
		}
	};

	template<GLenum TextureType>
	class StandardTextureCreator final : public TextureCreator<TextureType> {

	public:
		explicit StandardTextureCreator(const QuestUtility::ImageLoading::StandardImageLoaderFromFile& image_loader, const bool apply_linear_correction)
			:TextureCreator<TextureType>{ image_loader, apply_linear_correction },
			m_image_loader{ image_loader }{
		}
	private:
		void set_parameters() const override {
			glTexParameteri(TextureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(TextureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		void load_texture() const override {
			// Typically: glTexImage2D when TextureType = GL_TEXTURE_2D
			const auto texture_function = OGLResolution::OglTextureFunctionResolution::get_function<TextureType>();
			if (this->m_apply_linear_correction) {
				// When internal format equals: SRGB: OpenGL will correct the colors
				// to linear space as soon as they are loaded.  This is typically done
				// for diffuse and other coloring maps (not normal/specular maps)
				texture_function(TextureType, 0, this->m_internal_format, this->m_width, this->m_height, 0, this->m_pixel_format, GL_UNSIGNED_BYTE, m_image_loader.get_image_data());
			} else {
				texture_function(TextureType, 0, this->m_pixel_format, this->m_width, this->m_height, 0, this->m_pixel_format, GL_UNSIGNED_BYTE, m_image_loader.get_image_data());
			}
			glGenerateMipmap(TextureType);
		}

		const QuestUtility::ImageLoading::StandardImageLoaderFromFile& m_image_loader;

	};

	template<GLenum TextureType>
	class HDRTextureCreator final : public TextureCreator<TextureType> {

	public:
		explicit HDRTextureCreator(const QuestUtility::ImageLoading::HDRImageLoaderFromFile& image_loader)
			:TextureCreator<TextureType>{ image_loader, false },
			m_image_loader{ image_loader }{
		}

	private:
		void set_parameters() const override {
			glTexParameteri(TextureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(TextureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		void load_texture() const override {
			// Typically: glTexImage2D when TextureType = GL_TEXTURE_2D
			const auto texture_function = OGLResolution::OglTextureFunctionResolution::get_function<TextureType>();
			texture_function(TextureType, 0, GL_RGB16F, this->m_width, this->m_height, 0, this->m_pixel_format, GL_FLOAT, m_image_loader.get_image_data());
		}

		const QuestUtility::ImageLoading::HDRImageLoaderFromFile& m_image_loader;
		
	};

} // namespace QuestGLCore