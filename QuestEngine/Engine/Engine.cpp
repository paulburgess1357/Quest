#include "pch.h"
#include "Engine.h"
#include "QuestUtility/Include/Logger.h"
#include "QuestEngine/Constants/Constants.h"

namespace QuestEngine::Engine {

	Engine::Engine(const int width, const int height)
		:m_window{ width, height },
		m_active_camera{ nullptr },
		m_projection_matrix {m_window },
		m_systems_manager{ m_registry_manager.get_active_registry() },
		m_ubo_manager{ m_resource_manager.get_ubo(Constants::ubo_matrices) },
		m_user_interface{ m_window.get_window() },
		m_framebuffer{ width, height, 0}{
		QUEST_INFO("Quest Engine v{}.{} Initialized\n", 0, 1)
		initialization();
	}

	void Engine::run() {
		qc_checks();
		gameloop();
	}

	void Engine::initialization() {
		init_framebuffer();
		set_active_camera(Constants::main_camera);
	}

	void Engine::init_framebuffer() {
		// Framebuffer attachments (currently one only)
		m_framebuffer.create_color_attachments(m_window.get_width(), m_window.get_height(), 1);

		// Write to all color attachments:
		m_framebuffer.set_all_color_attachments_to_write_to();
	}


	void Engine::set_active_camera(const std::string& camera_id) {
		if (auto* camera = m_resource_manager.get_camera_pointer(camera_id)) {
			m_active_camera = camera;
		}
	}

	void Engine::qc_checks() const {
		m_resource_manager.shader_qc();
	}

	void Engine::gameloop() { //TODO make const
		while (!shutdown()){
			m_window.clear_buffer();
			m_ubo_manager.run(*m_active_camera, m_projection_matrix);
			m_systems_manager.run();
			m_window.poll_events();
			TEMP_UI();
			m_window.swap_buffer();
		}
	}

	void Engine::TEMP_UI() const {
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