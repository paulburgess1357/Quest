#pragma once
#include "QuestEngine/Camera/Camera.h"
#include "QuestEngine/Camera/ProjectionMatrix.h"
#include <entt/entt.hpp>

namespace QuestEngine::ECS {

	class SystemManager {

	public:
		explicit SystemManager(entt::registry& active_registry, const Window::Window& window, Camera::Camera& camera);
		void set_active_camera(Camera::Camera& camera);
		void set_active_registry(entt::registry& registry);
		void run();

	private:
		void update() const;
		void render();

		entt::registry* m_active_registry;
		Camera::ProjectionMatrix m_projection_matrix;
		Camera::Camera* m_active_camera;
	};

} // QuestEngine::ECS