#include "pch.h"
#include "FileToString.h"
#include "QuestUtility/Filepath/InvalidFilePathException.h"
#include <fstream>
#include <sstream>

std::string QuestUtility::String::FileToString::load(const std::string& filepath) {
	std::stringstream ss;
	if(const std::ifstream file { filepath }) {
		ss << file.rdbuf();
	} else {
		throw Filepath::InvalidFilePathException();
	}
	return ss.str();
}
