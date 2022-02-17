// ReSharper disable CppClangTidyClangDiagnosticExitTimeDestructors
#include "ShapeTests.h"
#include "QuestEngine/API/OpenGL/ShaderLoaderAPI.h"
#include "QuestEngine/API/OpenGL/ModelLoaderAPI.h"
#include "QuestEngine/API/Neutral/Constants.h"
#include "QuestEngine/API/OpenGL/PointLightLoaderAPI.h"
#include "QuestEngine/API/Neutral/Constants.h"

namespace QuestSandbox::Tests {
	
    const std::string ShapeTests::m_base_shader_path{"../Resources/Shaders/"};
	const std::string ShapeTests::m_base_texture_path{ "../Resources/Textures/" };

    ShapeTests::ShapeTests(QuestEngine::API::EngineAPI& engine_api)
        :m_engine_api{ engine_api } {
    }

	void ShapeTests::g_buffer_lighting_test_pointlight_mesh_volume() {

		// This renders pointlight spheres so they are visible. This does not
		// use spherical pointlight shader volume shading.  Pointlight spheres
		// are still loaded as 'deferred' rather than 'pointlight' render pass

		// GBuffer Shader (for textured cube): GBufferShapeVertexGeometryPass
		// LightPass Shader: GBufferVertexLightPass
		// PostProcess Quad (string): Gamma correction

		// This is using the post process quad to adjust lighting RATHER
		// than the pointlight sphere area.

		constexpr int LIGHT_AND_BOX_QTY = 12;
		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();

		// ========== Load test textured cube into resource ==========
		// Load Textured Cube ECS Entity into world::
		constexpr int BOX_QTY = LIGHT_AND_BOX_QTY;
		for (unsigned int i = 0; i < BOX_QTY; i++) {

			const auto xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			const auto yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
			const auto zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			load_dual_textured_cube_into_world({ xPos , yPos, zPos }, m_base_shader_path + "/GBuffer/GBufferShapeVertexGeometryPass.glsl", m_base_shader_path + "/GBuffer/GBufferShapeFragmentGeometryPass.glsl", QuestEngine::ECS::RenderPass::Deferred);
		}


		// ========== Load G-Buffer Light Pass Shader ==========
		const std::string light_pass_shader_id{ QuestEngine::Constants::g_buffer_light_pass };
		const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = m_engine_api.get_shader_loader_api();
		shader_loader.load_shader(light_pass_shader_id, m_base_shader_path + "GBuffer/GBufferVertexLightPass.glsl", m_base_shader_path + "GBuffer/GBufferFragmentLightPass.glsl", true, true); // from_file: true; link_ubo_matrices: true

		const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
    	QuestGLCore::Shader::ShaderProgram& g_buffer_light_pass_shader_program = resource_api.get_shader(light_pass_shader_id);


		// ========== Load pointlight mesh into resource ==========
		const QuestEngine::API::OpenGL::PointLightLoader pointlight_loader(10);
		pointlight_loader.load_pointlight_mesh(m_engine_api);
		const auto pointlight_model_ptr = resource_api.get_indexed_model_pointer(QuestEngine::Constants::pointlight_model);


		// ========== Load pointlight into resource alongside light center locations ===========
    	// TODO: Currently just setting a constant sphere mesh size for now.  Normally it needs to based on attenuation

		g_buffer_light_pass_shader_program.bind();

		// Lights (hardcoded in shader)
		constexpr int LIGHT_QTY = LIGHT_AND_BOX_QTY;
		for (unsigned int i = 0; i < LIGHT_QTY; i++) {

			// calculate slightly random offsets
			const auto xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			const auto yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
			const auto zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			g_buffer_light_pass_shader_program.set_uniform("all_lights[" + std::to_string(i) + "].light_position", glm::vec3(xPos, yPos + 2.0f, zPos));

			// also calculate random color
			const auto rColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			const auto gColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			const auto bColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			g_buffer_light_pass_shader_program.set_uniform("all_lights[" + std::to_string(i) + "].color", glm::vec3(1.0, 1.0, 1.0)); // Setting all to white for now

			// Load mesh pointlight to wherever a light source originates
			registry_api.load_model_into_world("pointlight_" + std::to_string(i), pointlight_model_ptr, { xPos , yPos, zPos }, QuestEngine::ECS::RenderPass::Deferred); // deferred rendering

		}


		// ================= Set lighting pass uniforms ==================
		constexpr float CONSTANT = 1.0f;
		constexpr float pointlight_linear = 0.7f;
		constexpr float pointlight_quadratic = 1.8f;
		g_buffer_light_pass_shader_program.set_uniform("linear", pointlight_linear);
		g_buffer_light_pass_shader_program.set_uniform("quadratic", pointlight_quadratic);

		// ======== Light Volume Calculation (for radius; normally should impact mesh size but currently not using it)
		// *** Calculate light volume (max distance to display light). ***
		// Note: This 'max_brightness' calculation clearly isn't necessary.  However, if you had a light color that was different than white, we would need the max r/g/b value for max_brightness.
		const float max_brightness = std::fmaxf(std::fmaxf(1.0f, 1.0f), 1.0f);
		const float radius = (-pointlight_linear + std::sqrt(pointlight_linear * pointlight_linear - 4 * pointlight_quadratic * (CONSTANT - (256.0f / 5.0f) * max_brightness))) / (2.0f * pointlight_quadratic);
		g_buffer_light_pass_shader_program.set_uniform("pointlight_max_radius", radius);
		g_buffer_light_pass_shader_program.unbind();
	}

