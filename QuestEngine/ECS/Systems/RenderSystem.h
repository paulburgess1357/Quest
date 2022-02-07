#pragma once
#include "QuestEngine/Camera/Camera.h"
#include "QuestEngine/Camera/ProjectionMatrix.h"
#include "QuestEngine/ECS/Components/ModelComponent.h"
#include <entt/entt.hpp>

//TODO need to handle indexed vs normal model the same!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

namespace QuestEngine::ECS::Systems {

	// TODO I think a solution for this is to do what I did in ExtraLifeEngine.  Create a transform component that houses the model matrix (and possible world position-  not sure about this yet)
	// TODO This would allow me to not have so many copies of systems (I just operate on the transform component).  For rendering, I set the model matrix (so anything in the world would have to have its own model matrix).
	// TODO I think this works fine because I can only wriet one rotation system, one movement, one physiucs, etc.  I just need to make sure the model matrix is set for rendering when the shader call to set_uniform is made.
	// TODO Not sure about normal matrix.  I should look through my old ExtraLifeEngine code and see what I did there.

	//TODO so i think i would have something like:
	// registry.view<Components::StandardModelComponent, Components::TransformComponent>
	// registry.view<Components::IndexedStandardModelComponent, Components::TransformComponent>

	struct RenderSystem {
		static void render(const entt::registry& registry, Camera::ProjectionMatrix& projection_matrix, Camera::Camera& camera) {

			// TODO (The view and projection matrices will need to be set in their own system when they are made global) *****
			// TODO Camera is not const due to view matrix changing (in the future) due to get_view_matrix() and camera position changing.  ACtually this will likely be done in the update system.
			registry.view<Components::StandardModelComponent>().each([&](auto& model) {

				// Temp for matrices ==============
				Shader::ShaderProgram* shader_program = model.m_model->get_shader_program();
				shader_program->bind();
				shader_program->set_uniform("view_matrix", camera.get_view_matrix());
				shader_program->set_uniform("projection_matrix", projection_matrix.get_projection_matrix());
				model.m_model->draw(); // TODO re-enable model matrix being set when testing complete.
			});

			// TODO (The view and projection matrices will need to be set in their own system when they are made global) *****
			// TODO Camera is not const due to view matrix changing (in the future) due to get_view_matrix() and camera position changing.  ACtually this will likely be done in the update system.
			registry.view<Components::IndexedModelComponent>().each([&](auto& model) {
				// Temp for matrices ==============
				Shader::ShaderProgram* shader_program = model.m_model->get_shader_program();
				shader_program->bind();
				shader_program->set_uniform("view_matrix", camera.get_view_matrix());
				shader_program->set_uniform("projection_matrix", projection_matrix.get_projection_matrix());
				model.m_model->draw();
			});

		}
	};

} // QuestEngine::ECS::Systems
