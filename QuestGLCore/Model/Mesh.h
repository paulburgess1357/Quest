#pragma once
#include "QuestGLCore/Shader/ShaderProgram.h"
#include "QuestGLCore/VertexData/Typedefs.h"

namespace QuestGLCore::Model {

	template<typename T>
	class Mesh {

	public:
		Mesh(const Shader::ShaderProgram& shader_program, const T& vertex_data)
			:m_shader_program{ &shader_program }, m_vertex_data{ &vertex_data } {
		}

		void bind() {
			m_shader_program->bind();
			m_vertex_data->bind();
		}
		void unbind() {
			m_vertex_data->unbind();
			m_shader_program->unbind();
		}

		void draw(const GLenum draw_mode) {
			glDrawArrays(draw_mode, 0, m_vertex_data->m_vertex_count);
		}

	protected:
		const Shader::ShaderProgram* m_shader_program;
		const T* m_vertex_data;
	};

	// Specialized (Indexed mesh draw call)
	template<>
	inline void Mesh<Typedefs::VertexElement>::draw(const GLenum draw_mode) {
		glDrawElements(draw_mode, m_vertex_data->m_index_count, GL_UNSIGNED_INT, 0);
	}

} // namespace QuestGLCore::Model 
