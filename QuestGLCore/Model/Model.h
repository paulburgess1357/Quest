#pragma once
#include "QuestGLCore/Model/Mesh.h"
#include "QuestGLCore/Shader/ShaderProgram.h"
#include "QuestGLCore/Constants/Constants.h"
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
			m_shader_program->set_uniform(QuestGLCore::Constants::model_matrix, m_model_matrix);

			// Set normal matrix =================
			// m_shader_program->set_uniform(QuestGLCore::Constants::normal_matrix, m_normal_matrix);
			// ===================================

			for(const auto& mesh : m_meshes) {
				mesh.draw();
			}

			m_shader_program->unbind();
		}

		[[nodiscard]] Shader::ShaderProgram* get_shader_program() const {
			return m_shader_program;
		}

		[[nodiscard]] glm::mat4 get_model_matrix() const {
			return m_model_matrix;
		}

		void set_model_matrix(const glm::mat4& model_matrix) {
			m_model_matrix = model_matrix;
		}

	private:
		Shader::ShaderProgram* m_shader_program;
		std::vector<Mesh<VertexDataType>> m_meshes;
		glm::mat4 m_model_matrix{ 1.0 };
		glm::mat3 m_normal_matrix{ 1.0 };
	};

} // namespace QuestGLCore::Model

