#include "pch.h"
#include "EngineAPI.h"

namespace QuestEngine::API {

	EngineAPI::EngineAPI(const int width, const int height)
		:m_engine{ std::make_unique<Engine::Engine>(width, height) },
		m_resource_api{ m_engine.get() },
		m_registry_api{ m_engine.get() }{
	}

	void EngineAPI::run() const {
		m_engine->run();
	}

	void EngineAPI::set_active_camera(const std::string& camera_id) const {
		m_engine->set_active_camera(camera_id);
	}

	ResourceAPI& EngineAPI::get_resource_api() {
		return m_resource_api;
	}

	RegistryAPI& EngineAPI::get_registry_api() {
		return m_registry_api;
	}

} // namespace QuestEngine::API