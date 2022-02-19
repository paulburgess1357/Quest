#pragma once
#include "QuestEngine/API/Neutral/EngineAPI.h"
#include <string>
#include <glm/glm.hpp>

namespace QuestSandbox::Tests {

	class ShapeTests {

	public:
		explicit ShapeTests(QuestEngine::API::EngineAPI& engine_api);
		void pointlight_lightvolume_test();

	private:
		void load_dual_textured_cube_into_world(const std::string& entity_id, const glm::vec3& world_position, const std::string& vertex_shader, const std::string& fragment_shader, const QuestEngine::ECS::RenderPass render_pass);

		QuestEngine::API::EngineAPI& m_engine_api;
		static const std::string m_base_shader_path;
		static const std::string m_base_texture_path;

		bool textured_cube_in_resource = false;
	};

} // QuestSandbox::Tests