#include "pch.h"
#include "RegistryManager.h"
#include "QuestUtility/Include/Logger.h"
#include "QuestEngine/ECS/Components/ModelComponent.h"
#include "QuestEngine/ECS/Components/RenderComponents.h"
#include "QuestEngine/ECS/Components/TransformComponent.h"
#include "QuestEngine/ECS/Components/RotateComponent.h"

namespace QuestEngine::ECS {

	entt::registry& RegistryManager::get_active_registry() {
		return m_active_registry;
	}

	void RegistryManager::load_model_into_world(const std::string& entity_id, Model::StandardModel* model, const glm::vec3& world_position, const bool deferred_render_pass) {
		const entt::entity entity = m_active_registry.create();
		m_active_registry.emplace<ECS::Components::StandardModelComponent>(entity, model);
		m_active_registry.emplace<ECS::Components::TransformComponent>(entity, world_position);
		m_active_registry.emplace<ECS::Components::RotateComponent>(entity);

		if(deferred_render_pass) {
			m_active_registry.emplace<ECS::Components::RenderDeferredComponent>(entity);
		} else {
			m_active_registry.emplace<ECS::Components::RenderForwardComponent>(entity);
		}

		store_entity_in_active_entity_map(entity_id, entity);
	}

	void RegistryManager::load_model_into_world(const std::string& entity_id, Model::IndexedModel* model, const glm::vec3& world_position, const bool deferred_render_pass) {
		const entt::entity entity = m_active_registry.create();
		m_active_registry.emplace<ECS::Components::IndexedModelComponent>(entity, model);
		m_active_registry.emplace<ECS::Components::TransformComponent>(entity, world_position);
		m_active_registry.emplace<ECS::Components::RotateComponent>(entity);
		store_entity_in_active_entity_map(entity_id, entity);

		if (deferred_render_pass) {
			m_active_registry.emplace<ECS::Components::RenderDeferredComponent>(entity);
		} else {
			m_active_registry.emplace<ECS::Components::RenderForwardComponent>(entity);
		}

	}

	void RegistryManager::store_entity_in_active_entity_map(const std::string& entity_id, const entt::entity& entity) {
		QUEST_WARN_CONDITION(m_active_entity_map.count(entity_id) == 0, "You are reloading an entity: <" + entity_id + "> into the entity map!  All entities are active, but your entity map (primarily used for the ui selection) will only reflect the most recently loaded entity.")
		m_active_entity_map[entity_id] = entity;
	}

} // namespace QuestEngine::ECS