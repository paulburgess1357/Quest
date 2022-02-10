#pragma once
#include <entt/entt.hpp>

namespace QuestEngine::ECS {

	class SystemManager {

	public:
		explicit SystemManager(entt::registry& active_registry);
		
		void set_active_registry(entt::registry& registry);
		void run() const;

	private:
		void update() const;
		void render() const;

		entt::registry* m_active_registry;
	};

} // QuestEngine::ECS