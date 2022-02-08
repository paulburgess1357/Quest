#include "pch.h"
#include "SystemManager.h"
#include "QuestEngine/ECS/Systems/RenderSystem.h"
#include "QuestEngine/ECS/Systems/TransformSystem.h"

namespace QuestEngine::ECS {

	SystemManager::SystemManager(entt::registry& active_registry, const Window::Window& window, Camera::Camera& camera)
		:m_active_registry{ &active_registry },
		m_projection_matrix{ window },
		m_active_camera{ &camera }{
	}

	void SystemManager::set_active_camera(Camera::Camera& camera) {
		m_active_camera = &camera;
	}

	void SystemManager::set_active_registry(entt::registry& registry) {
		m_active_registry = &registry;
	}

	void SystemManager::run() {
		update();
		render();
	}

	void SystemManager::update() const {
		ECS::Systems::TransformSystem::transform(*m_active_registry);
	}

	void SystemManager::render() {
		ECS::Systems::RenderSystem::render(*m_active_registry, m_projection_matrix, *m_active_camera);
	}

} // namespace QuestEngine::ECS