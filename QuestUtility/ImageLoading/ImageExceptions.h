#pragma once
#include <exception>

namespace QuestUtility::ImageLoading {

	class ImageLoadFromFileException final : public std::exception {
		[[nodiscard]] const char* what() const override {
			return "Unable to load texture from file!";
		}
	};

} // namespace QuestUtility::ImageLoading