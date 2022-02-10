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

	void SystemManager::run() {
		update();
		render();
	}

	void SystemManager::update() const {
		//TODO create entity for update system that is for ubo matrices only?
		//What if other ubos are added outside of the engine?? For example, the test project.
		//What if I want to add a UBO and use an entity/system to update it?
		//I'd like to create an entity that sends up the data for those...

		// ACtually an ECS for this is probably overkill...

		ECS::Systems::TransformSystem::transform(*m_active_registry);
	}

	void SystemManager::render() {
		//TODO note that when ubos work, the projection matrix and camera are no longer needed below.  Camera MAY be necessary later if i need world coordinates...
		ECS::Systems::RenderSystem::render(*m_active_registry);
	}

} // namespace QuestEngine::ECS