#include "pch.h"
#include "RegistryManager.h"
#include "QuestEngine/ECS/Manage/RegistryManagerExecptions.h"
#include "QuestEngine/ECS/Components/ModelComponent.h"
#include "QuestEngine/ECS/Components/RenderComponents.h"
#include "QuestEngine/ECS/Components/TransformComponent.h"
#include "QuestEngine/ECS/Components/RotateComponent.h"

#include "QuestUtility/Include/Logger.h"

namespace QuestEngine::ECS {

	entt::registry& RegistryManager::get_active_registry() {
		return m_active_registry;
	}

	void RegistryManager::load_model_into_world(const std::string& entity_id, Model::StandardModel* model, const glm::vec3& world_position, const RenderPass render_pass) {
		const entt::entity entity = m_active_registry.create();
		m_active_registry.emplace<ECS::Components::StandardModelComponent>(entity, model);
		m_active_registry.emplace<ECS::Components::ModelMatrixComponent>(entity, world_position);
		load_entity_render_pass(entity, render_pass);
		store_entity_in_active_entity_map(entity_id, entity);
	}

	void RegistryManager::load_model_into_world(const std::string& entity_id, Model::IndexedModel* model, const glm::vec3& world_position, const RenderPass render_pass) {
		const entt::entity entity = m_active_registry.create();
		m_active_registry.emplace<ECS::Components::IndexedModelComponent>(entity, model);
		m_active_registry.emplace<ECS::Components::ModelMatrixComponent>(entity, world_position);
		store_entity_in_active_entity_map(entity_id, entity);
		load_entity_render_pass(entity, render_pass);
	}

	void RegistryManager::load_entity_render_pass(const entt::entity& entity, const RenderPass render_pass) {
		switch(render_pass) {
			case RenderPass::Deferred: {
				m_active_registry.emplace<ECS::Components::RenderDeferredComponent>(entity);
				m_active_registry.emplace<ECS::Components::NormalMatrixComponent>(entity);
				break;
			}
			case RenderPass::Pointlight: {
				m_active_registry.emplace<ECS::Components::RenderPointlightComponent>(entity);
				break;
			}
			case RenderPass::Forward: {
				m_active_registry.emplace<ECS::Components::RenderForwardComponent>(entity);
				m_active_registry.emplace<ECS::Components::NormalMatrixComponent>(entity);
				break;
			}
			default:  // NOLINT(clang-diagnostic-covered-switch-default)
				QUEST_ERROR("Loaded entity render_pass (e.g. deferred, forward, etc.) does not exist in the load_entity_render_pass function!")
				throw EntityLoadRenderPassException();
			}
	}

	void RegistryManager::store_entity_in_active_entity_map(const std::string& entity_id, const entt::entity& entity) {
		QUEST_WARN_CONDITION(m_active_entity_map.count(entity_id) == 0, "You are reloading an entity: <" + entity_id + "> into the entity map!  All entities are active, but your entity map (primarily used for the ui selection) will only reflect the most recently loaded entity.")
		m_active_entity_map[entity_id] = entity;
	}

} // namespace QuestEngine::ECS