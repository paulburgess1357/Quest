#pragma once
#include <entt/entity/registry.hpp>
#include "QuestEngine/ECS/Components/ModelComponent.h"
#include "QuestEngine/ECS/Components/RotateComponent.h"
#include <glm/ext/matrix_transform.hpp>

//TODO need to handle indexed vs normal model the same!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

namespace QuestEngine::ECS::Systems {

	struct TransformSystem {
		static void transform(const entt::registry& registry) {
			rotate(registry);
			rotate_indexed(registry);
		}

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