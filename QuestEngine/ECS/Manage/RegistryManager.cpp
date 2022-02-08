#include "pch.h"
#include "RegistryManager.h"
#include "QuestUtility/Logging/LogMacros.h"

namespace QuestEngine::ECS {

	entt::registry& RegistryManager::get_active_registry() {
		return m_active_registry;
	}

	void RegistryManager::add_active_entity_to_map(const std::string& entity_id, const entt::entity& entity) {
		QUEST_WARN_CONDITION(m_active_entity_map.count(entity_id) == 0, "You are reloading an entity: <" + entity_id + "> into the entity map!  All entities are active, but your entity map (primarily used for the ui selection) will only reflect the most recently loaded entity.")
		m_active_entity_map[entity_id] = entity;
	}

	// Model Registry Loading
	void RegistryManager::load_model_into_registry(const std::string& entity_id, Model::StandardModel* model, const glm::vec3& world_position) {
		const entt::entity entity = m_active_registry.create();
		m_active_registry.emplace<ECS::Components::StandardModelComponent>(entity, model);
		load_model_entity_into_world(entity_id, entity, world_position);
	}

	void RegistryManager::load_model_into_registry(const std::string& entity_id, Model::IndexedModel* model, const glm::vec3& world_position) {
		const entt::entity entity = m_active_registry.create();
		m_active_registry.emplace<ECS::Components::IndexedModelComponent>(entity, model);
		load_model_entity_into_world(entity_id, entity, world_position);
	}

	void RegistryManager::load_model_entity_into_world(const std::string& entity_id, const entt::entity& entity, const glm::vec3& world_position) {
		m_active_registry.emplace<ECS::Components::TransformComponent>(entity, world_position);
		// Testing rotation
		m_active_registry.emplace<ECS::Components::RotateComponent>(entity);
		add_active_entity_to_map(entity_id, entity);
	}
}