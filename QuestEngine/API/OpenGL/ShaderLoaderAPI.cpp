#include "pch.h"
#include "ShaderLoaderAPI.h"
#include "QuestUtility/String/FileToString.h"

namespace QuestEngine::API::OpenGL {

	ShaderLoaderAPI::ShaderLoaderAPI(Engine::Engine* engine)
		:ResourceAPI{ engine } {
	}

	void ShaderLoaderAPI::load_shader(const std::string& shader_program_id, std::string vertex, std::string fragment, const bool from_file, const bool link_ubo_matrices) const {
		if(from_file) {
			vertex = QuestUtility::String::FileToString::load(vertex);
			fragment = QuestUtility::String::FileToString::load(fragment);
		}

		load_shader(shader_program_id, {
			std::pair{QuestGLCore::Shader::ShaderEnum::VERTEX, vertex },
			std::pair{QuestGLCore::Shader::ShaderEnum::FRAGMENT, fragment }
			}, link_ubo_matrices);
	}

	void ShaderLoaderAPI::load_shader(const std::string& shader_id, const std::initializer_list<std::pair<Shader::ShaderEnum, std::string>>& shaders, const bool link_ubo_matrices) const {
		std::unordered_map<Shader::ShaderEnum, std::string> shader_string_map;
		for (const auto& [shader_type, shader_string] : shaders) {
			QUEST_WARN_CONDITION(shader_string_map.count(shader_type) == 0, "You are loading two of the same shader type (e.g. two vertex shaders) into a single shader program!")
			shader_string_map[shader_type] = shader_string;
		}
		ResourceAPI::load_shader(shader_id, shader_string_map, link_ubo_matrices);
	}

} // namespace QuestEngine::API::OpenGL