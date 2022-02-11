#pragma once
#include "IImageLoader.h"
#include "ImageExceptions.h"
#include "QuestUtility/Include/Logger.h"
#include <string>

namespace QuestUtility::ImageLoading {

	class StandardImageLoaderFromFile final : public IImageLoaderFromFile {

	public:
		StandardImageLoaderFromFile(const std::string& path, const bool flip_image)
			:IImageLoaderFromFile{ flip_image } {
			StandardImageLoaderFromFile::load_image(path);
			StandardImageLoaderFromFile::check_image_data(path);
		}

		~StandardImageLoaderFromFile() override {
			if(m_image_data) {
				QUEST_TRACE("STBI: Freeing loaded image data")
				stbi_image_free(m_image_data);
			}
		}

		StandardImageLoaderFromFile(const StandardImageLoaderFromFile& source) = delete;
		StandardImageLoaderFromFile(StandardImageLoaderFromFile&& source) = delete;
		StandardImageLoaderFromFile& operator=(const StandardImageLoaderFromFile& rhs) = delete;
		StandardImageLoaderFromFile& operator=(StandardImageLoaderFromFile&& rhs) = delete;

		void load_image(const std::string& path) override {
			m_image_data = stbi_load(path.c_str(), &m_width, &m_height, &m_color_channels, 0);
		}

		void check_image_data(const std::string& path) const override {
			if(!m_image_data) {
				QUEST_ERROR("Failed to load image data for texture: " + path)
				throw ImageLoadFromFileException();
			}
		}

		[[nodiscard]] unsigned char* get_image_data() const {
			return m_image_data;
		}

	private:
		unsigned char* m_image_data{ nullptr };
	};

} // namespace QuestUtility::ImageLoading