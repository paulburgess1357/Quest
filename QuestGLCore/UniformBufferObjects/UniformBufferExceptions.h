#pragma once
#include <exception>

namespace QuestGLCore::UniformBufferObjects {

	class UniformBufferSendDataTypeException final : public std::exception {
		[[nodiscard]] const char* what() const override {
			return "You are sending an invalid data type to the uniform buffer!";
		}
	};

	class UniformBufferVariableNotFound final : public std::exception {
		[[nodiscard]] const char* what() const override {
			return "Unable to locate named uniform buffer in glsl code!";
		}
	};

} // namespace QuestGLCore::ShaderProgram#pragma once
