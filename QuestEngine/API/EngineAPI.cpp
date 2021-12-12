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

	// ======= Shader =======
	QuestGLCore::Shader::ShaderProgram& QuestEngineAPI::get_shader(const std::string& shader_id) const {
		return m_engine->m_resource_manager.get_shader(shader_id);
	}

	void QuestEngineAPI::load_shader(const std::string& shader_id, const std::initializer_list<std::pair<QuestGLCore::Shader::ShaderEnum, std::string>> shaders) const {
		m_engine->m_resource_manager.load_shader(shader_id, shaders);
	}

} // namespace QuestEngine::API