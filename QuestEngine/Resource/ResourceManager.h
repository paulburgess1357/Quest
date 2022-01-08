#pragma once
#include "QuestEngine/Using/Resource.h"

namespace QuestEngine::Resource {

	class ResourceManager {

	public:
		// ======================== Shader ========================
		[[nodiscard]] Shader::ShaderProgram& get_shader(const std::string& shader_id);
		[[nodiscard]] Shader::ShaderProgram* get_shader_pointer(const std::string& shader_id);
		void load_shader(const std::string& shader_id, const std::initializer_list<std::pair<Shader::ShaderEnum, std::string>> shaders);

		// ======================== Model ========================
		[[nodiscard]] Model::StandardModel& get_model(const std::string& model_id);
		[[nodiscard]] Model::StandardModel* get_model_pointer(const std::string& model_id);
		void load_model(const std::string& model_id, const Shader::ShaderProgram& shader_program, std::vector<Model::StandardMesh>& meshes);

		//// ==================== Indexed Model ====================
		[[nodiscard]] Model::IndexedModel& get_indexed_model(const std::string& model_id);
		[[nodiscard]] Model::IndexedModel* get_indexed_model_pointer(const std::string& model_id);
		void load_indexed_model(const std::string& model_id, const Shader::ShaderProgram& shader_program, std::vector<Model::IndexedMesh>& meshes);

	private:
		ShaderResource m_shader_resource;
		StandardModelResource m_standard_model_resource;
		IndexedModelResource m_indexed_model_resource;
		
	};

} // namespace QuestEngine::Resource