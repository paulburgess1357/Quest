#pragma once
#include "QuestEngine/API/Neutral/ResourceAPI.h"
#include "QuestEngine/Texture/TextureType.h"

namespace QuestEngine::API::OpenGL {

	class TextureLoaderAPI : public ResourceAPI {

	public:
		explicit TextureLoaderAPI(Engine::Engine* engine);

		void load_texture2D(const std::string& texture_path, const Texture::TextureType texture_type, const bool flip_image, const bool apply_linear_correction) const;
		void load_texture2D(const std::string& texture_id, const std::string& texture_path, const Texture::TextureType texture_type, const bool flip_image, const bool apply_linear_correction) const;

	private:
		void load_hdr_texture(const std::string& texture_id, const std::string& texture_path, const bool flip_image, const bool apply_linear_correction) const;
		void load_standard_texture(const std::string& texture_id, const std::string& texture_path, const bool flip_image, const bool apply_linear_correction) const;
	};

} // namespace QuestEngine::API::OpenGL