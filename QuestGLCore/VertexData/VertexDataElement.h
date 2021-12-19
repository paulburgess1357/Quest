#pragma once
#include "QuestGLCore/Handle/Template/HandleTemplate.h"
#include "QuestGLCore/Handle/Traits/Vao.h"
#include "QuestGLCore/Handle/Traits/Buffer.h"
#include <glad/glad.h>
#include <numeric>

namespace QuestGLCore::VertexData {

	template<GLenum VBOTarget = GL_ARRAY_BUFFER, GLenum EBOTarget = GL_ELEMENT_ARRAY_BUFFER>
	class VertexDataElement {

	public:
		void bind() const {
			m_vao.bind();
		}

		void unbind() const {
			m_vao.unbind();
		}

		template<typename T = float, GLenum GLType = GL_FLOAT, GLenum DrawType = GL_STATIC_DRAW>
		void load_data(const std::vector<T>& input_data, const std::vector<unsigned int>& indices, const std::vector<int>& vertex_description) {
			bind_data();

			// Store data
			glBufferData(VBOTarget, static_cast<Typedefs::GLSizePtr>(sizeof(T) * input_data.size()), input_data.data(), DrawType);

			// Store indices
			glBufferData(EBOTarget, static_cast<Typedefs::GLSizePtr>(sizeof(unsigned int) * indices.size()), indices.data(), DrawType);

			// Describe attributes (for shader)
			const int column_num = std::accumulate(vertex_description.begin(), vertex_description.end(), 0);
			const auto stride = static_cast<Typedefs::GLSize>(column_num * sizeof(T));
			unsigned int offset = 0;

			for (int i = 0; i < static_cast<int>(vertex_description.size()); i++) {
				glVertexAttribPointer(i, vertex_description.at(i), GLType, GL_FALSE, stride, (void*)(offset * sizeof(T)));
				glEnableVertexAttribArray(i);
				offset += vertex_description.at(i);
			}

			unbind_data();
			m_vertex_count = static_cast<QuestGLCore::Typedefs::GLSize>(input_data.size()) / column_num;
			m_index_count = static_cast<Typedefs::GLSize>(indices.size());
		}

	private:
		void bind_data() const {
			bind();
			m_vbo.bind();
			m_ebo.bind();
		}

		void unbind_data() const {
			m_vao.unbind();
			m_vbo.unbind();
			m_ebo.unbind();
		}

		Handle::HandleTemplate<Traits::VAOTraits, Typedefs::GLHandle> m_vao;
		Handle::HandleTemplate<Traits::BufferTraits<VBOTarget>, Typedefs::GLHandle> m_vbo;
		Handle::HandleTemplate<Traits::BufferTraits<EBOTarget>, Typedefs::GLHandle> m_ebo;

		Typedefs::GLSize m_vertex_count{ 0 };
		Typedefs::GLSize m_index_count{ 0 };
	};

} // namespace QuestGlCore::VertexData
