#pragma once
#include "QuestEngine/Engine/Engine.h"
#include "QuestEngine/API/Neutral/RegistryAPI.h"
#include "QuestEngine/API/Neutral/ResourceAPI.h"
#include "QuestEngine/Using/API.h"
#include <memory>

namespace QuestEngine::API {

	class EngineAPI {

	public:
		explicit EngineAPI(const int width = 1920, const int height = 1080);
		void run() const;
		void set_active_camera(const std::string& camera_id) const;

		ResourceAPI& get_resource_api();
		RegistryAPI& get_registry_api();
		ModelLoaderAPI& get_model_loader_api();
		ShaderLoaderAPI& get_shader_loader_api();
		TextureLoaderAPI& get_texture_loader_api();

	private:
		std::unique_ptr<Engine::Engine> m_engine{ nullptr };
		ResourceAPI m_resource_api{ nullptr };
		RegistryAPI m_registry_api{ nullptr };
		ModelLoaderAPI m_model_loader_api{ nullptr };
		ShaderLoaderAPI m_shader_loader_api{ nullptr };
		TextureLoaderAPI m_texture_loader_api{ nullptr };

	};

} // namespace QuestEngine::API