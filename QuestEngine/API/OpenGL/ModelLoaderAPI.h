#pragma once
#include "QuestEngine/API/Neutral/ResourceAPI.h"

namespace QuestEngine::API::OpenGL {

	class ModelLoaderAPI : public ResourceAPI {

	public:
		explicit ModelLoaderAPI(Engine::Engine* engine);

		template<GLenum DrawMode>
		void load_model(const std::string& model_id, const std::string& shader_program_id, const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<int>& vertex_description) const {
			// Load multiple vectors of vertices.  For example, you can load a model
			// that has multiple meshes.  Each mesh would have its own vector of vertices
			Shader::ShaderProgram& shader_program = get_shader(shader_program_id);

			// Load vertex data
			std::vector<QuestGLCore::Model::Mesh<QuestGLCore::VertexData::VertexData>> all_meshes;
			for (auto& mesh_vertices : all_mesh_vertices) {
				QuestGLCore::VertexData::VertexData vertex_data{ GL_ARRAY_BUFFER, DrawMode };
				vertex_data.load_data<float>(mesh_vertices, vertex_description);

				// Move vertex data into mesh
				QuestGLCore::Model::Mesh standard_mesh{ std::move(vertex_data) };

				// Move mesh into vector
				all_meshes.push_back(std::move(standard_mesh));
			}

			// Move vector of mesh's into model and store in resource
			ResourceAPI::load_model(model_id, shader_program, all_meshes);
		}

		template<GLenum DrawMode>
		void load_model(const std::string& model_id, const std::string& shader_program_id, const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<std::vector<unsigned>>& all_mesh_indices, const std::vector<int>& vertex_description) const {
			// Load multiple indexed mesh's.  The length of all_mesh_vertices must
			// be the same length as all_mesh_indices, as each mesh would have its
			// own corresponding vector of indices.
			check_indexed_vertices_indices(all_mesh_vertices, all_mesh_indices);
			Shader::ShaderProgram& shader_program = get_shader(shader_program_id);

			std::vector<QuestGLCore::Model::Mesh<QuestGLCore::VertexData::IndexedVertexData>> all_indexed_meshes;
			for (size_t i = 0; i < all_mesh_vertices.size(); i++) {
				QuestGLCore::VertexData::IndexedVertexData vertex_data_element{ GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, DrawMode };
				vertex_data_element.load_data(all_mesh_vertices.at(i), all_mesh_indices.at(i), vertex_description);

				// Move vertex data into mesh
				QuestGLCore::Model::Mesh indexed_mesh{ std::move(vertex_data_element) };

				// Move mesh into vector
				all_indexed_meshes.push_back(std::move(indexed_mesh));
			}

			// Move vector of mesh's into model and store in resource
			ResourceAPI::load_model(model_id, shader_program, all_indexed_meshes);
		}

	private:
		static void check_indexed_vertices_indices(const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<std::vector<unsigned>>& all_mesh_indices);
	};

} // namespace QuestEngine::API::OpenGL