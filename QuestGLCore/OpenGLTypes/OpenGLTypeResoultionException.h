#pragma once
#include <exception>

namespace QuestGLCore::OGLResolution {

	class OGLTypeResolutionException final : public std::exception {
		[[nodiscard]] const char* what() const override {
			return "Unable to resolve OpenGL type resolution!";
		}
	};

} // namespace QuestGLCore::OGLResolution
