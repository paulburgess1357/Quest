#pragma once
#include "IImageLoader.h"
#include "ImageExceptions.h"
#include "QuestUtility/Logging/LogMacros.h"
#include <string>

namespace QuestUtility::ImageLoading {

	class HDRImageLoaderFromFile final : public IImageLoaderFromFile {

	public:
		HDRImageLoaderFromFile(const std::string& path, const bool flip_image)
			:IImageLoaderFromFile{ flip_image } {
			HDRImageLoaderFromFile::load_image(path);
			HDRImageLoaderFromFile::check_image_data(path);
		}

		~HDRImageLoaderFromFile() override {
			if(m_image_data) {
				QUEST_TRACE("STBI: Freeing HDR loaded image data")
				stbi_image_free(m_image_data);
			}
		}

		HDRImageLoaderFromFile(const HDRImageLoaderFromFile& source) = delete;
		HDRImageLoaderFromFile(HDRImageLoaderFromFile&& source) = delete;
		HDRImageLoaderFromFile& operator=(const HDRImageLoaderFromFile& rhs) = delete;
		HDRImageLoaderFromFile& operator=(HDRImageLoaderFromFile&& rhs) = delete;

		void load_image(const std::string& path) override {
			m_image_data = stbi_loadf(path.c_str(), &m_width, &m_height, &m_color_channels, 0);
		}

		void check_image_data(const std::string& path) const override {
			if(!m_image_data) {
				QUEST_ERROR("Failed to load image data for texture: " + path)
				throw ImageLoadFromFileException();
			}
		}

		[[nodiscard]] float* get_image_data() const {
			return m_image_data;
		}

	private:
		float* m_image_data{ nullptr };
	};

} // namespace QuestUtility::ImageLoading