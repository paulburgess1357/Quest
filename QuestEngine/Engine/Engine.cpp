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
		m_post_process_framebuffer{ width, height, { Texture::BlankTextureEnum::RGBA_LINEAR, Texture::BlankTextureEnum::RGBA16F_LINEAR }, m_resource_manager.get_shader(Constants::post_process_shader) },
		m_window_width{ Window::Window::get_width() },
		m_window_height{ Window::Window::get_height() }{
		QUEST_INFO("Quest Engine v{}.{} Initialized\n", 0, 1)
		initialization();
	}

	void Engine::run() {
		qc_checks();
		gameloop();
	}

	void Engine::initialization() {
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
			m_systems_manager.update();

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
			m_projection_matrix.update_projection_matrix(m_window_width, m_window_height);
		}
	}

	void Engine::draw_scene() const {
		// Draw scene to post-process framebuffer
		m_post_process_framebuffer.bind();
		Framebuffer::Framebuffer2D::clear_buffer_no_bind();
		m_systems_manager.draw();

		// Unbind framebuffer and draw to window
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