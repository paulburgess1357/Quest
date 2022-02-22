// ReSharper disable CppClangTidyClangDiagnosticExitTimeDestructors
// ReSharper disable CppClangTidyConcurrencyMtUnsafe
// ReSharper disable CppClangTidyBugproneNarrowingConversions
// ReSharper disable CppClangTidyClangDiagnosticDoublePromotion

#include "ShapeTests.h"
#include "QuestEngine/API/OpenGL/ShaderLoaderAPI.h"
#include "QuestEngine/API/OpenGL/ModelLoaderAPI.h"
#include "QuestEngine/API/Neutral/Constants.h"
#include "QuestEngine/API/Neutral/Constants.h"

namespace QuestSandbox::Tests {
	
    const std::string ShapeTests::m_base_shader_path{"../Resources/Shaders/"};
	const std::string ShapeTests::m_base_texture_path{ "../Resources/Textures/" };

    ShapeTests::ShapeTests(QuestEngine::API::EngineAPI& engine_api)
        :m_engine_api{ engine_api } {
    }

	void ShapeTests::pointlight_lightvolume_test() {

		// ========== Load test textured cube into world ==========
		// Load Textured Cube ECS Entity into world::
		constexpr int BOX_QTY = 12;
		for (unsigned int i = 0; i < BOX_QTY; i++) {

			const auto xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			const auto yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
			const auto zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);

			const std::string entity_id = "Textured_Cube" + std::to_string(i);
			load_dual_textured_cube_into_world(entity_id, { xPos , yPos, zPos }, QuestEngine::ECS::RenderPass::Deferred);
		}

		// ================= Set lighting pass uniforms ==================
		const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
		auto& pointlight_shader = resource_api.get_shader(QuestEngine::Constants::pointlight_shader);

		pointlight_shader.bind();

			constexpr float CONSTANT = 1.0f; // 1.0
			constexpr float pointlight_linear = 0.7f; // 0.7
			constexpr float pointlight_quadratic = 1.8f; // 1.8
			constexpr auto light_color = glm::vec3{ 0.1f, 0.1f, 0.1f };

			pointlight_shader.set_uniform("linear", pointlight_linear);
			pointlight_shader.set_uniform("quadratic", pointlight_quadratic);
			pointlight_shader.set_uniform("light_color", light_color);

			// Radius calculation below: Currently its not being used as it doesn't seem to quite capture all the light (it cuts it off)
			// Light Volume Calculation (for radius; normally should impact mesh size but currently not using it)
			// *** Calculate light volume (max distance to display light). ***
			const float max_brightness = std::fmaxf(std::fmaxf(light_color.x, light_color.y), light_color.z);
			const float radius = (-pointlight_linear + std::sqrt(pointlight_linear * pointlight_linear - 4 * pointlight_quadratic * (CONSTANT - (256.0f / 5.0f) * max_brightness))) / (2.0f * pointlight_quadratic);

			QUEST_INFO("CALCULATED RADIUS TEST: {} ; (Not being used currently due to issues with formula)", radius)
			constexpr float pointlight_radius = 5.09f;
			pointlight_shader.set_uniform("pointlight_max_radius", pointlight_radius);

			// ================= Load pointlights into world ==================
			// Both pointlight volumes and visualize pointlights are being loaded
			// Light qty (hardcoded in shader)
			constexpr int LIGHT_QTY = 5;

