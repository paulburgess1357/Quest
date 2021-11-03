#pragma once
#include <exception>

namespace QuestWindow {
	namespace OpenGL {

		class OGLGladException final : public std::exception {
			[[nodiscard]] const char* what() const override {
				return "Failed to initialize GLAD";
			}
		};

	} // namespace Interface
} // namespace QuestWindow
