#pragma once
#include "QuestGLCore/Model/Mesh.h"
#include "QuestGLCore/Shader/ShaderProgram.h"
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace QuestGLCore::Model {

	template<typename VertexDataType>
	class Model {

	public:
		Model(const Shader::ShaderProgram& shader_program, std::vector<Mesh<VertexDataType>> meshes)
			:m_shader_program{ &shader_program },
			m_meshes { std::move(meshes) } {
		}

		void draw(const GLenum draw_mode) const {
			m_shader_program->bind();
			// Set model matrix
			// Set normal matrix
			for(const auto& mesh : m_meshes) {
				mesh.draw(draw_mode);
			}

			m_shader_program->unbind();
		}

	private:
		const Shader::ShaderProgram* m_shader_program;
		std::vector<Mesh<VertexDataType>> m_meshes;
		glm::mat4 m_model_matrix{ 1.0 };
		glm::mat3 m_normal_matrix{ 1.0 };
	};

} // namespace QuestGLCore::Model

