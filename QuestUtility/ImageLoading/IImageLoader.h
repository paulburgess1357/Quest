#pragma once
#include "STBI.h"
#include <string>

namespace QuestUtility::ImageLoading {

	class IImageLoaderFromFile {

	public:
		explicit IImageLoaderFromFile(const bool flip_image) {
			stbi_set_flip_vertically_on_load(flip_image);
		}
		virtual ~IImageLoaderFromFile() = default;

		IImageLoaderFromFile(const IImageLoaderFromFile& source) = delete;
		IImageLoaderFromFile(IImageLoaderFromFile&& source) = delete;
		IImageLoaderFromFile& operator=(const IImageLoaderFromFile& rhs) = delete;
		IImageLoaderFromFile& operator=(IImageLoaderFromFile&& rhs) = delete;

		[[nodiscard]] int get_width() const {
			return m_width;
		}

		[[nodiscard]] int get_height() const {
			return m_height;
		}

		[[nodiscard]] int get_color_channel_num() const {
			return m_color_channels;
		}

	protected:
		virtual void load_image(const std::string& path) = 0;
		virtual void check_image_data(const std::string& path) const = 0;

		int m_width { 0 };
		int m_height { 0 };
		int m_color_channels { 0 };

	};

} // QuestUtility::ImageLoading