#pragma once
#include <exception>
#include <iostream>

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

		class IWindowExistsException final : public std::exception {
			[[nodiscard]] const char* what() const override {
				return "Only one window can exist";
			}
		};

	} // namespace Interface
} // namespace QuestWindow