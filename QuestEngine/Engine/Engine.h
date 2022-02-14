#pragma once
#include "QuestEngine/Using/Window.h"
#include "QuestEngine/Using/UserInterface.h"
#include "QuestEngine/Resource/ResourceManager.h"
#include "QuestEngine/ECS/Manage/RegistryManager.h"
#include "QuestEngine/ECS/Manage/SystemManager.h"
#include "QuestEngine/UniformBufferObjects/UniformBufferManager.h"
#include "QuestEngine/Camera/Camera.h"
#include "QuestEngine/Camera/ProjectionMatrix.h"
#include "QuestEngine/Using/UserInterface.h"
#include "QuestEngine/Using/Framebuffer.h"

namespace QuestEngine::Engine {

	class Engine{

	public:
		explicit Engine(const int width = 1920, const int height = 1080);
		void set_active_camera(const std::string& camera_id);
		void run();

		Resource::ResourceManager& get_resource_manager();
		ECS::RegistryManager& get_registry_manager();

	private:
		void initialization();

		void init_framebuffer();

		void qc_checks() const;
		void gameloop();

		void TEMP_UI() const;

		[[nodiscard]] bool shutdown() const;

		const Window::Window m_window;
		Camera::Camera* m_active_camera;
		Camera::ProjectionMatrix m_projection_matrix;

		Resource::ResourceManager m_resource_manager;
		ECS::RegistryManager m_registry_manager;
		ECS::SystemManager m_systems_manager;
		UniformBufferObjects::UniformBufferManager m_ubo_manager;

		UserInterface::UserInterface m_user_interface;
		Framebuffer::FramebufferStandard2D m_framebuffer;

	};

} // namespace QuestEngine::Engine