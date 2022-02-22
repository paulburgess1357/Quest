#include "pch.h"
#include "ModelCreator.h"
#include "ModelExceptions.h"
#include "QuestGLCore/OpenGLTypes/OpenGLEnumResolution.h"
#include "QuestUtility/Logging/LogHandler.h"

namespace QuestGLCore::Model {

	Model<VertexData::VertexData> ModelCreator::create_model(const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<int>& vertex_description, const ModelDrawMode draw_mode) {
		// Load vertex data
		std::vector<Mesh<VertexData::VertexData>> all_meshes;
		const GLenum ogl_draw_mode = OGLResolution::ModelDrawTypeResolution::get_draw_mode(draw_mode);
		for (auto& mesh_vertices : all_mesh_vertices) {
			VertexData::VertexData vertex_data{ GL_ARRAY_BUFFER, ogl_draw_mode };
			vertex_data.load_data<float>(mesh_vertices, vertex_description);

			// Move vertex data into mesh
			Mesh standard_mesh{ std::move(vertex_data) };

			// Move mesh into vector
			all_meshes.push_back(std::move(standard_mesh));
		}

		Model<VertexData::VertexData> model{ std::move(all_meshes) };
		return model;
	}

	Model<VertexData::IndexedVertexData> ModelCreator::create_model(const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<std::vector<unsigned>>& all_mesh_indices, const std::vector<int>& vertex_description, const ModelDrawMode draw_mode) {
		// Load multiple indexed mesh's.  The length of all_mesh_vertices must
		// be the same length as all_mesh_indices, as each mesh would have its
		// own corresponding vector of indices.
		check_indexed_vertices_indices(all_mesh_vertices, all_mesh_indices);
		std::vector<Mesh<VertexData::IndexedVertexData>> all_indexed_meshes;
		const GLenum ogl_draw_mode = OGLResolution::ModelDrawTypeResolution::get_draw_mode(draw_mode);
		for (size_t i = 0; i < all_mesh_vertices.size(); i++) {
			VertexData::IndexedVertexData vertex_data_element{ GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, ogl_draw_mode };
			vertex_data_element.load_data(all_mesh_vertices.at(i), all_mesh_indices.at(i), vertex_description);

			// Move vertex data into mesh
			Mesh indexed_mesh{ std::move(vertex_data_element) };

			// Move mesh into vector
			all_indexed_meshes.push_back(std::move(indexed_mesh));
		}

		Model<VertexData::IndexedVertexData> model{ std::move(all_indexed_meshes) };
		return model;
	}

	void ModelCreator::check_indexed_vertices_indices(const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<std::vector<unsigned>>& all_mesh_indices) {
		if (all_mesh_vertices.size() != all_mesh_indices.size()) {
			QUEST_ERROR("The length of all_mesh_vertices does not equal the length of all_mesh_indices!  Each loaded indexed mesh must have its own corresponding vector of indices!")
			throw IndexedModelCreationException();
		}
	}

} // QuestGLCore::Model