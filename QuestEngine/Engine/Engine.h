#pragma once
#include "QuestEngine/Using/Window.h"
#include "QuestEngine/Resource/ResourceManager.h"
#include "QuestEngine/ECS/Manage/RegistryManager.h"
#include "QuestEngine/ECS/Manage/SystemManager.h"

namespace QuestEngine::API {
	class QuestEngineAPI; 
} // namespace QuestEngine::API

namespace QuestEngine::Engine {

	class Engine{

	public:
		explicit Engine(const int width = 1920, const int height = 1080);
		void set_active_camera(const std::string& camera_id);

	private:
		void qc_checks() const;
		void run();
		void gameloop();

		[[nodiscard]] bool shutdown() const;

		const Window::Window m_window;

		Resource::ResourceManager m_resource_manager;
		ECS::RegistryManager m_registry_manager;
		ECS::SystemManager m_systems_manager;

		friend class API::QuestEngineAPI;

	};

} // namespace QuestEngine::Engine