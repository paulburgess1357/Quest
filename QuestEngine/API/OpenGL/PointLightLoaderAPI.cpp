#include "pch.h"
#include "PointLightLoaderAPI.h"
#include "QuestEngine/API/OpenGL/ModelLoaderAPI.h"
#include "QuestEngine/API/Neutral/Constants.h"

namespace QuestEngine::API::OpenGL {

	PointLightLoader::PointLightLoader(const unsigned int segments) {
		generate_sphere(segments);
	}

	// TODO MY POINTLIGHT SHADER PROGRAM IS INCORRECT.  iN THE ENGINE, I AM USING THE SHADER MEANT FOR DEFERRED OBJECTS ONLY (THEY WRITE
	// todo TO TEXTURE ATTACHMENTS).  i UNBIND THE G-BUFFER.  I THEN BIND THE POST-PROCESS FRAMEBUFFER.  WHEN I RENDER THE POINTLIGHTS,
	// TODO, I AM USING A SHADER THAT WRITES TO 3 TEXTURES, BUT, THE FRAMEBUFFER DOESN'T EXPECT THOSE TEXTURES TO BE WRITTEN TO.
	// TODO I THINK I JUST NEED TO UPDATE THE POINTLIGHT SHADER TO BE SOMETHING MORE NORMAL. BOTH THE LAYOUT AND THE ACTUAL CODE IN MAIN.

	void PointLightLoader::load_pointlight_mesh(QuestEngine::API::EngineAPI& engine_api) const {
		const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = engine_api.get_shader_loader_api();
		const std::string shader_id{ Constants::g_buffer_light_pass }; // Constants::pointlight_shader

		// if you want to load into deferred pipeline...
		// shader_loader.load_shader(shader_id, "../Resources/Shaders/GBuffer/GBufferShapeVertexGeometryPassNoTexture.glsl", "../Resources/Shaders/GBuffer/GBufferShapeFragmentGeometryPassNoTexture.glsl", true, true);

		// shader for light pass geometry
		// this draws the light stuff....
		// shader_loader.load_shader(shader_id, "../Resources/Shaders/GBuffer/GBufferVertexLightPass_POINTLIGHT.glsl", "../Resources/Shaders/GBuffer/GBufferFragmentLightPass.glsl", true, true);


		// Load pointlight into resource
		const std::string model_entity_id{ Constants::pointlight_model };
		const QuestEngine::API::OpenGL::ModelLoaderAPI model_loader = engine_api.get_model_loader_api();
		model_loader.load_model<GL_TRIANGLE_STRIP>(model_entity_id, shader_id, { m_sphere_data_storage.m_vertex_data }, { m_sphere_data_storage.m_index_data }, { 3, 3, 2 });
	}

	void PointLightLoader::generate_sphere(const unsigned int segments) {

		// *********************************************************
		// *********************************************************
		// *********** Temp until model loading is added ***********
		// *********************************************************
		// *********************************************************

		const float pi = 3.14159265359f;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> texture_coords;
		std::vector<glm::vec3> normals;

		for (unsigned int x = 0; x <= segments; ++x) {
			for (unsigned int y = 0; y <= segments; ++y) {
				const float x_segment = static_cast<float>(x) / static_cast<float>(segments);
				const float y_segment = static_cast<float>(y) / static_cast<float>(segments);
				const float x_pos = std::cos(x_segment * 2.0f * pi) * std::sin(y_segment * pi);
				const float y_pos = std::cos(y_segment * pi);
				const float z_pos = std::sin(x_segment * 2.0f * pi) * std::sin(y_segment * pi);

				positions.emplace_back(glm::vec3(x_pos, y_pos, z_pos));
				texture_coords.emplace_back(glm::vec2(x_segment, y_segment));
				normals.emplace_back(glm::vec3(x_pos, y_pos, z_pos));
			}
		}

		bool odd_row = false;
		const int segments_int = static_cast<int>(segments);
		for (unsigned int y = 0; y < segments; ++y) {
			if (!odd_row) {
				for (unsigned int x = 0; x <= segments; ++x) {
					m_sphere_data_storage.m_index_data.push_back(y * (segments + 1) + x);
					m_sphere_data_storage.m_index_data.push_back((y + 1) * (segments + 1) + x);
				}
			} else {
				for (int x = segments_int; x >= 0; --x) {
					m_sphere_data_storage.m_index_data.push_back((y + 1) * (segments + 1) + x);
					m_sphere_data_storage.m_index_data.push_back(y * (segments + 1) + x);
				}
			}
			odd_row = !odd_row;
		}

		for (unsigned int i = 0; i < positions.size(); ++i) {
			m_sphere_data_storage.m_vertex_data.push_back(positions[i].x);
			m_sphere_data_storage.m_vertex_data.push_back(positions[i].y);
			m_sphere_data_storage.m_vertex_data.push_back(positions[i].z);
			if (!normals.empty()) {
				m_sphere_data_storage.m_vertex_data.push_back(normals[i].x);
				m_sphere_data_storage.m_vertex_data.push_back(normals[i].y);
				m_sphere_data_storage.m_vertex_data.push_back(normals[i].z);
			}
			if (!texture_coords.empty()) {
				m_sphere_data_storage.m_vertex_data.push_back(texture_coords[i].x);
				m_sphere_data_storage.m_vertex_data.push_back(texture_coords[i].y);
			}
		}
	}

} // QuestEngine::API::OpenGL