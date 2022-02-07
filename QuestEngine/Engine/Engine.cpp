#include "pch.h"
#include "Engine.h"
#include "QuestEngine/ECS/Systems/RenderSystem.h"
#include "QuestEngine/ECS/Systems/TransformSystem.h"
#include "QuestUtility/Logging/LogMacros.h"

namespace QuestEngine::Engine {

	Engine::Engine(const int width, const int height)
		:m_window{ width, height },
		m_projection_matrix{ m_window },
		m_active_camera{ nullptr }{
		initialize();
		QUEST_INFO("Quest Engine v{}.{} Initialized\n", 0, 1)
	}

	void Engine::initialize() {
		init_camera();
	}

	void Engine::run() { //TODO make const
		qc_checks();
		gameloop();
	}

	void Engine::qc_checks() const {
		m_resource_manager.shader_qc();
	}

	void Engine::gameloop() { //TODO make const
		while (!shutdown()){
			m_window.clear_buffer();
			update();
			render();
			m_window.swap_buffer();
			m_window.poll_events();
		}
	}

	void Engine::update() const {
		ECS::Systems::TransformSystem::transform(m_registry);
	}

	void Engine::render() {
		ECS::Systems::RenderSystem::render(m_registry, m_projection_matrix, *m_active_camera);
	}

	void Engine::init_camera() {
		const std::string camera_id{ "Main Camera" };
		m_resource_manager.load_camera(camera_id, { 0.0f, 0.0f, -6.0f }, { 0.0f, 0.0f, 0.0f });
		set_active_camera(camera_id);
	}

	void Engine::set_active_camera(const std::string& camera_id) {
		if(auto* camera = m_resource_manager.get_camera_pointer(camera_id)) {
			m_active_camera = camera;
		}
	}

	bool Engine::shutdown() const {
		return m_window.close_window() || Window::KeyboardInput::is_pressed(Window::Keyboard::ESCAPE);
	}

} // namespace QuestEngine::Engine