#include "pch.h"
#include "OpenGL2DTextureCreator.h"
#include "OpenGLTextureFormat.h"


namespace QuestGLCore::Texture {

	TextureHandle OpenGL2DTextureCreator::load_texture(const QuestUtility::ImageLoading::StandardImageLoaderFromFile& image_loader, const bool apply_linear_correction) {
		TextureHandle handle{ GL_TEXTURE_2D };
		handle.bind();

		set_standard_texture_parameters();
		load_standard_texture(image_loader, apply_linear_correction);
		glGenerateMipmap(GL_TEXTURE_2D);

		handle.unbind();
		return handle;
	}

	TextureHandle OpenGL2DTextureCreator::load_texture(const QuestUtility::ImageLoading::HDRImageLoaderFromFile& image_loader) {
		TextureHandle handle{ GL_TEXTURE_2D };
		handle.bind();

		set_hdr_texture_parameters();
		load_hdr_texture(image_loader);

		handle.unbind();
		return handle;
	}

	void OpenGL2DTextureCreator::set_texture_metadata(const QuestUtility::ImageLoading::IImageLoaderFromFile& image_loader) {
		m_color_channel_num = image_loader.get_color_channel_num();
		m_width = image_loader.get_width();
		m_height = image_loader.get_height();
		m_internal_format = OpenGLTextureFormat::get_internal_format(m_color_channel_num);
		m_pixel_format = OpenGLTextureFormat::get_pixel_format(m_color_channel_num);
	}

	void OpenGL2DTextureCreator::load_standard_texture(const QuestUtility::ImageLoading::StandardImageLoaderFromFile& image_loader, const bool apply_linear_correction) {
		set_texture_metadata(image_loader);
		if (apply_linear_correction) {
			// When internal format equals: SRGB: OpenGL will correct the colors
			// to linear space as soon as they are loaded.  This is typically done
			// for diffuse and other coloring maps (not normal/specular maps)
			glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, m_pixel_format, GL_UNSIGNED_BYTE, image_loader.get_image_data());
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, m_pixel_format, m_width, m_height, 0, m_pixel_format, GL_UNSIGNED_BYTE, image_loader.get_image_data());
		}
	}

	void OpenGL2DTextureCreator::load_hdr_texture(const QuestUtility::ImageLoading::HDRImageLoaderFromFile& image_loader) {
		set_texture_metadata(image_loader);
		m_pixel_format = OpenGLTextureFormat::get_pixel_format(m_color_channel_num);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, m_width, m_height, 0, m_pixel_format, GL_FLOAT, image_loader.get_image_data()); //TODO need to handle RGBA 16f version? need to create function that gives internal format as well.  Also, i guess there is no gamma correction for hdr images?
	}

	void OpenGL2DTextureCreator::set_standard_texture_parameters() {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void OpenGL2DTextureCreator::set_hdr_texture_parameters() {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}



} // namespace OpenGLTextureCreator