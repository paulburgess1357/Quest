#include "pch.h"
#include "QuestEngine/API/EngineAPI.h"
#include "QuestEngine/Engine/Engine.h"
#include "QuestEngine/ECS/Components/ModelComponent.h"
#include "QuestEngine/ECS/Components/RotateComponent.h"

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
	void QuestEngineAPI::load_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::StandardMesh>& meshes) const {
		m_engine->m_resource_manager.load_model(model_id, shader_program, meshes);
	}

	void QuestEngineAPI::load_indexed_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::IndexedMesh>& meshes) const {
		m_engine->m_resource_manager.load_indexed_model(model_id, shader_program, meshes);
	}

	// ======================== Camera ========================
	void QuestEngineAPI::load_camera(const std::string& camera_id, const glm::vec3& camera_position, const glm::vec3& pt_to_look_at_in_world) const {
		m_engine->m_resource_manager.load_camera(camera_id, camera_position, pt_to_look_at_in_world);
	}

	void QuestEngineAPI::set_active_camera(const std::string& camera_id) const {
		m_engine->set_active_camera(camera_id);
	}

	// ========================= Registry ======================
	void QuestEngineAPI::load_model_into_registry(const std::string& model_id) const {
		Model::StandardModel* model = m_engine->m_resource_manager.get_model_pointer(model_id);
		const entt::entity entity = m_engine->m_registry.create();
		m_engine->m_registry.emplace<ECS::Components::StandardModelComponent>(entity, model);
		// Testing w/ rotation
		m_engine->m_registry.emplace<ECS::Components::RotateComponent>(entity);
	}

	void QuestEngineAPI::load_indexed_model_into_registry(const std::string& model_id) const {
		Model::IndexedModel* model = m_engine->m_resource_manager.get_indexed_model_pointer(model_id);
		const entt::entity entity = m_engine->m_registry.create();
		m_engine->m_registry.emplace<ECS::Components::IndexedModelComponent>(entity, model);
		// Testing w/ rotation
		m_engine->m_registry.emplace<ECS::Components::RotateComponent>(entity);
	}

} // namespace QuestEngine::API