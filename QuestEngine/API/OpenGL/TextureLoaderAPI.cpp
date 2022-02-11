#include "pch.h"
#include "TextureLoaderAPI.h"
#include "QuestUtility/Logging/LogHandler.h"

namespace QuestEngine::API::OpenGL {

	TextureLoaderAPI::TextureLoaderAPI(Engine::Engine* engine)
		:ResourceAPI(engine) {
	}

	void TextureLoaderAPI::load_texture2D(const std::string& texture_path, const Texture::TextureType texture_type, const bool flip_image, const bool apply_linear_correction) const {
		load_texture2D(texture_path, texture_path, texture_type, flip_image, apply_linear_correction);
	}

	void TextureLoaderAPI::load_texture2D(const std::string& texture_id, const std::string& texture_path, const Texture::TextureType texture_type, const bool flip_image, const bool apply_linear_correction) const {
		switch (texture_type) {
			case Texture::TextureType::Standard: {
				load_standard_texture(texture_id, texture_path, flip_image, apply_linear_correction);
				break;
			}
			case Texture::TextureType::HDR: {
				load_hdr_texture(texture_id, texture_path, flip_image, apply_linear_correction);
				break;
			}
			default:  // NOLINT(clang-diagnostic-covered-switch-default)
				QUEST_ERROR("Unknown texture type being loaded into Texture Resource: " + texture_id)
					break;
			}
	}

	void TextureLoaderAPI::load_standard_texture(const std::string& texture_id, const std::string& texture_path, const bool flip_image, const bool apply_linear_correction) const {
		const QuestUtility::ImageLoading::StandardImageLoaderFromFile image_loader{ texture_path, flip_image };
		const Texture::StandardTextureCreator2D texture_creator{ image_loader, apply_linear_correction };
		Texture::Texture texture{ texture_creator.generate_texture() };
		ResourceAPI::load_texture2D(texture_id, texture);
	}

	void TextureLoaderAPI::load_hdr_texture(const std::string& texture_id, const std::string& texture_path, const bool flip_image, const bool apply_linear_correction) const {
		const QuestUtility::ImageLoading::HDRImageLoaderFromFile image_loader{ texture_path, flip_image };
		const Texture::HDRTextureCreator2D texture_creator{ image_loader };
		Texture::Texture texture{ texture_creator.generate_texture() };
		ResourceAPI::load_texture2D(texture_id, texture);
		QUEST_WARN_CONDITION(!apply_linear_correction, "A parameter has been set to apply linear correction to an HDR image.  There is no option to do this.  No linear correction has been applied to: " + texture_id)
	}

} // namespace QuestEngine::API::OpenGL