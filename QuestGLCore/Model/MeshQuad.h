#pragma once
#include "QuestGLCore/Model/Mesh.h"
#include "QuestGLCore/VertexData/VertexDataElement.h"

namespace QuestGLCore::Model {

	class IndexedMeshQuad {
	public:
		IndexedMeshQuad() {
			init_quad();
		}
		void draw() const {
			m_mesh->draw();
		}

	private:
		void init_quad() {
			const std::vector<unsigned int> indices = {
				0, 1, 3,
				1, 2, 3
			};

			const std::vector<float> vertices = {
				// positions   // tex_coords
				-1.0f,  1.0f,  0.0f, 1.0f,
				-1.0f, -1.0f,  0.0f, 0.0f,
				 1.0f, -1.0f,  1.0f, 0.0f,
				 1.0f,  1.0f,  1.0f, 1.0f
			};

			VertexData::IndexedVertexData vertex_data_element{ GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_TRIANGLES };
			vertex_data_element.load_data(vertices, indices, { 2, 2 });
			m_mesh = std::make_unique<Mesh<VertexData::IndexedVertexData>>(std::move(vertex_data_element));
		}
		std::unique_ptr<Mesh<VertexData::IndexedVertexData>> m_mesh;

	};

} // namespace QuestGLCore::Model