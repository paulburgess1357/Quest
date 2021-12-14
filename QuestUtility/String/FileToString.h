#pragma once
#include <string>

namespace QuestUtility::String {

	class FileToString {
	public:
		static std::string load(const std::string& filepath);
	};

} // namespace QuestUtility::String