#include "pch.h"
#include "PointLightLoaderAPI.h"
#include "QuestEngine/API/OpenGL/ModelLoaderAPI.h"
#include "QuestEngine/API/Neutral/Constants.h"
#include "QuestEngine/ECS/Manage/RegistryManagerExecptions.h"
#include "QuestUtility/Sphere/Sphere.h"

namespace QuestEngine::API::OpenGL {

	PointLightLoader::PointLightLoader(const unsigned int segments) {
		generate_sphere(segments);
	}

	void PointLightLoader::load_pointlight_mesh(QuestEngine::API::EngineAPI& engine_api, const ECS::RenderPass renderpass) const {

		// Load pointlight into resource
		const QuestEngine::API::OpenGL::ModelLoaderAPI model_loader = engine_api.get_model_loader_api();
		const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = engine_api.get_shader_loader_api();

		switch (renderpass) {
			case ECS::RenderPass::Deferred: {
				const std::string pointlight_id{ "temp_pointlight_deferred" };
				shader_loader.load_shader(pointlight_id + "_shader", "../Resources/Shader/GBuffer/GBufferShapeVertexGeometryPass.glsl", "../Resources/Shader/GBuffer/GBufferShapeFragmentGeometryPass.glsl", true, true); // from file: true; load_ubo_matrices: true
				model_loader.load_model<GL_TRIANGLE_STRIP>(pointlight_id, pointlight_id + "_shader", {m_sphere_data_storage_pos_norm_tex.m_vertex_data}, {m_sphere_data_storage_pos_norm_tex.m_index_data}, {3, 3, 2});
				break;
			}
			case ECS::RenderPass::Pointlight: {
				// Engine loads pointlight shader by default
				const std::string resource_id { Constants::pointlight_model };
				model_loader.load_model<GL_TRIANGLE_STRIP>(resource_id, Constants::pointlight_shader, { m_sphere_data_storage_pos.m_vertex_data }, { m_sphere_data_storage_pos.m_index_data }, { 3 });
				break;
			}
			case ECS::RenderPass::Forward: {
				const std::string pointlight_id{ "temp_pointlight_forward_shader" };
				shader_loader.load_shader(pointlight_id + "_shader", "../Resources/Shaders/ForwardPass/ForwardPassVertex.glsl", "../Resources/Shaders/ForwardPass/ForwardPassFragment.glsl", true, true); // from file: true; load_ubo_matrices: true
				model_loader.load_model<GL_TRIANGLE_STRIP>(pointlight_id, pointlight_id + "_shader", { m_sphere_data_storage_pos_norm_tex.m_vertex_data }, { m_sphere_data_storage_pos_norm_tex.m_index_data }, { 3, 3, 2 });
				break;
			}
			default: {
				QUEST_ERROR("You are trying to load a pointlight with an invalid Renderpass enum!")
					throw ECS::EntityLoadRenderPassException();
			}
		}
	}

	void PointLightLoader::generate_sphere(const unsigned int segments) {

		// *********** Temp until model loading is added ***********
		Sphere sphere(1.0f, 36, 18); // radius = 1, sectors = 36, stacks = 18, smooth = true (default)









	//	const float pi = 3.14159265359f;
	//	std::vector<glm::vec3> positions;
	//	std::vector<glm::vec2> texture_coords;
	//	std::vector<glm::vec3> normals;

	//	for (unsigned int x = 0; x <= segments; ++x) {
	//		for (unsigned int y = 0; y <= segments; ++y) {
	//			const float x_segment = static_cast<float>(x) / static_cast<float>(segments);
	//			const float y_segment = static_cast<float>(y) / static_cast<float>(segments);
	//			const float x_pos = std::cos(x_segment * 2.0f * pi) * std::sin(y_segment * pi);
	//			const float y_pos = std::cos(y_segment * pi);
	//			const float z_pos = std::sin(x_segment * 2.0f * pi) * std::sin(y_segment * pi);

	//			positions.emplace_back(glm::vec3(x_pos, y_pos, z_pos));
	//			texture_coords.emplace_back(glm::vec2(x_segment, y_segment));
	//			normals.emplace_back(glm::vec3(x_pos, y_pos, z_pos));
	//		}
	//	}

	//	bool odd_row = false;
	//	const int segments_int = static_cast<int>(segments);
	//	for (unsigned int y = 0; y < segments; ++y) {
	//		if (!odd_row) {
	//			for (unsigned int x = 0; x <= segments; ++x) {
	//				m_sphere_data_storage_pos_norm_tex.m_index_data.push_back(y * (segments + 1) + x);
	//				m_sphere_data_storage_pos_norm_tex.m_index_data.push_back((y + 1) * (segments + 1) + x);

	//				m_sphere_data_storage_pos.m_index_data.push_back(y * (segments + 1) + x);
	//				m_sphere_data_storage_pos.m_index_data.push_back((y + 1) * (segments + 1) + x);
	//			}
	//		} else {
	//			for (int x = segments_int; x >= 0; --x) {
	//				m_sphere_data_storage_pos_norm_tex.m_index_data.push_back((y + 1) * (segments + 1) + x);
	//				m_sphere_data_storage_pos_norm_tex.m_index_data.push_back(y * (segments + 1) + x);

	//				m_sphere_data_storage_pos.m_index_data.push_back((y + 1) * (segments + 1) + x);
	//				m_sphere_data_storage_pos.m_index_data.push_back(y * (segments + 1) + x);
	//			}
	//		}
	//		odd_row = !odd_row;
	//	}

	//	for (unsigned int i = 0; i < positions.size(); ++i) {

	//		// Position Only
	//		m_sphere_data_storage_pos.m_vertex_data.push_back(positions[i].x);
	//		m_sphere_data_storage_pos.m_vertex_data.push_back(positions[i].y);
	//		m_sphere_data_storage_pos.m_vertex_data.push_back(positions[i].z);

	//		// Position, Normals, Textures
	//		m_sphere_data_storage_pos_norm_tex.m_vertex_data.push_back(positions[i].x);
	//		m_sphere_data_storage_pos_norm_tex.m_vertex_data.push_back(positions[i].y);
	//		m_sphere_data_storage_pos_norm_tex.m_vertex_data.push_back(positions[i].z);

	//		m_sphere_data_storage_pos_norm_tex.m_vertex_data.push_back(normals[i].x);
	//		m_sphere_data_storage_pos_norm_tex.m_vertex_data.push_back(normals[i].y);
	//		m_sphere_data_storage_pos_norm_tex.m_vertex_data.push_back(normals[i].z);

	//		m_sphere_data_storage_pos_norm_tex.m_vertex_data.push_back(texture_coords[i].x);
	//		m_sphere_data_storage_pos_norm_tex.m_vertex_data.push_back(texture_coords[i].y);
	//	}
	//}

} // QuestEngine::API::OpenGL