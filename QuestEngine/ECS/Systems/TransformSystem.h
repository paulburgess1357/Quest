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



			// When ui is open, see active model/indexed model entities:
			// Perhaps add flag to the entity that says (add ui component)
			// This system adds the ui component


			//  - Add ui component to entity based on the name

			// Take entity with ui component.  Perform transformations here.
			// Set Rotation
			// Move along world
			// Rotate
			// etc.


			// Once complete, I remove that component from the entity
		}

		//static void get_model_entity(entt::registry& registry, const std::string& model_id) {
		//	registry.view<Components::StandardModelComponent>().each([](auto& model) {
		//		
		//	});
		//	registry.view<Components::IndexedModelComponent>().each([](auto& model) {
		//		
		//	});
		//}

		//TODO is is possible to manipulate the transform component for a given entity? So the entity does not hold its own model matrix???
		//TODO similarly, the entity would not hold its normal matrix.  That sort of messed up the set uniform stuff though...

		// Pointer to transform component??? Seems messy.

		// Perhaps I create a system that has a 'user manipulation' component? When I select an entity, I add the component to that entity.
		// then, in that system I access the asscicated transform component and update the actual component.

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