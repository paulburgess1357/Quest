#include "pch.h"
#include "Engine.h"

namespace QuestEngine {
	namespace Engine {

		Engine::Engine(const int width, const int height)
			:m_window{ width, height } {
		}

		void Engine::run() const {
			gameloop();
		}

		void Engine::gameloop() const {

			while (!shutdown_engine()){
				m_window.poll_events();
				m_window.clear_buffer();
				m_window.swap_buffer();
			}

		}

		bool Engine::shutdown_engine() const {
			return m_window.close_window() || Qw::KeyboardInput::is_pressed(Qw::Keyboard::ESCAPE);
		}

	} // namespace Engine
} // namespace QuestEngine