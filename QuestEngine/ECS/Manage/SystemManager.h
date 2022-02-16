#pragma once
#include <entt/entt.hpp>
#include "QuestEngine/Camera/Camera.h"

namespace QuestEngine::ECS {

	class SystemManager {

	public:
		explicit SystemManager(entt::registry& active_registry);
		void set_active_registry(entt::registry& registry);
		void update(const Camera::Camera& camera) const;
		void draw_deferred() const;
		void draw_forward() const;
	private:
		entt::registry* m_active_registry;
	};

} // QuestEngine::ECS