#include "pch.h"
#include "ResourceManager.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "QuestUtility/Logging/LogHandler.h"

namespace QuestEngine::Resource {

	// ======================== Shader ========================
	Shader::ShaderProgram& ResourceManager::get_shader(const std::string& shader_id) {
		return m_shader_resource[shader_id];
	}

	Shader::ShaderProgram* ResourceManager::get_shader_pointer(const std::string& shader_id) {
		return m_shader_resource.get_pointer(shader_id);
	}

	void ResourceManager::load_shader(const std::string& shader_id, const std::initializer_list<std::pair<Shader::ShaderEnum, std::string>> shaders) {
		std::unordered_map<Shader::ShaderEnum, std::string> shader_string_map;
		for (const auto& [shader_type, shader_string] : shaders) {
			QUEST_WARN_CONDITION(shader_string_map.count(shader_type) == 0, "You are loading two of the same shader type (e.g. two vertex shaders) into a single shader program!");
			shader_string_map[shader_type] = shader_string;
		}
		m_shader_resource.load(shader_id, shader_id, Shader::ShaderProgramCreator{ shader_string_map });
	}

	// ======================== Model ========================
	Model::StandardModel& ResourceManager::get_model(const std::string& model_id) {
		return m_standard_model_resource[model_id];
	}

	Model::StandardModel* ResourceManager::get_model_pointer(const std::string& model_id) {
		return m_standard_model_resource.get_pointer(model_id);
	}

	void ResourceManager::load_model(const std::string& model_id, const Shader::ShaderProgram& shader_program, std::vector<Model::StandardMesh>& meshes) {
		m_standard_model_resource.load(model_id, shader_program, std::move(meshes));
	}

	// ==================== Indexed Model ====================
	Model::IndexedModel& ResourceManager::get_indexed_model(const std::string& model_id) {
		return m_indexed_model_resource[model_id];
	}

	Model::IndexedModel* ResourceManager::get_indexed_model_pointer(const std::string& model_id) {
		return m_indexed_model_resource.get_pointer(model_id);
	}

	void ResourceManager::load_indexed_model(const std::string& model_id, const Shader::ShaderProgram& shader_program, std::vector<Model::IndexedMesh>& meshes) {
		m_indexed_model_resource.load(model_id, shader_program, std::move(meshes));
	}

} // namespace QuestEngine::Resource