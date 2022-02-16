#include "pch.h"
#include "RegistryAPI.h"

namespace QuestEngine::API {

	RegistryAPI::RegistryAPI(Engine::Engine* engine)
		:m_engine_registry_manager{ engine->get_registry_manager() } {
	}

	entt::registry& RegistryAPI::get_active_registry() const {
		return m_engine_registry_manager.get_active_registry();
	}

	void RegistryAPI::load_model_into_world(const std::string& entity_id, Model::StandardModel* model, const glm::vec3& world_position, const bool deferred_render_pass) const {
		m_engine_registry_manager.load_model_into_world(entity_id, model, world_position, deferred_render_pass);
	}

	void RegistryAPI::load_model_into_world(const std::string& entity_id, Model::IndexedModel* model, const glm::vec3& world_position, const bool deferred_render_pass) const {
		m_engine_registry_manager.load_model_into_world(entity_id, model, world_position, deferred_render_pass);
	}

	void RegistryAPI::store_entity_in_active_entity_map(const std::string& entity_id, const entt::entity& entity) const {
		m_engine_registry_manager.store_entity_in_active_entity_map(entity_id, entity);
	}

} // namespace QuestEngine::API