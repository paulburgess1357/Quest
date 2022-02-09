#pragma once
#include "QuestEngine/API/Neutral/ResourceAPI.h"

namespace QuestEngine::API::OpenGL {

	class ModelLoaderAPI : public ResourceAPI {

	public:
		explicit ModelLoaderAPI(Engine::Engine* engine);
		void load_model(const std::string& model_id, const std::string& shader_program_id, const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<int>& vertex_description) const;
		void load_model(const std::string& model_id, const std::string& shader_program_id, const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<std::vector<unsigned int>>& all_mesh_indices, const std::vector<int>& vertex_description) const;

	private:
		static void check_indexed_vertices_indices(const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<std::vector<unsigned>>& all_mesh_indices);
	};

} // namespace QuestEngine::API::OpenGL