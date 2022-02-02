#pragma once
#include "QuestEngine/Using/Window.h"
#include "QuestEngine/Resource/ResourceManager.h"
#include "QuestEngine/Camera/ProjectionMatrix.h"

namespace QuestEngine::API {
	class QuestEngineAPI; 
} // namespace QuestEngine::API

namespace QuestEngine::Engine {

	class Engine{

	public:
		explicit Engine(const int width = 1920, const int height = 1080);

	private:
		void run();
		void gameloop();
		[[nodiscard]] bool shutdown() const;

		void LOADED_MODEL_TEST();

		const Window::Window m_window;
		Resource::ResourceManager m_resource_manager;

		Camera::ProjectionMatrix m_projection_matrix;


		friend class API::QuestEngineAPI;
	};

} // namespace QuestEngine::Engine