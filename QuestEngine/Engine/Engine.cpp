#include "pch.h"
#include "Engine.h"
#include "QuestUtility/Include/Logger.h"

namespace QuestEngine::Engine {

	Engine::Engine(const int width, const int height)
		:m_window{ width, height } {
		QUEST_INFO("Quest Engine v{}.{} Initialized\n", 0, 1);
	}

	void Engine::run() { //TODO make const
		gameloop();
	}

	void Engine::gameloop() { //TODO make const
		while (!shutdown()){
			m_window.clear_buffer();


			LOADED_MODEL_TEST();


			m_window.swap_buffer();
			m_window.poll_events();
		}
	}

	bool Engine::shutdown() const {
		return m_window.close_window() || Window::KeyboardInput::is_pressed(Window::Keyboard::ESCAPE);
	}

	void Engine::LOADED_MODEL_TEST() {
		// m_resource_manager.get_model("Test Model").draw(GL_TRIANGLES);
		m_resource_manager.get_indexed_model("Test Model").draw(GL_TRIANGLES); //TODO i'd prefer draw model set when i create the model
	}


} // namespace QuestEngine::Engine