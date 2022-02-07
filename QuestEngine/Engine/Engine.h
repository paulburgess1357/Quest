#pragma once
#include "QuestEngine/Using/Window.h"
#include "QuestEngine/Resource/ResourceManager.h"
#include "QuestEngine/Camera/ProjectionMatrix.h"
#include "entt/entity/registry.hpp"

namespace QuestEngine::API {
	class QuestEngineAPI; 
} // namespace QuestEngine::API

namespace QuestEngine::Engine {

	class Engine{

	public:
		explicit Engine(const int width = 1920, const int height = 1080);

	private:
		void initialize();
		void qc_checks() const;

		void run();
		void gameloop();
		void update() const;
		void render();

		void init_camera();
		void set_active_camera(const std::string& camera_id);

		[[nodiscard]] bool shutdown() const;

		const Window::Window m_window;
		Camera::ProjectionMatrix m_projection_matrix;
		Camera::Camera* m_active_camera;

		Resource::ResourceManager m_resource_manager;
		entt::registry m_registry;

		friend class API::QuestEngineAPI;

	};

} // namespace QuestEngine::Engine