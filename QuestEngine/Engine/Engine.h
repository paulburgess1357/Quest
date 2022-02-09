#pragma once
#include "QuestEngine/Using/Window.h"
#include "QuestEngine/Resource/ResourceManager.h"
#include "QuestEngine/ECS/Manage/RegistryManager.h"
#include "QuestEngine/ECS/Manage/SystemManager.h"

namespace QuestEngine::Engine {

	class Engine{

	public:
		explicit Engine(const int width = 1920, const int height = 1080);
		void set_active_camera(const std::string& camera_id);
		void run();

		Resource::ResourceManager& get_resource_manager();
		ECS::RegistryManager& get_registry_manager();

	private:
		void qc_checks() const;
		void gameloop();
		[[nodiscard]] bool shutdown() const;

		const Window::Window m_window;
		Resource::ResourceManager m_resource_manager;
		ECS::RegistryManager m_registry_manager;
		ECS::SystemManager m_systems_manager;

	};

} // namespace QuestEngine::Engine