#pragma once
#include "QuestEngine/API/EngineAPI.h"

namespace QuestEngine::API::OpenGL {

	class ModelLoader {

	public:
		explicit ModelLoader(const QuestEngineAPI& engine_api);
		void load_model(const std::string& model_id, const std::string& shader_program_id, const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<int>& vertex_description) const;
		void load_model(const std::string& model_id, const std::string& shader_program_id, const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<std::vector<unsigned int>>& all_mesh_indices, const std::vector<int>& vertex_description) const;
		void load_model_into_registry(const std::string& model_id, const Model::ModelType model_type) const;

	private:
		static void check_indexed_vertices_indices(const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<std::vector<unsigned>>& all_mesh_indices);
		const QuestEngineAPI& m_engine_api;
	};

} // namespace QuestEngine::API::OpenGL