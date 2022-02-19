#pragma once
#include "QuestEngine/API/Neutral/ResourceAPI.h"
#include "QuestEngine/Using/Model.h"

namespace QuestEngine::API::OpenGL {

	class ModelLoaderAPI : public ResourceAPI {

	public:
		explicit ModelLoaderAPI(Engine::Engine* engine)
			:ResourceAPI{ engine } {
		}

		void load_model(const std::string& model_id, const std::string& shader_program_id, const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<int>& vertex_description, const Model::ModelDrawMode draw_mode) const {
			// Load multiple vectors of vertices.  For example, you can load a model
			// that has multiple meshes.  Each mesh would have its own vector of vertices
			Shader::ShaderProgram& shader_program = get_shader(shader_program_id);
			auto model = Model::ModelCreator::create_model(shader_program, all_mesh_vertices, vertex_description, draw_mode);

			// Move vector of mesh's into model and store in resource
			ResourceAPI::load_model(model_id, model);
		}

		void load_model(const std::string& model_id, const std::string& shader_program_id, const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<std::vector<unsigned>>& all_mesh_indices, const std::vector<int>& vertex_description, const Model::ModelDrawMode draw_mode) const {
			// Load multiple indexed mesh's.  The length of all_mesh_vertices must
			// be the same length as all_mesh_indices, as each mesh would have its
			// own corresponding vector of indices.
			Shader::ShaderProgram& shader_program = get_shader(shader_program_id);
			auto model = Model::ModelCreator::create_model(shader_program, all_mesh_vertices, all_mesh_indices, vertex_description, draw_mode);

			// Move vector of mesh's into model and store in resource
			ResourceAPI::load_model(model_id, model);
		}

	};

} // namespace QuestEngine::API::OpenGL