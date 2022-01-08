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

	// ======================== Shader ========================
	Shader::ShaderProgram& QuestEngineAPI::get_shader(const std::string& shader_id) const {
		return m_engine->m_resource_manager.get_shader(shader_id);
	}

	void QuestEngineAPI::load_shader(const std::string& shader_id, const std::initializer_list<std::pair<Shader::ShaderEnum, std::string>> shaders) const {
		m_engine->m_resource_manager.load_shader(shader_id, shaders);
	}

	// ======================== Model ========================
	Model::StandardModel& QuestEngineAPI::get_model(const std::string& model_id) const {
		return m_engine->m_resource_manager.get_model(model_id);
	}

	void QuestEngineAPI::load_model(const std::string& model_id, const Shader::ShaderProgram& shader_program, std::vector<Model::StandardMesh>& meshes) const {
		m_engine->m_resource_manager.load_model(model_id, shader_program, meshes);
	}

	// ==================== Indexed Model ====================
	Model::IndexedModel& QuestEngineAPI::get_indexed_model(const std::string& model_id) const {
		return m_engine->m_resource_manager.get_indexed_model(model_id);
	}

	void QuestEngineAPI::load_indexed_model(const std::string& model_id, const Shader::ShaderProgram& shader_program, std::vector<Model::IndexedMesh>& meshes) const {
		m_engine->m_resource_manager.load_indexed_model(model_id, shader_program, meshes);
	}

} // namespace QuestEngine::API