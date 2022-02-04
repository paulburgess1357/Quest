#pragma once
#include <exception>

namespace QuestEngine::API::OpenGL {

	class IndexedModelLoaderError final : public std::exception {
		[[nodiscard]] const char* what() const override {
			return "Unable to load indexed model!";
		}
	};



} // namespace QuestEngine::API::OpenGL