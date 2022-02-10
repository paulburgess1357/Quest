#pragma once
#include "QuestEngine/Camera/Camera.h"
#include "QuestEngine/Camera/ProjectionMatrix.h"
#include "QuestEngine/ECS/Components/ModelComponent.h"
#include <entt/entt.hpp>

// TODO (The view and projection matrices will need to be set in their own system when they are made global) *****
// TODO Camera is not const due to view matrix changing (in the future) due to get_view_matrix() and camera position changing.  ACtually this will likely be done in the update system.

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
