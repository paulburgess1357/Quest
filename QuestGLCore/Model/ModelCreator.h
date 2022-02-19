#pragma once
#include "QuestGLCore/Shader/ShaderProgram.h"
#include "QuestGLCore/Model/ModelEnums.h"
#include <glad/glad.h>

namespace QuestGLCore::Model {

	class ModelCreator {
		
	public:
		static Model<VertexData::VertexData> create_model(Shader::ShaderProgram& shader_program, const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<int>& vertex_description, const ModelDrawMode draw_mode);
		static Model<VertexData::IndexedVertexData> create_model(Shader::ShaderProgram& shader_program, const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<std::vector<unsigned>>& all_mesh_indices, const std::vector<int>& vertex_description, const ModelDrawMode draw_mode);

	private:
		static void check_indexed_vertices_indices(const std::vector<std::vector<float>>& all_mesh_vertices, const std::vector<std::vector<unsigned>>& all_mesh_indices);
	};

}