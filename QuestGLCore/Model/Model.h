#pragma once
#include "QuestGLCore/Model/Mesh.h"

namespace QuestGLCore::Model {

	template<typename VertexDataType>
	class Model {

	public:
		explicit Model(std::vector<Mesh<VertexDataType>> meshes)
			:m_meshes { std::move(meshes) } {
		}

		void draw() const {
			for(const auto& mesh : m_meshes) {
				mesh.draw();
			}
		}

		[[nodiscard]] std::vector<Mesh<VertexDataType>>& get_mesh_vector() {
			return m_meshes;
		}

	private:
		std::vector<Mesh<VertexDataType>> m_meshes;
	};

} // namespace QuestGLCore::Model

