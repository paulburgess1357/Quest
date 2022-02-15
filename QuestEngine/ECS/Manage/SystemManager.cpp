#include "pch.h"
#include "SystemManager.h"
#include "QuestEngine/ECS/Systems/RenderSystem.h"
#include "QuestEngine/ECS/Systems/TransformSystem.h"

namespace QuestEngine::ECS {

	SystemManager::SystemManager(entt::registry& active_registry)
		:m_active_registry{ &active_registry }{
	}

	void SystemManager::set_active_registry(entt::registry& registry) {
		m_active_registry = &registry;
	}

	void SystemManager::update(const Camera::Camera& camera) const {
		ECS::Systems::TransformSystem::transform(*m_active_registry, camera);
	}

	void SystemManager::draw() const {
		ECS::Systems::RenderSystem::render(*m_active_registry);
	}

} // namespace QuestEngine::ECS