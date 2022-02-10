#pragma once
#include "QuestEngine/ECS/Components/ModelComponent.h"
#include <entt/entt.hpp>

namespace QuestEngine::ECS::Systems {

	struct RenderSystem {
		static void render(const entt::registry& registry) {

			registry.view<Components::StandardModelComponent>().each([&](auto& model) {
				model.m_model->draw();
			});

			registry.view<Components::IndexedModelComponent>().each([&](auto& model) {
				model.m_model->draw();
			});

		}
	};

} // QuestEngine::ECS::Systems
