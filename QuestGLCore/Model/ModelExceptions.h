#pragma once
#include <exception>

namespace QuestGLCore::Model {

	class IndexedModelCreationException final : public std::exception {
		[[nodiscard]] const char* what() const override {
			return "Unable to create indexed model!";
		}
	};

}
