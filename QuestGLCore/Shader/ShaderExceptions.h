#pragma once
#include <exception>

namespace QuestGLCore::Shader {

	class ShaderCompileTypeException final : public std::exception {
		[[nodiscard]] const char* what() const override {
			return "Unknown shader type being used for shader compilation!";
		}
	};

	class ShaderCompileException final : public std::exception {
		[[nodiscard]] const char* what() const override {
			return "ShaderProgram failed to compile!";
		}
	};

	class ShaderLinkException final : public std::exception {
		[[nodiscard]] const char* what() const override {
			return "ShaderProgram failed to link!";
		}
	};

	class UniformNotFoundException final : public std::exception {
		[[nodiscard]] const char* what() const override {
			return "Uniform does not exist in the GLSL ShaderProgram code!";
		}
	};

} // namespace QuestGLCore::ShaderProgram