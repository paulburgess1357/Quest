#include "pch.h"
#include "ResourceManager.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "QuestUtility/Logging/LogHandler.h"

namespace QuestEngine::Resource {

	// Shader
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



} // namespace QuestEngine::Resource