#pragma
#include "QuestWindow/Include/Window.h"

namespace QuestEngine {
	namespace Engine {

		class Engine{

		public:
			explicit Engine(const int width = 1920, const int height = 1080);
			void run() const;

		private:
			void gameloop() const;
			[[nodiscard]] bool shutdown() const;
			const QuestWindow::Window m_window;
		};

	} // Engine
} // namespace QuestEngine