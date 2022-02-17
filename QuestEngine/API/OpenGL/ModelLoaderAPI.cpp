#include "pch.h"
#include "ModelLoaderAPI.h"
#include "ModelLoaderExceptions.h"

namespace QuestEngine::API::OpenGL {

	ModelLoaderAPI::ModelLoaderAPI(Engine::Engine* engine)
		:ResourceAPI{ engine } {
	}

	

	void ModelLoaderAPI::check_indexed_vertices_indices(const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<std::vector<unsigned>>& all_mesh_indices) {
		if(all_mesh_vertices.size() != all_mesh_indices.size()) {
			QUEST_ERROR("The length of all_mesh_vertices does not equal the length of all_mesh_indices!  Each loaded indexed mesh must have its own corresponding vector of indices!")
			throw IndexedModelLoaderError();
		}
	}

} // namespace QuestEngine::API::OpenGL