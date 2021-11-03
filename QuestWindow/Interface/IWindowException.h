#pragma once
#include <exception>

namespace QuestWindow {
	namespace Interface {

		class IWindowInitException final : public std::exception {
			[[nodiscard]] const char* what() const override {
				return "GLFW failed to initialize";
			}
		};

		class IWindowCreationException final : public std::exception {
			[[nodiscard]] const char* what() const override {
				return "Failed to create GLFW window";
			}
		};

	} // namespace Interface
} // namespace QuestWindow