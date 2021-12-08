#pragma once
#include "QuestEngine/Using/Window.h"
#include "QuestEngine/Using/Resource.h"

namespace QuestEngine {
	namespace Engine {

		class Engine{

		public:
			explicit Engine(const int width = 1920, const int height = 1080);
			void run() const;

		private:
			void gameloop() const;
			[[nodiscard]] bool shutdown() const;
			const Window m_window;

			Resource::ShaderResource m_shader_resource;
		};

	} // Engine
} // namespace QuestEngine