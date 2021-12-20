// ReSharper disable CppCStyleCast
#pragma once
#include "QuestGLCore/Handle/Template/HandleTemplate.h"
#include "QuestGLCore/Handle/Traits/Vao.h"
#include "QuestGLCore/Handle/Traits/Buffer.h"
#include "QuestGLCore/OpenGLTypes/OglTypeResolution.h"
#include <glad/glad.h>
#include <numeric>

namespace QuestGLCore::VertexData {

	class VertexData {

	public:
		explicit VertexData(const GLenum vbo_target)
			:m_vbo_target{ vbo_target },
			m_vbo{ m_vbo_target } {
		}

		void draw(const GLenum draw_mode) const {
			m_vao.bind();
			glDrawArrays(draw_mode, 0, m_vertex_count);
			m_vao.unbind();
		}

		Typedefs::GLSize get_vertex_count() const {
			return m_vertex_count;
		}

		template<typename T = float>
		void load_data(const std::vector<T>& input_data, const std::vector<int>& vertex_description, const GLenum draw_usage = GL_STATIC_DRAW) {
			m_vao.bind();
			m_vbo.bind();

			// Store data
			glBufferData(m_vbo_target, static_cast<Typedefs::GLSizePtr>(sizeof(T) * input_data.size()), input_data.data(), draw_usage);

			// Describe attributes (for shader)
			const int column_num = std::accumulate(vertex_description.begin(), vertex_description.end(), 0);
			const auto stride = static_cast<Typedefs::GLSize>(column_num * sizeof(T));
			unsigned int offset = 0;
			const GLenum gl_type = OglTypeResolution::get_type<T>();

			for (int i = 0; i < static_cast<int>(vertex_description.size()); i++) {
				glVertexAttribPointer(i, vertex_description.at(i), gl_type, GL_FALSE, stride, (void*)(offset * sizeof(T)));
				glEnableVertexAttribArray(i);
				offset += vertex_description.at(i);
			}

			m_vao.unbind();
			m_vbo.unbind();
			m_vertex_count = static_cast<QuestGLCore::Typedefs::GLSize>(input_data.size()) / column_num;
		}

	private:
		GLenum m_vbo_target;
		Handle::HandleTemplate<Traits::VAOTraits, Typedefs::GLHandle> m_vao;
		Handle::HandleTemplate<Traits::BufferTraits, Typedefs::GLHandle> m_vbo;
		Typedefs::GLSize m_vertex_count{ 0 };

	};

} // namespace QuestGlCore::VertexData
