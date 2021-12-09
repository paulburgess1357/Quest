#include "pch.h"
#include "Engine.h"
#include "QuestUtility/Include/Logger.h"

namespace QuestEngine::Engine {

	Engine::Engine(const int width, const int height)
		:m_window{ width, height } {
		QUEST_INFO("Quest Engine v{}.{} Initialized\n", 0, 1);
	}

	void Engine::run() const {
		gameloop();
	}

	void Engine::gameloop() const {
		while (!shutdown()){
			m_window.poll_events();
			m_window.clear_buffer();
			m_window.swap_buffer();
		}
	}

	bool Engine::shutdown() const {
		return m_window.close_window() || KeyboardInput::is_pressed(Keyboard::ESCAPE);
	}

} // namespace QuestEngine::Engine