			// Model pointers necessary to load objects into world
			const auto pointlight_model_ptr = resource_api.get_indexed_model_pointer(QuestEngine::Constants::pointlight_model);
			const auto pointlight_visualization_model_ptr = resource_api.get_indexed_model_pointer(QuestEngine::Constants::visualize_pointlight_model);

    		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();
			for (unsigned int i = 0; i < LIGHT_QTY; i++) {

				// Calculate slightly random offsets
				const auto xPos = static_cast<float>((rand() % 100) / 100.0 * 6.0 - 3.0);
				const auto yPos = static_cast<float>((rand() % 100) / 100.0 * 6.0 - 4.0);
				const auto zPos = static_cast<float>((rand() % 100 / 100.0) * 6.0 - 3.0);
				// QUEST_TRACE("{}, {}, {}", xPos, yPos, zPos);
				pointlight_shader.set_uniform("all_lights[" + std::to_string(i) + "].light_position", glm::vec3(xPos, yPos, zPos));

				// Load mesh pointlight to wherever a light source originates
				// pointlight rendering; scaling to be the same as 'radius'
				// Not currently doing the above due to calculation of 'radius' not quite being correct
				registry_api.load_model_into_world("pointlight_" + std::to_string(i), pointlight_model_ptr, { xPos , yPos, zPos }, QuestEngine::ECS::RenderPass::Pointlight, pointlight_radius);

				// To visualize pointlights
				// Load as deferred (in addition to the above)
				// Could be deferred or forward to make them show up; Deferred will have scene lighting
				// Scaling to be tiny as we just need to visualize it
				registry_api.load_model_into_world("visual_pointlight_" + std::to_string(i), pointlight_visualization_model_ptr, { xPos , yPos, zPos }, QuestEngine::ECS::RenderPass::Forward,  0.2f); 
			}

