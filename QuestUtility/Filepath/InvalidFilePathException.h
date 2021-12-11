#pragma once
#include <exception>

namespace QuestUtility::Filepath {
	class InvalidFilePathException final : public std::exception {
		[[nodiscard]] const char* what() const override {
			return "Invalid Filepath";
		}
	};
} // namespace QuestWindow
