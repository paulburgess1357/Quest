#pragma once
#include "QuestEngine/Engine/Engine.h"
#include "QuestEngine/ECS/Manage/RegistryManager.h"
#include <entt/entt.hpp>

namespace QuestEngine::API {

	class RegistryAPI {

	public:
		explicit RegistryAPI(Engine::Engine* engine);
		[[nodiscard]] entt::registry& get_active_registry() const;
		void load_model_into_world(const std::string& entity_id, Model::StandardModel* model, const glm::vec3& world_position, const ECS::RenderPass render_pass) const;
		void load_model_into_world(const std::string& entity_id, Model::IndexedModel* model, const glm::vec3& world_position, const ECS::RenderPass render_pass) const;
		void store_entity_in_active_entity_map(const std::string& entity_id, const entt::entity& entity) const;

	private:
		ECS::RegistryManager& m_engine_registry_manager;
	};

} // namespace QuestEngine::API