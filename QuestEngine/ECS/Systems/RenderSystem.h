#pragma once
#include "QuestEngine/ECS/Components/ModelComponent.h"
#include "QuestEngine/ECS/Components/RenderComponents.h"
#include <entt/entt.hpp>

namespace QuestEngine::ECS::Systems {

	struct RenderSystem {

		static void render_deferred(const entt::registry& registry) {

			registry.view<Components::StandardModelComponent, Components::RenderDeferredComponent>().each([&](auto& model, auto& deferred) {
				model.m_model->draw();
				});

			registry.view<Components::IndexedModelComponent, Components::RenderDeferredComponent>().each([&](auto& model, auto& deferred) {
				model.m_model->draw();
				});

		}

		static void render_forward(const entt::registry& registry) {

			registry.view<Components::StandardModelComponent, Components::RenderForwardComponent>().each([&](auto& model, auto& forward) {
				model.m_model->draw();
			});

			registry.view<Components::IndexedModelComponent, Components::RenderForwardComponent>().each([&](auto& model, auto& forward) {
				model.m_model->draw();
			});

		}


	};

} // QuestEngine::ECS::Systems
