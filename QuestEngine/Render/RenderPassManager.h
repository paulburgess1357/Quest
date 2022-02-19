#pragma once
#include "QuestEngine/Using/Framebuffer.h"
#include "QuestEngine/Using/Shader.h"
#include "QuestEngine/Using/Model.h"
#include "QuestEngine/Using/Window.h"
#include "QuestEngine/Using/UserInterface.h"
#include <entt/entt.hpp>

namespace QuestEngine::Render {

	class RenderPassManager {

	public:
		RenderPassManager(const Window::Window& window, entt::registry& active_registry);
		void render();
		void set_active_registry(entt::registry& registry);
		void resize_attachments(const int width, const int height);

		void set_pointlight_shader(Shader::ShaderProgram& shader_program);
		void set_postprocess_shader(Shader::ShaderProgram& shader_program);

	private:
		void deferred_pass() const;
		void light_pass() const;
		void forward_pass() const;

		void default_framebuffer_pass() const;
		void imgui_viewport_pass() const;

		void draw_post_process() const;
		void draw_user_interface(void* handle) const;

		void handle_window_resize();

		// Tracking window resizes:
		const Window::Window& m_window;
		int m_window_width;
		int m_window_height;

		// RGBA16F_NEAREST, RGBA16F_NEAREST, RGBA_NEAREST
		// Position,        Normals,         Color + Specular
		Framebuffer::Framebuffer2D m_g_buffer;

		// RGBA16F_NEAREST
		// Scene colors
		Framebuffer::Framebuffer2D m_post_process_framebuffer;

		Shader::ShaderProgram* m_pointlight_shader;
		Shader::ShaderProgram* m_postprocess_shader;

		Model::IndexedMeshQuad m_quad;
		entt::registry* m_active_registry;

		UserInterface::UserInterface m_user_interface;

	};


} // namespace QuestEngine::Render


