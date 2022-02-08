#pragma once
#include "QuestGLCore/Shader/ShaderProgramCreator.h"
#include "QuestGLCore/Shader/Typedefs.h"
#include <glm/glm.hpp>

namespace QuestGLCore::Shader {

	class ShaderProgram {

	public:
		ShaderProgram(std::string program_name, const ShaderProgramCreator shader_creator);
		void bind() const;
		void unbind() const;

		// Single Value Uniforms
		void set_uniform(const std::string& uniform_name, const int value);
		void set_uniform(const std::string& uniform_name, const unsigned int value);
		void set_uniform(const std::string& uniform_name, const float value);

		// Vector Uniforms
		void set_uniform(const std::string& uniform_name, const glm::vec2& value);
		void set_uniform(const std::string& uniform_name, const glm::vec3& value);
		void set_uniform(const std::string& uniform_name, const glm::vec4& value);

		// Matrix Uniforms		
		void set_uniform(const std::string& uniform_name, const glm::mat3& value);
		void set_uniform(const std::string& uniform_name, const glm::mat4& value);

		void check_uniforms_initialized() const;

	private:
		int get_uniform(const std::string& uniform_name);

		std::string m_program_name;
		Typedefs::ShaderProgramHandle m_handle;
		std::unordered_map<std::string, GLint> m_uniform_locations;

	};

} // namespace QuestGLCore::ShaderProgram
