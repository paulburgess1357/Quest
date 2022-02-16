#pragma once
#include "QuestGLCore/Model/Mesh.h"

namespace QuestGLCore::Model {

	template<typename VertexDataType>
	class Model {

	public:
		Model(Shader::ShaderProgram& shader_program, std::vector<Mesh<VertexDataType>> meshes)
			:m_shader_program{ &shader_program },
			m_meshes { std::move(meshes) } {
		}

		void draw() const {
			for(const auto& mesh : m_meshes) {
				mesh.draw();
			}
		}

		[[nodiscard]] Shader::ShaderProgram* get_shader_program() const {
			return m_shader_program;
		}

		[[nodiscard]] std::vector<Mesh<VertexDataType>>& get_mesh_vector() {
			return m_meshes;
		}

	private:
		Shader::ShaderProgram* m_shader_program;
		std::vector<Mesh<VertexDataType>> m_meshes;
	};

} // namespace QuestGLCore::Model

