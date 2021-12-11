#pragma once
#include "QuestEngine/Using/Window.h"
#include "QuestEngine/Resource/ResourceManager.h"

namespace QuestEngine::API {
	class QuestEngineAPI; 
} // namespace QuestEngine::API

namespace QuestEngine::Engine {

	class Engine{

	public:
		explicit Engine(const int width = 1920, const int height = 1080);

	private:
		void run() const;
		void gameloop() const;
		[[nodiscard]] bool shutdown() const;
		const Window m_window;

		Resource::ResourceManager m_resource_manager;


		friend class API::QuestEngineAPI;
	};

} // namespace QuestEngine::Engine