		pointlight_shader.unbind();
	}

	void ShapeTests::load_dual_textured_cube_into_world(const std::string& entity_id, const glm::vec3& world_position, const QuestEngine::ECS::RenderPass render_pass) {

		const std::string model_entity_id{ "Textured Indexed Shape Model Entity" };
		if (!textured_cube_in_resource) {

			const std::vector<float> vertices = {
				// Vertices               // Normals		     // Textures
				// back face
				 0.5f, -0.5f, -0.5f,        0.0f,  0.0f, -1.0f,     0.0f, 0.0f, // bottom left	
				-0.5f, -0.5f, -0.5f,        0.0f,  0.0f, -1.0f,     1.0f, 0.0f, // bottom right
				-0.5f,  0.5f, -0.5f,        0.0f,  0.0f, -1.0f,     1.0f, 1.0f, // top right
				 0.5f,  0.5f, -0.5f,        0.0f,  0.0f, -1.0f,     0.0f, 1.0f, // top left

				// front face
				-0.5f, -0.5f,  0.5f,		0.0f,  0.0f, 1.0f,     0.0f, 0.0f, // bottom left
				 0.5f, -0.5f,  0.5f,		0.0f,  0.0f, 1.0f,     1.0f, 0.0f, // bottom right
				 0.5f,  0.5f,  0.5f,		0.0f,  0.0f, 1.0f,     1.0f, 1.0f, // top right
				-0.5f,  0.5f,  0.5f,		0.0f,  0.0f, 1.0f,     0.0f, 1.0f, // top left

				// left face
				-0.5f, -0.5f, -0.5f,		-1.0f,  0.0f,  0.0f,     0.0f, 0.0f, // bottom left
				-0.5f, -0.5f,  0.5f,		-1.0f,  0.0f,  0.0f,     1.0f, 0.0f, // bottom right
				-0.5f,  0.5f,  0.5f,		-1.0f,  0.0f,  0.0f,     1.0f, 1.0f, // top right
				-0.5f,  0.5f, -0.5f,		-1.0f,  0.0f,  0.0f,     0.0f, 1.0f, // top left	   

				// right face
				 0.5f, -0.5f,  0.5f,		1.0f,  0.0f,  0.0f,     0.0f, 0.0f, // bottom left
				 0.5f, -0.5f, -0.5f,		1.0f,  0.0f,  0.0f,     1.0f, 0.0f, // bottom right
				 0.5f,  0.5f, -0.5f,		1.0f,  0.0f,  0.0f,     1.0f, 1.0f, // top right	
				 0.5f,  0.5f,  0.5f,		1.0f,  0.0f,  0.0f,     0.0f, 1.0f, // top left

				// bottom face
				-0.5f, -0.5f, -0.5f,		0.0f, -1.0f,  0.0f,     0.0f, 0.0f, // bottom left
				 0.5f, -0.5f, -0.5f,		0.0f, -1.0f,  0.0f,     1.0f, 0.0f, // bottom right
				 0.5f, -0.5f,  0.5f,		0.0f, -1.0f,  0.0f,     1.0f, 1.0f, // top right
				-0.5f, -0.5f,  0.5f,		0.0f, -1.0f,  0.0f,     0.0f, 1.0f, // top left

				// top face
				-0.5f,  0.5f,  0.5f,		0.0f,  1.0f,  0.0f,     0.0f, 0.0f, // bottom left
				 0.5f,  0.5f,  0.5f,		0.0f,  1.0f,  0.0f,     1.0f, 0.0f, // bottom right
				 0.5f,  0.5f, -0.5f,		0.0f,  1.0f,  0.0f,     1.0f, 1.0f, // top right
				-0.5f,  0.5f, -0.5f,		0.0f,  1.0f,  0.0f,     0.0f, 1.0f, // top left
			};

			const std::vector<unsigned int> indices = {
				// back face
				0, 1, 2,
				2, 3, 0,

				// front face
				4, 5, 6,
				6, 7, 4,

				// left face
				8, 9, 10,
				10, 11, 8,

				// right face
				12, 13, 14,
				14, 15, 12,

				// bottom face
				16, 17, 18,
				18, 19, 16,

				// top face
				20, 21, 22,
				22, 23, 20
			};

			// Load created model into resource
			const QuestEngine::API::OpenGL::ModelLoaderAPI model_loader = m_engine_api.get_model_loader_api();
			model_loader.load_model(model_entity_id, QuestEngine::Constants::standard_object_shader, { vertices }, { indices }, { 3, 3, 2 }, QuestGLCore::Model::ModelDrawMode::Triangles);

			// Get pointer to loaded model
			const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
			QuestEngine::Model::IndexedModel* model_pointer = resource_api.get_indexed_model_pointer(model_entity_id);

			// Texture Model

			// Load texture into resource
			const std::string texture_id_in_resource{ "wood_texture" };

			const auto texture_api = m_engine_api.get_texture_loader_api();
			texture_api.load_texture2D(texture_id_in_resource, m_base_texture_path + "wood.png", QuestEngine::Texture::TextureType::Standard, false, true);
			const auto texture_ptr = resource_api.get_texture_pointer(texture_id_in_resource);

			auto& mesh_vector = model_pointer->get_mesh_vector();
			QuestGLCore::Shader::ShaderProgram* model_shader_program = model_pointer->get_shader_program();

			// For each mesh, register the texture
			for (auto& model_mesh : mesh_vector) {
				model_mesh.register_texture(QuestGLCore::Texture::TextureEnum::Diffuse, model_shader_program, texture_ptr);
			}

			// Load specular texture
			const std::string specular_texture_id_in_resource{ "specular_texture" };

			texture_api.load_texture2D(specular_texture_id_in_resource, m_base_texture_path + "container_specular_map.png", QuestEngine::Texture::TextureType::Standard, false, false);
			const auto specular_texture_ptr = resource_api.get_texture_pointer(specular_texture_id_in_resource);
			// For each mesh, register the texture
			for (auto& model_mesh : mesh_vector) {
				model_mesh.register_texture(QuestGLCore::Texture::TextureEnum::Specular, model_shader_program, specular_texture_ptr);
			}

			textured_cube_in_resource = true;

		}

		// Load textured cube into registry:
		const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
		QuestEngine::Model::IndexedModel* model_pointer = resource_api.get_indexed_model_pointer(model_entity_id);

		// Take loaded model and create ECS entity
		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();
		registry_api.load_model_into_world(entity_id, model_pointer, world_position, render_pass, 1.0f);
	}

} // namespace QuestSandbox::Tests