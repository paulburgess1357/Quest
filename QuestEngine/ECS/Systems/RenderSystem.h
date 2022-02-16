#pragma once
#include "QuestEngine/ECS/Components/ModelComponent.h"
#include "QuestEngine/ECS/Components/RenderComponents.h"
#include "QuestEngine/ECS/Components/TransformComponent.h"
#include "QuestGLCore/Shader/ShaderProgram.h"
#include "QuestGLCore/Constants/Constants.h"
#include <entt/entt.hpp>

namespace QuestEngine::ECS::Systems {

	class RenderSystem {
	public:

		// ========== Deferred Rendering ==========

		static void render_deferred(const entt::registry& registry) {
			registry.view<Components::StandardModelComponent, Components::TransformComponent, Components::RenderDeferredComponent>().each([](auto& model, auto& transform, auto& deferred) {
				auto* shader_program = model.m_model->get_shader_program();
				shader_program->bind();
				set_model_uniform_matrices(shader_program, transform.m_model_matrix, transform.m_normal_matrix);
				model.m_model->draw();
			});
			registry.view<Components::IndexedModelComponent, Components::TransformComponent, Components::RenderDeferredComponent>().each([](auto& model, auto& transform, auto& deferred) {
				auto* shader_program = model.m_model->get_shader_program();
				shader_program->bind();
				set_model_uniform_matrices(shader_program, transform.m_model_matrix, transform.m_normal_matrix);
				model.m_model->draw();
			});
		}

		// ========== Forward Rendering ==========

		static void render_forward(const entt::registry& registry) {
			registry.view<Components::StandardModelComponent, Components::TransformComponent, Components::RenderForwardComponent>().each([](auto& model, auto& transform, auto& forward) {
				auto* shader_program = model.m_model->get_shader_program();
				shader_program->bind();
				set_model_uniform_matrices(shader_program, transform.m_model_matrix, transform.m_normal_matrix);
				model.m_model->draw();
			});
			registry.view<Components::IndexedModelComponent, Components::TransformComponent, Components::RenderForwardComponent>().each([](auto& model, auto& transform, auto& forward) {
				auto* shader_program = model.m_model->get_shader_program();
				shader_program->bind();
				set_model_uniform_matrices(shader_program, transform.m_model_matrix, transform.m_normal_matrix);
				model.m_model->draw();
			});
		}

	private:
		static void set_model_uniform_matrices(Shader::ShaderProgram* shader_program, const glm::mat4& model_matrix, const glm::mat3& normal_matrix) {
			shader_program->set_uniform(QuestGLCore::Constants::model_matrix, model_matrix);
			shader_program->set_uniform(QuestGLCore::Constants::normal_matrix, normal_matrix);
		}

	};

} // QuestEngine::ECS::Systems
