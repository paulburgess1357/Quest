#pragma once
#include <entt/entity/registry.hpp>
#include "QuestEngine/ECS/Components/ModelComponent.h"
#include "QuestEngine/ECS/Components/RotateComponent.h"
#include <glm/ext/matrix_transform.hpp>

namespace QuestEngine::ECS::Systems {

	struct TransformSystem {
		static void transform(const entt::registry& registry) {
			rotate(registry);
			rotate_indexed(registry);
		}

		// TODO I think a solution for this is to do what I did in ExtraLifeEngine.  Create a transform component that houses the model matrix (and possible world position-  not sure about this yet)
		// TODO This would allow me to not have so many copies of systems (I just operate on the transform component).  For rendering, I set the model matrix (so anything in the world would have to have its own model matrix).
		// TODO I think this works fine because I can only wriet one rotation system, one movement, one physiucs, etc.  I just need to make sure the model matrix is set for rendering when the shader call to set_uniform is made.
		// TODO Not sure about normal matrix.  I should look through my old ExtraLifeEngine code and see what I did there.

		static void rotate(const entt::registry& registry) {
			registry.view<Components::StandardModelComponent, Components::RotateComponent>().each([&](auto& model) {
				glm::mat4 model_matrix = model.m_model->get_model_matrix();
				model_matrix = glm::rotate(model_matrix, 0.01f, glm::vec3(0.5f, 1.0f, 0.0f));
				model.m_model->set_model_matrix(model_matrix);
			});
		}

		static void rotate_indexed(const entt::registry& registry) {
			registry.view<Components::IndexedModelComponent, Components::RotateComponent>().each([&](auto& model) {
				glm::mat4 model_matrix = model.m_model->get_model_matrix();
				model_matrix = glm::rotate(model_matrix, 0.06f, glm::vec3(0.5f, 1.0f, 0.0f));
				model.m_model->set_model_matrix(model_matrix);
			});
		}

	};

} // QuestEngine::ECS::Systems