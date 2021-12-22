// ReSharper disable CppCStyleCast
#pragma once
#include "QuestGLCore/Handle/Template/HandleTemplate.h"
#include "QuestGLCore/Handle/Traits/Vao.h"
#include "QuestGLCore/Handle/Traits/Buffer.h"
#include "QuestGLCore/OpenGLTypes/OglTypeResolution.h"
#include <glad/glad.h>
#include <numeric>

namespace QuestGLCore::VertexData {

	class IndexedVertexData {

	public:
		explicit IndexedVertexData(const GLenum vbo_target, const GLenum ebo_target)
			:m_vbo_target{ vbo_target },
			m_ebo_target{ ebo_target },
			m_vbo{ m_vbo_target },
			m_ebo{ m_ebo_target } {
		}

		void draw(const GLenum draw_mode) const {
			m_vao.bind();
			glDrawElements(draw_mode, m_index_count, GL_UNSIGNED_INT, 0);
			m_vao.unbind();
		}

		[[nodiscard]] Typedefs::GLSize get_vertex_count() const {
			return m_vertex_count;
		}

		[[nodiscard]] Typedefs::GLSize get_index_count() const {
			return m_index_count;
		}

		template<typename T = float>
		void load_data(const std::vector<T>& input_data, const std::vector<unsigned int>& indices, const std::vector<int>& vertex_description, const GLenum draw_usage = GL_STATIC_DRAW) {

			m_vao.bind();
			m_vbo.bind();
			m_ebo.bind();

			// Store data
			glBufferData(m_vbo_target, static_cast<Typedefs::GLSizePtr>(sizeof(T) * input_data.size()), input_data.data(), draw_usage);

			// Store indices
			glBufferData(m_ebo_target, static_cast<Typedefs::GLSizePtr>(sizeof(unsigned int) * indices.size()), indices.data(), draw_usage);

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
			m_ebo.unbind();

			m_vertex_count = static_cast<QuestGLCore::Typedefs::GLSize>(input_data.size()) / column_num;
			m_index_count = static_cast<Typedefs::GLSize>(indices.size());
		}

	private:
		GLenum m_vbo_target;
		GLenum m_ebo_target;

		Handle::HandleTemplate<Traits::VAOTraits, Typedefs::GLHandle> m_vao;
		Handle::HandleTemplate<Traits::BufferTraits, Typedefs::GLHandle> m_vbo;
		Handle::HandleTemplate<Traits::BufferTraits, Typedefs::GLHandle> m_ebo;

		Typedefs::GLSize m_vertex_count{ 0 };
		Typedefs::GLSize m_index_count{ 0 };
	};

} // namespace QuestGlCore::VertexData
