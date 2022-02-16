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
		m_g_buffer.set_shader_program(m_resource_manager.get_shader(Constants::g_buffer_light_pass));
		m_post_process_framebuffer.set_shader_program(m_resource_manager.get_shader(Constants::post_process_shader));
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
			draw_user_interface();
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

		// ======= Lighting drawing pass =======
		// - Take g-buffer stored data and draw lighting to window framebuffer
		m_g_buffer.unbind();

		m_window.clear_buffer();
		m_g_buffer.draw();

		// Transfer g-buffer depth values to default fb (necessary for depth w/
		// forward rendering pass):
		m_g_buffer.blit_depth_to_default_fb(m_window_width, m_window_height, m_window_width, m_window_height);

		// Fully unbind (prepares subsequent read/writes to default fb)
		m_g_buffer.unbind();

		// ======== Forward drawing pass =======
		// Read/Write forward pass to window framebuffer
		m_systems_manager.draw_forward();
		

		// ====== Post process drawing pass =====
		// TODO Color will look off until this is applied! (e.g. gamma correction is NOT being added currently!!)
		// For post process to work, I have to 'inject' it above (so i blit to post process fb instead...)
		// All drawing would go to post-proecss fb (quad being drawn, blit, forward, etc.)  After that I would draw to main window...

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