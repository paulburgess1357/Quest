#pragma once
#include "QuestEngine/Logging/Log.h"
#include "QuestWindow/Include/Window.h"

namespace QuestEngine {
	namespace Engine {

		class Engine{

		public:
			Engine(const int width = 1920, const int height = 1080);
			void initialize() const;
			void run() const;

		private:
			void gameloop() const;
			[[nodiscard]] bool shutdown() const;

			const Qw::Window m_window;
			const Ql::LogManager m_logger;

		};

	} // Engine
} // namespace QuestEngine