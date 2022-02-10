#pragma once
#include <entt/entity/registry.hpp>
#include "QuestEngine/ECS/Components/ModelComponent.h"
#include "QuestEngine/ECS/Components/RotateComponent.h"
#include "QuestEngine/ECS/Components/TransformComponent.h"
#include <glm/ext/matrix_transform.hpp>

namespace QuestEngine::ECS::Systems {

	struct TransformSystem {
		static void transform(entt::registry& registry) {
			rotate(registry);
			ui_transform(registry);


			update_model_matrix(registry); // set last
		}

		static void rotate(entt::registry& registry) {
			registry.view<Components::TransformComponent, Components::RotateComponent>().each([](auto& transform, auto& rotate) {
				transform.m_model_matrix = glm::rotate(transform.m_model_matrix, rotate.m_rate, rotate.m_axis);
			});
		}

		static void ui_transform(entt::registry& registry) {

			// Even better, I *think* I can make a map of
			// model id and entity id.  I can then access the entity that way.
			//  I need to make sure the entity in the associated map is destroyed when the registry destroys it as well...

			// Access entity via map
			// May need to add ui component to write a system that manipulates the transform component
			// The transform component manipulation will be done by the gizmo library

			// Once complete, I remove that component from the entity (i.e. when the ui window is closed)
		}

		static void update_model_matrix(entt::registry& registry) {
			registry.view<Components::StandardModelComponent, Components::TransformComponent>().each([](auto& model, auto& transform) {
				model.m_model->set_model_matrix(transform.m_model_matrix);
			});
			registry.view<Components::IndexedModelComponent, Components::TransformComponent>().each([](auto& model, auto& transform) {
				model.m_model->set_model_matrix(transform.m_model_matrix);
			});
		}

	};

} // QuestEngine::ECS::Systems