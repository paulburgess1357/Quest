#include "pch.h"
#include "QuestEngine/API/EngineAPI.h"
#include "QuestEngine/Engine/Engine.h"

namespace QuestEngine::API {

	QuestEngineAPI::QuestEngineAPI(const int width, const int height)
		:m_engine{ std::make_unique<Engine::Engine>(width, height) } {
	}

	void QuestEngineAPI::run() const {
		m_engine->run();
	}

	void QuestEngineAPI::load_shader(const std::string& shader_id, const std::initializer_list<std::pair<QuestGLCore::Shader::ShaderEnum, std::string>> shaders) const {
		std::unordered_map<QuestGLCore::Shader::ShaderEnum, std::string> shader_string_map;
		for (const auto& [shader_type, shader_string] : shaders) {
			QUEST_WARN_CONDITION(shader_string_map.count(shader_type) == 0, "You are loading two of the same shader type (e.g. two vertex shaders) into a single shader program!");
			shader_string_map[shader_type] = shader_string;
		}
		m_engine->m_shader_resource.load(shader_id, shader_id, QuestGLCore::Shader::ShaderProgramCreator{ shader_string_map });
	}

} // namespace QuestEngine::API