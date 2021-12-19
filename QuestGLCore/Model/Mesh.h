#pragma once
#include "QuestGLCore/Shader/ShaderProgram.h"

namespace QuestGLCore::Model {

	template<typename T>
	class Mesh {

	public:
		Mesh(const Shader::ShaderProgram& shader_program, const T& vertex_data)
			:m_shader_program{ &shader_program }, m_vertex_data{ &vertex_data } {
		}

		const Shader::ShaderProgram* m_shader_program;
		const T* m_vertex_data;
	};

} // namespace QuestGLCore::Model 