	void ShapeTests::g_buffer_lighting_pointlight_volume() {

    	// Pointlight spheres are still loaded as 'pointlight' render pass

		// GBuffer Shader (for textured cube): GBufferShapeVertexGeometryPass
		// LightPass Shader: GBufferVertexLightPass
		// PostProcess Quad (string): Gamma correction

		constexpr int LIGHT_AND_BOX_QTY = 12;
		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();

		// ========== Load test textured cube into resource ==========
		// Load Textured Cube ECS Entity into world::
		constexpr int BOX_QTY = LIGHT_AND_BOX_QTY;
		for (unsigned int i = 0; i < BOX_QTY; i++) {

			const auto xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			const auto yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
			const auto zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			load_dual_textured_cube_into_world({ xPos , yPos, zPos }, m_base_shader_path + "/GBuffer/GBufferShapeVertexGeometryPass.glsl", m_base_shader_path + "/GBuffer/GBufferShapeFragmentGeometryPass.glsl", QuestEngine::ECS::RenderPass::Deferred);
		}


		// ========== Load G-Buffer Light Pass Shader ==========
		const std::string light_pass_shader_id{ QuestEngine::Constants::g_buffer_light_pass };
		const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = m_engine_api.get_shader_loader_api();
		shader_loader.load_shader(light_pass_shader_id, m_base_shader_path + "GBuffer/GBufferVertexLightPass.glsl", m_base_shader_path + "GBuffer/GBufferFragmentLightPass.glsl", true, true); // from_file: true; link_ubo_matrices: true

		const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
		QuestGLCore::Shader::ShaderProgram& g_buffer_light_pass_shader_program = resource_api.get_shader(light_pass_shader_id);


		// ========== Load pointlight mesh into resource ==========
		const QuestEngine::API::OpenGL::PointLightLoader pointlight_loader(10);
		pointlight_loader.load_pointlight_mesh(m_engine_api);
		const auto pointlight_model_ptr = resource_api.get_indexed_model_pointer(QuestEngine::Constants::pointlight_model);


		// ========== Load pointlight into resource alongside light center locations ===========
		// TODO: Currently just setting a constant sphere mesh size for now.  Normally it needs to based on attenuation

		g_buffer_light_pass_shader_program.bind();

		// Lights (hardcoded in shader)
		constexpr int LIGHT_QTY = LIGHT_AND_BOX_QTY;
		for (unsigned int i = 0; i < LIGHT_QTY; i++) {

			// calculate slightly random offsets
			const auto xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			const auto yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
			const auto zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			g_buffer_light_pass_shader_program.set_uniform("all_lights[" + std::to_string(i) + "].light_position", glm::vec3(xPos, yPos, zPos));

			// also calculate random color
			const auto rColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			const auto gColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			const auto bColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			g_buffer_light_pass_shader_program.set_uniform("all_lights[" + std::to_string(i) + "].color", glm::vec3(1.0, 1.0, 1.0)); // Setting all to white for now

			// Load mesh pointlight to wherever a light source originates
			registry_api.load_model_into_world("pointlight_" + std::to_string(i), pointlight_model_ptr, { xPos , yPos, zPos }, QuestEngine::ECS::RenderPass::Pointlight); // pointlight rendering

		}


		// ================= Set lighting pass uniforms ==================
		constexpr float CONSTANT = 1.0f;
		constexpr float pointlight_linear = 0.7f;
		constexpr float pointlight_quadratic = 1.8f;
		g_buffer_light_pass_shader_program.set_uniform("linear", pointlight_linear);
		g_buffer_light_pass_shader_program.set_uniform("quadratic", pointlight_quadratic);

		// ======== Light Volume Calculation (for radius; normally should impact mesh size but currently not using it)
		// *** Calculate light volume (max distance to display light). ***
		// Note: This 'max_brightness' calculation clearly isn't necessary.  However, if you had a light color that was different than white, we would need the max r/g/b value for max_brightness.
		const float max_brightness = std::fmaxf(std::fmaxf(1.0f, 1.0f), 1.0f);
		const float radius = (-pointlight_linear + std::sqrt(pointlight_linear * pointlight_linear - 4 * pointlight_quadratic * (CONSTANT - (256.0f / 5.0f) * max_brightness))) / (2.0f * pointlight_quadratic);
		g_buffer_light_pass_shader_program.set_uniform("pointlight_max_radius", radius);
		g_buffer_light_pass_shader_program.unbind();
	}


