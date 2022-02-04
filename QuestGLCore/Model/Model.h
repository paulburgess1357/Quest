#pragma once
#include "QuestGLCore/Model/Mesh.h"
#include "QuestGLCore/Shader/ShaderProgram.h"
#include <glm/glm.hpp>

namespace QuestGLCore::Model {

	template<typename VertexDataType>
	class Model {

	public:
		Model(Shader::ShaderProgram& shader_program, std::vector<Mesh<VertexDataType>> meshes)
			:m_shader_program{ &shader_program },
			m_meshes { std::move(meshes) } {
		}

		void draw() const {
			m_shader_program->bind();
			m_shader_program->set_uniform("model_matrix", m_model_matrix);


			// Set normal matrix


			for(const auto& mesh : m_meshes) {
				mesh.draw();
			}

			m_shader_program->unbind();
		}

	private:
		Shader::ShaderProgram* m_shader_program;
		std::vector<Mesh<VertexDataType>> m_meshes;
		glm::mat4 m_model_matrix{ 1.0 };
		glm::mat3 m_normal_matrix{ 1.0 };
	};

} // namespace QuestGLCore::Model

