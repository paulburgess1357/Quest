#include "pch.h"
#include "ShaderProgramCreator.h"
#include "ShaderExceptions.h"
#include <glad/glad.h>
#include <iostream>

namespace QuestGLCore::Shader {

	ShaderProgramCreator::ShaderProgramCreator(const std::unordered_map<ShaderType, std::string>& shader_string_map)
		:m_shader_string_map{ shader_string_map } {
	}

	ShaderProgramHandle ShaderProgramCreator::create() const {

		// Create shader program handle
		ShaderProgramHandle program_handle;
		const Typedefs::HandleTypedef shader_program_handle = program_handle.get_handle();

		// Load GLSL shaders and attach
		std::vector<Typedefs::HandleTypedef> shader_handles;
		for(const auto& [shader_type, shader_string] : m_shader_string_map) {
			const Typedefs::HandleTypedef shader_handle = load_glsl_shader(shader_type, shader_string);
			glAttachShader(shader_program_handle, shader_handle);
			shader_handles.push_back(shader_handle);
		}

		// Link shaders and check for errors:
		glLinkProgram(shader_program_handle);
		check_shader_program(shader_program_handle);

		// Detach individual shader handles and delete:
		for(const auto& shader_handle : shader_handles) {
			glDetachShader(shader_program_handle, shader_handle);
			glDeleteShader(shader_handle);
		}

		return program_handle;
	}

	Typedefs::HandleTypedef ShaderProgramCreator::load_glsl_shader(const ShaderType shader_type, const std::string& shader_string) {

		// ReSharper disable once CppInitializedValueIsAlwaysRewritten
		Typedefs::HandleTypedef shader_handle{ };
		switch (shader_type) {
			case ShaderType::VERTEX: {
				shader_handle = glCreateShader(GL_VERTEX_SHADER);
				break;
			}
			case ShaderType::FRAGMENT: {
				shader_handle = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			}
			case ShaderType::GEOMETRY: {
				shader_handle = glCreateShader(GL_GEOMETRY_SHADER);
				break;
			}
			default:
				throw ShaderCompileTypeException();
		}

		const char* shader_code_ptr = shader_string.c_str();
		glShaderSource(shader_handle, 1, &shader_code_ptr, nullptr);
		glCompileShader(shader_handle);
		check_shader(shader_handle);

		return shader_handle;
	}

	void ShaderProgramCreator::check_shader(const Typedefs::HandleTypedef handle) {
		int success{ 0 };
		glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
		if (!success) {
			int error_length{ 0 };
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &error_length);
			std::string error_string(error_length, ' ');
			glGetShaderInfoLog(handle, error_length, &error_length, &error_string[0]);
			std::cerr << error_string << std::endl;
			throw ShaderCompileException();
		}
	}

	void ShaderProgramCreator::check_shader_program(const Typedefs::HandleTypedef handle) {
		int success{ 0 };
		glGetProgramiv(handle, GL_LINK_STATUS, &success);
		if (!success) {
			int error_length{ 0 };
			glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &error_length);
			std::string error_string(error_length, ' ');
			glGetProgramInfoLog(handle, error_length, &error_length, &error_string[0]);
			throw ShaderLinkException();
		}
	}

} // namespace QuestGLCore::ShaderProgram