#pragma once
#include "QuestGLCore/VertexData/VertexData.h"
#include "QuestGLCore/VertexData/VertexDataElement.h"

namespace QuestGLCore::Model {

	template<typename T>
	class Mesh {

	public:
		explicit Mesh(T vertex_data)
			:m_vertex_data{ std::move(vertex_data) } {
		}

		void draw(const GLenum draw_mode) const {
			// Bind materials
			// Bind textures
			m_vertex_data.draw(draw_mode);
			// Unbind materials
			// Unbind textures
		}

	private:
		T m_vertex_data;
	};

} // namespace QuestGLCore::Model 
