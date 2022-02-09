#pragma once
#include "entt/entity/registry.hpp"

namespace QuestEngine::ECS{

	class RegistryManager {

	public:
		entt::registry& get_active_registry();
		void load_model_into_world(const std::string& entity_id, Model::StandardModel* model, const glm::vec3& world_position);
		void load_model_into_world(const std::string& entity_id, Model::IndexedModel* model, const glm::vec3& world_position);
		void store_entity_in_active_entity_map(const std::string& entity_id, const entt::entity& entity);

	private:
		entt::registry m_active_registry;
		std::unordered_map<std::string, entt::entity> m_active_entity_map;

	};

} // QuestEngine::Registry