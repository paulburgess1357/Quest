#include "pch.h"
#include "Engine.h"
#include "QuestEngine/ECS/Systems/RenderSystem.h"
#include "QuestUtility/Logging/LogMacros.h"

namespace QuestEngine::Engine {

	Engine::Engine(const int width, const int height)
		:m_window{ width, height },
		m_systems_manager{ m_registry_manager.get_active_registry(),
			              m_window,
			              m_resource_manager.get_camera("Main Camera")}{
		QUEST_INFO("Quest Engine v{}.{} Initialized\n", 0, 1)
	}

	void Engine::set_active_camera(const std::string& camera_id) {
		if (auto* camera = m_resource_manager.get_camera_pointer(camera_id)) {
			m_systems_manager.set_active_camera(*camera);
		}
	}

	void Engine::run() {
		qc_checks();
		gameloop();
	}

	void Engine::qc_checks() const {
		m_resource_manager.shader_qc();
	}

	void Engine::gameloop() { //TODO make const
		while (!shutdown()){
			m_window.clear_buffer();
			m_systems_manager.run();
			m_window.swap_buffer();
			m_window.poll_events();
		}
	}

	bool Engine::shutdown() const {
		return m_window.close_window() || Window::KeyboardInput::is_pressed(Window::Keyboard::ESCAPE);
	}

} // namespace QuestEngine::Engine