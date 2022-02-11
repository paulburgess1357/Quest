#pragma once
#include "QuestGLCore/Texture/Typedefs.h"
#include "QuestUtility/ImageLoading/HDRImageLoader.h"
#include "QuestUtility/ImageLoading/StandardImageLoader.h"

namespace QuestGLCore::Texture {

	enum class TextureType {
		StandardTexture,
		HDRTexture
	};

	class OpenGL2DTextureCreator {

	public:
		TextureHandle load_texture(const QuestUtility::ImageLoading::StandardImageLoaderFromFile& image_loader, const bool apply_linear_correction);
		TextureHandle load_texture(const QuestUtility::ImageLoading::HDRImageLoaderFromFile& image_loader);

	private:
		void set_texture_metadata(const QuestUtility::ImageLoading::IImageLoaderFromFile& image_loader);

		void load_standard_texture(const QuestUtility::ImageLoading::StandardImageLoaderFromFile& image_loader, const bool apply_linear_correction);
		static void set_standard_texture_parameters();

		void load_hdr_texture(const QuestUtility::ImageLoading::HDRImageLoaderFromFile& image_loader);
		static void set_hdr_texture_parameters();

		int m_color_channel_num { 0 };
		int m_width { 0 };
		int m_height{ 0 };
		GLint m_internal_format{ 0 };
		GLint m_pixel_format { 0 };
	};

} // namespace OpenGLTextureCreator