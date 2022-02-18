#pragma once
#include "QuestEngine/API/Neutral/ResourceAPI.h"
#include "QuestEngine/API/Neutral/RegistryAPI.h"

namespace QuestEngine::API::OpenGL {

	struct SphereDataStorage {
		std::vector<unsigned int> m_index_data;
		std::vector<float> m_vertex_data;
	};

	class PointLightLoader {

	public:
		explicit PointLightLoader(const unsigned int segments);
		void load_pointlight_mesh(QuestEngine::API::EngineAPI& engine_api, const ECS::RenderPass renderpass) const;


	private:
		void generate_sphere(const unsigned int segments);
		SphereDataStorage m_sphere_data_storage_pos;
		SphereDataStorage m_sphere_data_storage_pos_norm_tex;

	};

} // QuestEngine::API::OpenGL