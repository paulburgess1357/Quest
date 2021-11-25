#pragma once
#include "QuestWindow/Include/Window.h"

namespace QuestEngine {
	namespace Engine {

		class Engine{

		public:
			Engine(const int width = 1920, const int height = 1080);
			void run() const;

		private:
			void gameloop() const;
			[[nodiscard]] bool shutdown_engine() const;

			const Qw::Window m_window;

		};

	} // Engine
} // namespace QuestEngine