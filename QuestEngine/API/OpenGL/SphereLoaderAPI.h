#pragma once
#include "QuestUtility/Sphere/Sphere.h"
#include "QuestEngine/Using/Model.h"

namespace QuestEngine::API::OpenGL {

	class SphereLoader {

	public:
		explicit SphereLoader(const float radius, const int sectors, const int stacks, const bool smooth = true);
		void load_sphere_into_resource(QuestEngine::API::EngineAPI& engine_api, const std::string& sphere_resource_id, const std::string& loaded_shader_id, const bool position_only, const Model::ModelDrawMode draw_mode) const;
		void load_default_textured_sphere_into_resource(QuestEngine::API::EngineAPI& engine_api, const std::string& sphere_resource_id, const std::string& loaded_shader_id, const Model::ModelDrawMode draw_mode) const;

	private:
		Sphere m_sphere;
	};

} // QuestEngine::API::OpenGL