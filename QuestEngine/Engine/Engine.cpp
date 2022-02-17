#include "pch.h"
#include "Engine.h"
#include "QuestUtility/Include/Logger.h"
#include "QuestEngine/Constants/Constants.h"
#include "QuestEngine/Using/Texture.h"

namespace QuestEngine::Engine {

	Engine::Engine(const int width, const int height)
		:m_window{ width, height },
		m_active_camera{ nullptr },
		m_projection_matrix { Window::Window::get_width(), Window::Window::get_height() },
		m_systems_manager{ m_registry_manager.get_active_registry() },
		m_ubo_manager{ m_resource_manager.get_ubo(Constants::ubo_matrices) },
		m_user_interface{ m_window.get_window() },
		m_g_buffer{ width, height, { Texture::BlankTextureEnum::RGBA16F_NEAREST, Texture::BlankTextureEnum::RGBA16F_NEAREST, Texture::BlankTextureEnum::RGBA_NEAREST }},
		m_post_process_framebuffer{ width, height, { Texture::BlankTextureEnum::RGBA_LINEAR }},
		m_window_width{ Window::Window::get_width() },
		m_window_height{ Window::Window::get_height() }{
		QUEST_INFO("Quest Engine v{}.{} Initialized\n", 0, 1)
	}

	void Engine::run() {
		initialization();
		qc_checks();
		gameloop();
	}

	void Engine::initialization() {
		m_g_buffer.set_shader_program(m_resource_manager.get_shader(Constants::g_buffer_light_pass)); // "g_buffer_light_pass"
		m_post_process_framebuffer.set_shader_program(m_resource_manager.get_shader(Constants::post_process_shader)); // "post_process_shader"
		set_active_camera(Constants::main_camera);
	}

	void Engine::set_active_camera(const std::string& camera_id) {
		if (auto* camera = m_resource_manager.get_camera_pointer(camera_id)) {
			m_active_camera = camera;
		}
	}

	void Engine::qc_checks() const {
		m_resource_manager.shader_qc();
	}

	void Engine::gameloop() {
		while (!shutdown()){
			m_ubo_manager.set_ubos(*m_active_camera, m_projection_matrix);
			m_systems_manager.update(*m_active_camera);

			handle_window_resize();
			draw_scene();
			// draw_user_interface();
			Window::Window::poll_events();

			m_window.swap_buffer();
		}
	}

	void Engine::handle_window_resize() {
		if (Window::Window::get_width() != m_window_width || Window::Window::get_height() != m_window_height) {
			m_window_width = Window::Window::get_width();
			m_window_height = Window::Window::get_height();
			m_post_process_framebuffer.rescale_attachments(m_window_width, m_window_height);
			m_g_buffer.rescale_attachments(m_window_width, m_window_height);
			m_projection_matrix.update_projection_matrix(m_window_width, m_window_height);
		}
	}

	void Engine::draw_scene() const {

		// ====== Deferred drawing pass ======
		// - Store scene in geometry buffer (positions, normals, textures, etc.)
		m_g_buffer.bind();
		Framebuffer::Framebuffer2D::clear_buffer_no_bind();
		m_systems_manager.draw_deferred();
		//m_systems_manager.draw_pointlight();

		// ======= Lighting drawing pass ======
		// - Take g-buffer stored data and draw lighting to post-process framebuffer
		m_post_process_framebuffer.bind();
		Framebuffer::Framebuffer2D::clear_buffer_no_bind();
		m_g_buffer.draw();

		// ************** I think.... *************
		// - Additionally, draw pointlights here?
		// Don't draw fullscreen quad for pointlight!!!! Only for directional light.... i think.... not sure what this means for a cubemap though
		// disable dpeth???
		// draw pointlights
		// ----- do i need depth information from g-buffer to discard fragments here still?
		// enable depth??
		// Note: I'd like a lighting stage:

		// draw pointlights to its own buffer
		// draw directional light to its own buffer

		// e.g.
		//m_pointlight_buffer.bind()... etc
		//m_pointlight_buffer.draw();


		//m_directionallight_buffer.bind()... etc.
		//m_directionallight_buffer.draw();
		



		// Transfer g-buffer depth from 'm_g_buffer' to 'm_post_process_framebuffer'
		m_g_buffer.blit_depth_to_existing_fb(m_post_process_framebuffer, m_window_width, m_window_height, m_window_width, m_window_height);

		// ======== Forward drawing pass =======
		// Fully bind post-process framebuffer
		m_post_process_framebuffer.bind();
		m_systems_manager.draw_forward();

		// ============ Post-Process ===========
		// Draw post-process framebuffer to window
		m_post_process_framebuffer.unbind();
		m_window.clear_buffer();
		m_post_process_framebuffer.draw();
	}

	void Engine::draw_user_interface() const {
		UserInterface::UserInterface::begin_render();
		UserInterface::UserInterface::show_demo();
		m_user_interface.end_render();
	}

	bool Engine::shutdown() const {
		return m_window.close_window() || Window::KeyboardInput::is_pressed(Window::Keyboard::ESCAPE);
	}

	Resource::ResourceManager& Engine::get_resource_manager() {
		return m_resource_manager;
	}

	ECS::RegistryManager& Engine::get_registry_manager() {
		return m_registry_manager;
	}

} // namespace QuestEngine::Engine