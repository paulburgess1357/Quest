#pragma once
#include "QuestGLCore/Handle/Template/HandleTemplate.h"
#include "QuestGLCore/Handle/Traits/Vao.h"
#include "QuestGLCore/Handle/Traits/Buffer.h"
#include <glad/glad.h>
#include <numeric>

//TODO change handle templatse traits to accept the ogl enum instead of tmeplate parameter?
//TODO that would allow me to pass things like GL_ARRAY_Buffer into the constructor here
//TODO and elsewhere.  I don't think these need to be templated...

namespace QuestGLCore::VertexData {

	template<GLenum VBOTarget = GL_ARRAY_BUFFER>
	class VertexData {

	public:
		void bind() const {
			m_vao.bind();
		}

		void unbind() const {
			m_vao.unbind();
		}

		template<typename T = float, GLenum GLType = GL_FLOAT, GLenum DrawType = GL_STATIC_DRAW>
		void load_data(const std::vector<T>& input_data, const std::vector<int>& vertex_description) {
			bind_data();

			// Store data
			glBufferData(VBOTarget, static_cast<Typedefs::GLSizePtr>(sizeof(T) * input_data.size()), input_data.data(), DrawType);

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
		}

	private:
		void bind_data() const {
			bind();
			m_vbo.bind();
		}

		void unbind_data() const {
			unbind();
			m_vbo.unbind();
		}

		Handle::HandleTemplate<Traits::VAOTraits, Typedefs::GLHandle> m_vao;
		Handle::HandleTemplate<Traits::BufferTraits<VBOTarget>, Typedefs::GLHandle> m_vbo;
		Typedefs::GLSize m_vertex_count{ 0 };

		//GLenum m_array_buffer;
		//GLenum m_draw_type;
	};

} // namespace QuestGlCore::VertexData
