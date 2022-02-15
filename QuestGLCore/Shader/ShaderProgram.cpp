#include "pch.h"
#include "ShaderProgram.h"
#include "QuestGLCore/UniformBufferObjects/UniformBufferExceptions.h"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <unordered_set>

namespace QuestGLCore::Shader {

	ShaderProgram::ShaderProgram(std::string program_name, const ShaderProgramCreator& shader_creator)
		:m_program_name{ std::move(program_name) },
		m_handle{ shader_creator.create() } {
		QUEST_TRACE("Shader Program Created: <{}> | Handle: <{}>", m_program_name, m_handle.get_handle());
	}

	void ShaderProgram::bind() const {
		m_handle.bind();
	}

	void ShaderProgram::unbind() const {
		m_handle.unbind();
	}

	void ShaderProgram::set_uniform(const std::string& uniform_name, const int value) {
		glUniform1i(get_uniform(uniform_name), value);
	}

	void ShaderProgram::set_uniform(const std::string& uniform_name, const unsigned int value) {
		glUniform1i(get_uniform(uniform_name), static_cast<int>(value));
	}

	void ShaderProgram::set_uniform(const std::string& uniform_name, const float value) {
		glUniform1f(get_uniform(uniform_name), value);
	}

	void ShaderProgram::set_uniform(const std::string& uniform_name, const glm::vec2& value) {
		glUniform2fv(get_uniform(uniform_name), 1, glm::value_ptr(value));
	}

	void ShaderProgram::set_uniform(const std::string& uniform_name, const glm::vec3& value) {
		glUniform3fv(get_uniform(uniform_name), 1, glm::value_ptr(value));
	}

	void ShaderProgram::set_uniform(const std::string& uniform_name, const glm::vec4& value) {
		glUniform4fv(get_uniform(uniform_name), 1, glm::value_ptr(value));
	}

	void ShaderProgram::set_uniform(const std::string& uniform_name, const glm::mat3& value) {
		glUniformMatrix3fv(get_uniform(uniform_name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void ShaderProgram::set_uniform(const std::string& uniform_name, const glm::mat4& value) {
		glUniformMatrix4fv(get_uniform(uniform_name), 1, GL_FALSE, glm::value_ptr(value));
	}

	GLint ShaderProgram::get_uniform(const std::string& uniform_name) {
		if (const auto it = m_uniform_locations.find(uniform_name); it == m_uniform_locations.end()) {
			m_uniform_locations[uniform_name] = glGetUniformLocation(m_handle.get_handle(), uniform_name.c_str());
			if (m_uniform_locations[uniform_name] == -1) {
				QUEST_ERROR("Invalid uniform variable name: '" + uniform_name + "'. This variable has not been found in the current shader (GLSL Code): " + m_program_name)
				// throw UniformNotFoundException();
			}
		}
		return m_uniform_locations[uniform_name];
	}

	void ShaderProgram::check_uniforms_initialized() const {

		// Looks at all of the uniform variables in the shader and compares them to
		// the set uniforms in the m_uniform_locations map.  If a uniform does
		// not exist in the map, it means we have not initialized the GLSL uniform

		// This check is meant to be performed prior to the gameloop
		const std::unordered_set ignore_strings = {QuestGLCore::Constants::model_matrix, QuestGLCore::Constants::normal_matrix, QuestGLCore::Constants::view_matrix, Constants::projection_matrix};

		GLint count, size;
		GLenum type;
		GLsizei length;

		glGetProgramiv(m_handle.get_handle(), GL_ACTIVE_UNIFORMS, &count);

		for (GLint i = 0; i < count; i++) {
			constexpr GLsizei bufSize = 64;
			GLchar name[bufSize];

			glGetActiveUniform(m_handle.get_handle(), i, bufSize, &length, &size, &type, name);
			if (const std::string name_str{ name }; ignore_strings.count(name_str) == 0) {
				QUEST_ASSERT(m_uniform_locations.count(name_str) != 0, "The variable: " + name_str + " exists in your GLSL (ShaderProgram: " + m_program_name + ") code, but has not been set via set_uniform()!")
			}
		}

	}

	void ShaderProgram::link_shader_to_ubo(const UniformBufferObjects::UniformBufferObject& ubo) const {
		const GLuint shader_ubo_location = glGetUniformBlockIndex(m_handle.get_handle(), ubo.get_uniform_id().c_str());
		if(shader_ubo_location == GL_INVALID_INDEX) {
			QUEST_ERROR("The UBO ID: " + ubo.get_uniform_id() + " has not been found in the GLSL shader code! Are you sure this is the correct name for the uniform buffer object (set via std140)?")
			throw UniformBufferObjects::UniformBufferVariableNotFound();
		}
		glUniformBlockBinding(m_handle.get_handle(), shader_ubo_location, ubo.get_binding_point());
	}

} // namespace QuestGLCore::ShaderProgram