	void ShapeTests::load_dual_textured_cube_into_world(const glm::vec3& world_position, const std::string& vertex_shader, const std::string& fragment_shader, const QuestEngine::ECS::RenderPass render_pass) {

		const std::string model_entity_id{ "Textured Indexed Shape Model Entity" };
		if (!textured_cube_in_resource) {
			const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = m_engine_api.get_shader_loader_api();
			const std::string shader_id{ vertex_shader + "_" + fragment_shader };
			shader_loader.load_shader(shader_id, vertex_shader, fragment_shader, true, true); // from file: true; load_ubo_matrices: true

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
			model_loader.load_model<GL_TRIANGLES>(model_entity_id, shader_id, { vertices }, { indices }, { 3, 3, 2 });

			// Get pointer to loaded model
			const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
			QuestEngine::Model::IndexedModel* model_pointer = resource_api.get_indexed_model_pointer(model_entity_id);

			// Texture Model

			// Load texture into resource
			const std::string texture_id_in_resource{ "wood_texture" };
			const std::string texture_name_in_shader{ "all_textures.diffuse" };

			const auto texture_api = m_engine_api.get_texture_loader_api();
			texture_api.load_texture2D(texture_id_in_resource, m_base_texture_path + "wood.png", QuestEngine::Texture::TextureType::Standard, false, true);
			const auto texture_ptr = resource_api.get_texture_pointer(texture_id_in_resource);

			auto& mesh_vector = model_pointer->get_mesh_vector();
			QuestGLCore::Shader::ShaderProgram* model_shader_program = model_pointer->get_shader_program();

			// For each mesh, register the texture
			for (auto& model_mesh : mesh_vector) {
				model_mesh.register_texture(texture_name_in_shader, model_shader_program, texture_ptr);
			}

			// Load specular texture
			const std::string specular_texture_id_in_resource{ "specular_texture" };
			const std::string specular_texture_name_in_shader{ "all_textures.specular" };

			texture_api.load_texture2D(specular_texture_id_in_resource, m_base_texture_path + "container_specular_map.png", QuestEngine::Texture::TextureType::Standard, false, false);
			const auto specular_texture_ptr = resource_api.get_texture_pointer(specular_texture_id_in_resource);
			// For each mesh, register the texture
			for (auto& model_mesh : mesh_vector) {
				model_mesh.register_texture(specular_texture_name_in_shader, model_shader_program, specular_texture_ptr);
			}

			textured_cube_in_resource = true;

		}

		// Load textured cube into registry:
		const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
		QuestEngine::Model::IndexedModel* model_pointer = resource_api.get_indexed_model_pointer(model_entity_id);

		// Take loaded model and create ECS entity
		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();
		registry_api.load_model_into_world(model_entity_id, model_pointer, world_position, render_pass);
	}


} // namespace QuestSandbox::Tests