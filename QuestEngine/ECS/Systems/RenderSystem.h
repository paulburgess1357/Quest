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

		static void render_deferred(const entt::registry& registry, Shader::ShaderProgram* shader_program) {
			shader_program->bind();

			registry.view<Components::StandardModelComponent, Components::ModelMatrixComponent, Components::NormalMatrixComponent, Components::RenderDeferredComponent>().each([&](auto& model, auto& model_matrix, auto& normal_matrix, auto& deferred) {
				shader_program->set_uniform(QuestGLCore::Constants::model_matrix, model_matrix.m_model_matrix);
				shader_program->set_uniform(QuestGLCore::Constants::normal_matrix, normal_matrix.m_normal_matrix);
				model.m_model->draw();
			});
			registry.view<Components::IndexedModelComponent, Components::ModelMatrixComponent, Components::NormalMatrixComponent, Components::RenderDeferredComponent>().each([&](auto& model, auto& model_matrix, auto& normal_matrix, auto& deferred) {
				shader_program->set_uniform(QuestGLCore::Constants::model_matrix, model_matrix.m_model_matrix);
				shader_program->set_uniform(QuestGLCore::Constants::normal_matrix, normal_matrix.m_normal_matrix);
				model.m_model->draw();
			});
		}

		// ========== Forward Rendering ==========

		static void render_forward(const entt::registry& registry, Shader::ShaderProgram* shader_program) {
			shader_program->bind();
			registry.view<Components::StandardModelComponent, Components::ModelMatrixComponent, Components::NormalMatrixComponent, Components::RenderForwardComponent>().each([&](auto& model, auto& model_matrix, auto& normal_matrix, auto& forward) {
				shader_program->set_uniform(QuestGLCore::Constants::model_matrix, model_matrix.m_model_matrix);
				shader_program->set_uniform(QuestGLCore::Constants::normal_matrix, normal_matrix.m_normal_matrix);
				model.m_model->draw();
			});
			registry.view<Components::IndexedModelComponent, Components::ModelMatrixComponent, Components::NormalMatrixComponent, Components::RenderForwardComponent>().each([&](auto& model, auto& model_matrix, auto& normal_matrix, auto& forward) {
				shader_program->set_uniform(QuestGLCore::Constants::model_matrix, model_matrix.m_model_matrix);
				shader_program->set_uniform(QuestGLCore::Constants::normal_matrix, normal_matrix.m_normal_matrix);
				model.m_model->draw();
			});
		}

		// ========== Pointlight rendering ==========

		static void render_pointlight(const entt::registry& registry, Shader::ShaderProgram* shader_program, const Framebuffer::Framebuffer2D& g_buffer) {

			shader_program->bind();
			g_buffer.bind_all_color_attachments();

			registry.view<Components::StandardModelComponent, Components::ModelMatrixComponent, Components::RenderPointlightComponent>().each([&](auto& model, auto& model_matrix, auto& pointlight) {
				shader_program->set_uniform(QuestGLCore::Constants::model_matrix, model_matrix.m_model_matrix);
				model.m_model->draw();
			});

			registry.view<Components::IndexedModelComponent, Components::ModelMatrixComponent, Components::RenderPointlightComponent>().each([&](auto& model, auto& model_matrix, auto& pointlight) {
				shader_program->set_uniform(QuestGLCore::Constants::model_matrix, model_matrix.m_model_matrix);
				model.m_model->draw();
			});
		}

	};

} // QuestEngine::ECS::Systems
