// ReSharper disable CppClangTidyClangDiagnosticExitTimeDestructors
#include "ShapeTests.h"
#include "QuestEngine/API/OpenGL/ShaderLoaderAPI.h"
#include "QuestEngine/API/OpenGL/ModelLoaderAPI.h"
#include "QuestEngine/API/Neutral/Constants.h"
#include "QuestEngine/API/OpenGL/PointLightLoaderAPI.h"
#include "QuestEngine/API/Neutral/Constants.h"

namespace QuestSandbox::Tests {
	
    const std::string ShapeTests::m_base_shader_path{"../Resources/Shaders/Shape/"};
	const std::string ShapeTests::m_base_gbuffer_shader_path{ "../Resources/Shaders/GBuffer/" };

    ShapeTests::ShapeTests(QuestEngine::API::EngineAPI& engine_api)
        :m_engine_api{ engine_api } {
    }

    // ====================== Triangle ======================
	void ShapeTests::load_standard_triangle() const {

		// *** TODO: this test isn't being loaded into the registry!! 
		const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = m_engine_api.get_shader_loader_api();
		const std::string shader_id{ "Triangle Shader" };
        shader_loader.load_shader(shader_id, m_base_shader_path + "TriangleVertex.glsl", m_base_shader_path + "TriangleFragment.glsl", true, true);

        // Standard model (Single Array Buffer)
        const std::vector<float> vertices = {
            -0.5f, -0.5f, 0.0f, // left  
             0.5f, -0.5f, 0.0f, // right 
             0.0f,  0.5f, 0.0f  // top   
        };

        const QuestEngine::API::OpenGL::ModelLoaderAPI model_loader = m_engine_api.get_model_loader_api();
        model_loader.load_model<GL_TRIANGLES>("Test Model", shader_id, { vertices }, { 3 });

	}
    void ShapeTests::load_indexed_triangle() const {

		// *** TODO: this test isn't being loaded into the registry!! 
		const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = m_engine_api.get_shader_loader_api();
		const std::string shader_id{ "Triangle Shader" };
        shader_loader.load_shader(shader_id, m_base_shader_path + "TriangleVertex.glsl", m_base_shader_path + "TriangleFragment.glsl", true, true);

        const std::vector<float> vertices = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
        };
        const std::vector<unsigned int> indices = {
            0, 2, 1,   // first triangle
            3, 2, 0    // second triangle
        };

		const QuestEngine::API::OpenGL::ModelLoaderAPI model_loader = m_engine_api.get_model_loader_api();
        model_loader.load_model<GL_TRIANGLES>("Test Model", shader_id, { vertices }, { indices }, { 3 });
    }

    // ======================== Shape ========================
    void ShapeTests::load_standard_shape() const {
		
		const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = m_engine_api.get_shader_loader_api();
		const std::string shader_id{ "Shape Shader" };
        shader_loader.load_shader(shader_id, m_base_shader_path + "ShapeVertexUBO.glsl", m_base_shader_path + "ShapeFragmentUBO.glsl", true, true);

		const std::vector<float> vertices = {
			// back face
			-1.0f, -1.0f, -1.0f, // bottom right
			 1.0f, -1.0f, -1.0f, // bottom left   
			-1.0f,  1.0f, -1.0f, // top right
			-1.0f,  1.0f, -1.0f, // top right
			 1.0f, -1.0f, -1.0f, // bottom left
			 1.0f,  1.0f, -1.0f, // top left			 

			// left face
			-1.0f, -1.0f,  1.0f, // bottom right
			-1.0f, -1.0f, -1.0f, // bottom left	   
			-1.0f,  1.0f,  1.0f, // top right
			-1.0f,  1.0f,  1.0f, // top right
			-1.0f, -1.0f, -1.0f, // bottom left	
			-1.0f,  1.0f, -1.0f, // top left			   

			 // right face 	 	
			 1.0f, -1.0f, -1.0f, // bottom right
			 1.0f, -1.0f,  1.0f, // bottom left
			 1.0f,  1.0f, -1.0f, // top right
			 1.0f,  1.0f, -1.0f, // top right
			 1.0f, -1.0f,  1.0f, // bottom left
			 1.0f,  1.0f,  1.0f, // top left	

			// front face   
			 1.0f, -1.0f,  1.0f, // bottom right
			-1.0f, -1.0f,  1.0f, // bottom left
			 1.0f,  1.0f,  1.0f, // top right
			 1.0f,  1.0f,  1.0f, // top right
			-1.0f, -1.0f,  1.0f, // bottom left
			-1.0f,  1.0f,  1.0f, // top left	    

			 // top face   
			 1.0f,  1.0f,  1.0f, // bottom right
			-1.0f,  1.0f,  1.0f, // bottom left
			 1.0f,  1.0f, -1.0f, // top right
			 1.0f,  1.0f, -1.0f, // top right
			-1.0f,  1.0f,  1.0f, // bottom left
			-1.0f,  1.0f, -1.0f, // top left   

			 // bottom face   
			 1.0f, -1.0f, -1.0f, // bottom right
			-1.0f, -1.0f, -1.0f, // bottom left
			 1.0f, -1.0f,  1.0f, // top right
			 1.0f, -1.0f,  1.0f, // top right
			-1.0f, -1.0f, -1.0f, // bottom left 		 
			-1.0f, -1.0f,  1.0f, // top left
		};

		// Load created model into resource
		const std::string model_entity_id{ "Test Model" };
		const QuestEngine::API::OpenGL::ModelLoaderAPI model_loader = m_engine_api.get_model_loader_api();
		model_loader.load_model<GL_TRIANGLES>(model_entity_id, shader_id, { vertices }, { 3 });

		// Take loaded model and create ECS entity
		const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
		QuestEngine::Model::StandardModel* model_pointer = resource_api.get_model_pointer(model_entity_id);

		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();
		registry_api.load_model_into_world(model_entity_id, model_pointer, { 0.0f, 3.0f, 0.0f }, true);
 
    }
    void ShapeTests::load_indexed_shape() const {
		
		const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = m_engine_api.get_shader_loader_api();
		const std::string shader_id{ "Indexed Shape Shader" };
		shader_loader.load_shader(shader_id, m_base_shader_path + "ShapeVertexUBO.glsl", m_base_shader_path + "ShapeFragmentUBO.glsl", true, true);

		const std::vector<float> vertices = {

			// back face
			 1.0f, -1.0f, -1.0f, // bottom left   
			-1.0f, -1.0f, -1.0f, // bottom right
			-1.0f,  1.0f, -1.0f, // top right
			 1.0f,  1.0f, -1.0f, // top left			 

			// front face   
			-1.0f, -1.0f,  1.0f, // bottom left
			 1.0f, -1.0f,  1.0f, // bottom right
			 1.0f,  1.0f,  1.0f, // top right
			-1.0f,  1.0f,  1.0f, // top left

			// left face
			-1.0f, -1.0f, -1.0f, // bottom left
			-1.0f, -1.0f,  1.0f, // bottom right
			-1.0f,  1.0f,  1.0f, // top right
			-1.0f,  1.0f, -1.0f, // top left			   

			 // right face 	 	
			 1.0f, -1.0f,  1.0f, // bottom left
			 1.0f, -1.0f, -1.0f, // bottom right
			 1.0f,  1.0f, -1.0f, // top right
			 1.0f,  1.0f,  1.0f, // top left	

			 // bottom face   
			-1.0f, -1.0f, -1.0f, // bottom left
			 1.0f, -1.0f, -1.0f, // bottom right
			 1.0f, -1.0f,  1.0f, // top right
			-1.0f, -1.0f,  1.0f, // top left

			 // top face   
			-1.0f,  1.0f,  1.0f, // bottom left
			 1.0f,  1.0f,  1.0f, // bottom right
			 1.0f,  1.0f, -1.0f, // top right
			-1.0f,  1.0f, -1.0f, // top left
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
		const std::string model_entity_id{ "Test Indexed Model" };
		const QuestEngine::API::OpenGL::ModelLoaderAPI model_loader = m_engine_api.get_model_loader_api();
		model_loader.load_model<GL_TRIANGLES>(model_entity_id, shader_id, { vertices }, { indices }, { 3 });

		// Take loaded model and create ECS entity
		const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
		QuestEngine::Model::IndexedModel* model_pointer = resource_api.get_indexed_model_pointer(model_entity_id);

		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();
		registry_api.load_model_into_world(model_entity_id, model_pointer, { 0.0f, 1.0f, 0.0f }, true);
    }

	void ShapeTests::load_textured_indexed_shape() const {
		const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = m_engine_api.get_shader_loader_api();
		const std::string shader_id{ "Textured Indexed Shape Shader" };
		shader_loader.load_shader(shader_id, m_base_shader_path + "ShapeVertexUBOTextured.glsl", m_base_shader_path + "ShapeFragmentUBOTextured.glsl", true, true);

		const std::vector<float> vertices = {

			// Vertices                 // Texture Coordinates
			// back face
			 0.5f, -0.5f, -0.5f,		0.0f, 0.0f, // bottom left	
			-0.5f, -0.5f, -0.5f,		1.0f, 0.0f, // bottom right
			-0.5f,  0.5f, -0.5f,		1.0f, 1.0f, // top right	 
			 0.5f,  0.5f, -0.5f,		0.0f, 1.0f, // top left			

			 // front face
			-0.5f, -0.5f,  0.5f,		0.0f, 0.0f, // bottom left
			 0.5f, -0.5f,  0.5f,		1.0f, 0.0f, // bottom right
			 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, // top right
			-0.5f,  0.5f,  0.5f,		0.0f, 1.0f, // top left

			 // left face
			-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, // bottom left
			-0.5f, -0.5f,  0.5f,		1.0f, 0.0f, // bottom right
			-0.5f,  0.5f,  0.5f,		1.0f, 1.0f, // top right
			-0.5f,  0.5f, -0.5f,		0.0f, 1.0f, // top left		

			 // right face		 		 		 	     
			 0.5f, -0.5f,  0.5f,		0.0f, 0.0f, // bottom left
			 0.5f, -0.5f, -0.5f,		1.0f, 0.0f, // bottom right
			 0.5f,  0.5f, -0.5f,		1.0f, 1.0f, // top right
			 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, // top left

			 // bottom face
			-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, // bottom left
			 0.5f, -0.5f, -0.5f,		1.0f, 0.0f, // bottom right
			 0.5f, -0.5f,  0.5f,		1.0f, 1.0f, // top right
			-0.5f, -0.5f,  0.5f,		0.0f, 1.0f, // top left

			// top face
			-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, // bottom left
			 0.5f,  0.5f,  0.5f,		1.0f, 0.0f, // bottom right
			 0.5f,  0.5f, -0.5f,		1.0f, 1.0f, // top right
			-0.5f,  0.5f, -0.5f,		0.0f, 1.0f, // top left
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
		const std::string model_entity_id{ "Test Indexed Model" };
		const QuestEngine::API::OpenGL::ModelLoaderAPI model_loader = m_engine_api.get_model_loader_api();
		model_loader.load_model<GL_TRIANGLES>(model_entity_id, shader_id, { vertices }, { indices }, { 3, 2 });

		// Get pointer to loaded model
		const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
		QuestEngine::Model::IndexedModel* model_pointer = resource_api.get_indexed_model_pointer(model_entity_id);

		// Texture Model (
		// In this example, we only have one mesh.  However, the following would simply texture each
		// mesh within the model to having the same texture (or collection of textures). Normally each
		// mesh will be loaded and the textures loaded with it (via assimp).  In this example, we are
		// taking the already created model and setting each mesh within it to use the same textures
		// in order to test the textures are working

		// Load texture into resource
		const std::string base_texture_path{ "../Resources/Textures/" };
		const std::string texture_id_in_resource{ "blue_texture" };
		const std::string texture_name_in_shader{ "shape_texture_test" };

		const auto texture_api = m_engine_api.get_texture_loader_api();
		texture_api.load_texture2D(texture_id_in_resource, base_texture_path + "abstract_texture.jpg", QuestEngine::Texture::TextureType::Standard, false, true);
		const auto texture_ptr = resource_api.get_texture_pointer(texture_id_in_resource);

		auto& mesh_vector = model_pointer->get_mesh_vector();
		QuestGLCore::Shader::ShaderProgram* model_shader_program = model_pointer->get_shader_program();

		// For each mesh, register the texture
		for(auto& model_mesh : mesh_vector) {
			model_mesh.register_texture(texture_name_in_shader, model_shader_program, texture_ptr);
		}

		// Take loaded model and create ECS entity
		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();
		registry_api.load_model_into_world(model_entity_id, model_pointer, { 0.0f, 1.0f, 0.0f }, true);
	}
	void ShapeTests::load_normals_texture_indexed_shape_blinn_phong() const {

		const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = m_engine_api.get_shader_loader_api();
		const std::string shader_id{ "Textured Indexed Shape Shader" };
		shader_loader.load_shader(shader_id, m_base_shader_path + "ShapeVertexUBOTexturedNormalsBlinnPhong.glsl", m_base_shader_path + "ShapeFragmentUBOTexturedNormalsBlinnPhong.glsl", true, true);

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
		const std::string model_entity_id{ "Test Indexed Model" };
		const QuestEngine::API::OpenGL::ModelLoaderAPI model_loader = m_engine_api.get_model_loader_api();
		model_loader.load_model<GL_TRIANGLES>(model_entity_id, shader_id, { vertices }, { indices }, { 3, 3, 2 });

		// Get pointer to loaded model
		const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
		QuestEngine::Model::IndexedModel* model_pointer = resource_api.get_indexed_model_pointer(model_entity_id);

		// Texture Model (
		// In this example, we only have one mesh.  However, the following would simply texture each
		// mesh within the model to having the same texture (or collection of textures). Normally each
		// mesh will be loaded and the textures loaded with it (via assimp).  In this example, we are
		// taking the already created model and setting each mesh within it to use the same textures
		// in order to test the textures are working

		// Load texture into resource
		const std::string base_texture_path{ "../Resources/Textures/" };
		const std::string texture_id_in_resource{ "blue_texture" };
		const std::string texture_name_in_shader{ "all_textures.diffuse" };

		const auto texture_api = m_engine_api.get_texture_loader_api();
		texture_api.load_texture2D(texture_id_in_resource, base_texture_path + "wood.png", QuestEngine::Texture::TextureType::Standard, false, true);
		const auto texture_ptr = resource_api.get_texture_pointer(texture_id_in_resource);

		auto& mesh_vector = model_pointer->get_mesh_vector();
		QuestGLCore::Shader::ShaderProgram* model_shader_program = model_pointer->get_shader_program();

		// For each mesh, register the texture
		for (auto& model_mesh : mesh_vector) {
			model_mesh.register_texture(texture_name_in_shader, model_shader_program, texture_ptr);
		}

		// Load specular texture
		texture_api.load_texture2D("specular_texture", base_texture_path + "container_specular_map.png", QuestEngine::Texture::TextureType::Standard, false, false);
		const auto specular_texture_ptr = resource_api.get_texture_pointer("specular_texture");
		// For each mesh, register the texture
		for (auto& model_mesh : mesh_vector) {
			model_mesh.register_texture("all_textures.specular", model_shader_program, specular_texture_ptr);
		}

		// Take loaded model and create ECS entity
		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();
		registry_api.load_model_into_world(model_entity_id, model_pointer, { 0.0f, 0.0f, 0.0f }, true);

		// Set shader uniforms for lighting test
		// Light is directional or positional (0.0f in 4th position indicates directional light)
		model_shader_program->bind();
		model_shader_program->set_uniform("light_info.light_in_world", glm::vec4(0.0f, 0.0f, -3.0f, 0.0f));
		model_shader_program->set_uniform("light_info.ambient_intensity", glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		model_shader_program->set_uniform("light_info.diffuse_intensity", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		model_shader_program->set_uniform("light_info.specular_intensity", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		model_shader_program->set_uniform("light_info.shininess", 32.0f);
		model_shader_program->unbind();

	}

	void ShapeTests::g_buffer_lighting_test() const {
		const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = m_engine_api.get_shader_loader_api();
		std::string shader_id{ "Textured Indexed Shape Using G-Buffer" };
		shader_loader.load_shader(shader_id, m_base_gbuffer_shader_path + "GBufferShapeVertexGeometryPass.glsl", m_base_gbuffer_shader_path + "GBufferShapeFragmentGeometryPass.glsl", true, true);

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
		std::string model_entity_id{ "Test Indexed Model" };
		const QuestEngine::API::OpenGL::ModelLoaderAPI model_loader = m_engine_api.get_model_loader_api();
		model_loader.load_model<GL_TRIANGLES>(model_entity_id, shader_id, { vertices }, { indices }, { 3, 3, 2 });

		// Get pointer to loaded model
		const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
		QuestEngine::Model::IndexedModel* model_pointer = resource_api.get_indexed_model_pointer(model_entity_id);

		// Load texture into resource
		const std::string base_texture_path{ "../Resources/Textures/" };
		std::string texture_id_in_resource{ "wood_texture" };
		const std::string texture_name_in_shader{ "all_textures.diffuse" };

		const auto texture_api = m_engine_api.get_texture_loader_api();
		texture_api.load_texture2D(texture_id_in_resource, base_texture_path + "wood.png", QuestEngine::Texture::TextureType::Standard, false, true);
		auto texture_ptr = resource_api.get_texture_pointer(texture_id_in_resource);

		auto& mesh_vector = model_pointer->get_mesh_vector();
		QuestGLCore::Shader::ShaderProgram* model_shader_program = model_pointer->get_shader_program();

		// For each mesh, register the texture
		for (auto& model_mesh : mesh_vector) {
			model_mesh.register_texture(texture_name_in_shader, model_shader_program, texture_ptr);
		}

		// Load specular texture
		const std::string specular_texture_id_in_resource{"specular_texture"};
		const std::string specular_texture_id_in_shader{ "all_textures.specular" };

		texture_api.load_texture2D(specular_texture_id_in_resource, base_texture_path + "container_specular_map.png", QuestEngine::Texture::TextureType::Standard, false, false);
		auto specular_texture_ptr = resource_api.get_texture_pointer(specular_texture_id_in_resource);
		// For each mesh, register the texture
		for (auto& model_mesh : mesh_vector) {
			model_mesh.register_texture(specular_texture_id_in_shader, model_shader_program, specular_texture_ptr);
		}

		// Take loaded model and create ECS entity
		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();

		// Load ECS Entity into world::
		constexpr int BOX_QTY = 12;
		for (unsigned int i = 0; i < BOX_QTY; i++) {
			// calculate slightly random offsets
			const float xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			const float yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
			const float zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			registry_api.load_model_into_world(model_entity_id, model_pointer, { xPos , yPos, zPos }, true); // deferred rendering
		}


		// ====================================== G-Buffer Post Process ======================================
		// Load G-Buffer Light Pass Shader
		const std::string light_pass_shader_id{ QuestEngine::Constants::g_buffer_light_pass };
		shader_loader.load_shader(light_pass_shader_id, m_base_gbuffer_shader_path + "GBufferVertexLightPass.glsl", m_base_gbuffer_shader_path + "GBufferFragmentLightPass.glsl", true, true);

		QuestGLCore::Shader::ShaderProgram& g_buffer_light_pass_shader_program  = resource_api.get_shader(light_pass_shader_id);

		g_buffer_light_pass_shader_program.bind();

		// Lights (hardcoded in shader)
		constexpr int LIGHT_QTY = 64;
		for (unsigned int i = 0; i < LIGHT_QTY; i++){
			// calculate slightly random offsets
			const float xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			const float yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
			const float zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			g_buffer_light_pass_shader_program.set_uniform("all_lights[" + std::to_string(i) + "].light_position", glm::vec3(xPos, yPos + 2.0f, zPos));

			// also calculate random color
			const float rColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			const float gColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			const float bColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			g_buffer_light_pass_shader_program.set_uniform("all_lights[" + std::to_string(i) + "].color", glm::vec3(1.0, 1.0, 1.0)); // Setting all to white for now

			// Setting box model right below lights (limiting to just 32 models for testing light quantity):
			if(i <= 12) {
				registry_api.load_model_into_world(model_entity_id, model_pointer, { xPos , yPos, zPos }, true);
			}

		}

		// Set light pass pointlight uniforms
		constexpr float CONSTANT = 1.0f;
		constexpr float pointlight_linear = 0.7f;
		constexpr float pointlight_quadratic = 1.8f;
		g_buffer_light_pass_shader_program.set_uniform("linear", pointlight_linear);
		g_buffer_light_pass_shader_program.set_uniform("quadratic", pointlight_quadratic);

		// *** Calculate light volume (max distance to display light). ***
		// In the shader, we will discard any fragments outside this range for
		// light calculations

    	// Note: This 'max_brightness' calculation clearly isn't necessary.  However, if you had a light color that was different than white, we would need the max r/g/b value for max_brightness.
		const float max_brightness = std::fmaxf(std::fmaxf(1.0f, 1.0f), 1.0f);

		float radius = (-pointlight_linear + std::sqrt(pointlight_linear * pointlight_linear - 4 * pointlight_quadratic * (CONSTANT - (256.0f / 5.0f) * max_brightness))) / (2.0f * pointlight_quadratic);
		g_buffer_light_pass_shader_program.set_uniform("pointlight_max_radius", radius);

		g_buffer_light_pass_shader_program.unbind();


		// Testing forward pass
		// ===================================== Forward Pass Test ===========================================
		// If forward pass works, the rainbow cube should be behind the wooden cube
		// Note: No model matrix is being used for the rainbow cube.  For this example no lighting was being done in the forward pass, hence, its
		//       not needed (and the glsl code optimizes it away)

		// Load forward rendering shader (standard shader)
		shader_id =  "Textured Indexed Shape Forward Render";
		shader_loader.load_shader(shader_id, m_base_gbuffer_shader_path + "GBufferForwardPassVertex.glsl", m_base_gbuffer_shader_path + "GBufferForwardPassFragment.glsl", true, true);

		// Load created model into resource
		model_entity_id =  "Rainbow Indexed Model";
		model_loader.load_model<GL_TRIANGLES>(model_entity_id, shader_id, { vertices }, { indices }, { 3, 3, 2 });

		// Get pointer to loaded model
		model_pointer = resource_api.get_indexed_model_pointer(model_entity_id);

		// Load texture into resource
		texture_id_in_resource = "rainbow_texture";
		texture_api.load_texture2D(texture_id_in_resource, base_texture_path + "rainbow.jpg", QuestEngine::Texture::TextureType::Standard, false, true);
		texture_ptr = resource_api.get_texture_pointer(texture_id_in_resource);

		auto& mesh_vector2 = model_pointer->get_mesh_vector();
		model_shader_program = model_pointer->get_shader_program();

		// For each mesh, register the texture
		for (auto& model_mesh : mesh_vector2) {
			model_mesh.register_texture("rainbow_texture", model_shader_program, texture_ptr);
		}

		// Take loaded model and create ECS entity
		registry_api.load_model_into_world(model_entity_id, model_pointer, { 0.0f, 0.5f, 3.0f }, false); // true = deferred pass, false = forward pass

	}
	void ShapeTests::g_buffer_lighting_test_pointlight_mesh_volume() const {


		// Load test textured cube
		const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = m_engine_api.get_shader_loader_api();
		std::string shader_id{ "Textured Indexed Shape Using G-Buffer" };
		shader_loader.load_shader(shader_id, m_base_gbuffer_shader_path + "GBufferShapeVertexGeometryPass.glsl", m_base_gbuffer_shader_path + "GBufferShapeFragmentGeometryPass.glsl", true, true);

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
		std::string model_entity_id{ "Test Indexed Model" };
		const QuestEngine::API::OpenGL::ModelLoaderAPI model_loader = m_engine_api.get_model_loader_api();
		model_loader.load_model<GL_TRIANGLES>(model_entity_id, shader_id, { vertices }, { indices }, { 3, 3, 2 });

		// Get pointer to loaded model
		const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
		QuestEngine::Model::IndexedModel* model_pointer = resource_api.get_indexed_model_pointer(model_entity_id);

		// Load texture into resource
		const std::string base_texture_path{ "../Resources/Textures/" };
		std::string texture_id_in_resource{ "wood_texture" };
		const std::string texture_name_in_shader{ "all_textures.diffuse" };

		const auto texture_api = m_engine_api.get_texture_loader_api();
		texture_api.load_texture2D(texture_id_in_resource, base_texture_path + "wood.png", QuestEngine::Texture::TextureType::Standard, false, true);
		auto texture_ptr = resource_api.get_texture_pointer(texture_id_in_resource);

		auto& mesh_vector = model_pointer->get_mesh_vector();
		QuestGLCore::Shader::ShaderProgram* model_shader_program = model_pointer->get_shader_program();

		// For each mesh, register the texture
		for (auto& model_mesh : mesh_vector) {
			model_mesh.register_texture(texture_name_in_shader, model_shader_program, texture_ptr);
		}

		// Load specular texture
		const std::string specular_texture_id_in_resource{ "specular_texture" };
		const std::string specular_texture_id_in_shader{ "all_textures.specular" };

		texture_api.load_texture2D(specular_texture_id_in_resource, base_texture_path + "container_specular_map.png", QuestEngine::Texture::TextureType::Standard, false, false);
		auto specular_texture_ptr = resource_api.get_texture_pointer(specular_texture_id_in_resource);
		// For each mesh, register the texture
		for (auto& model_mesh : mesh_vector) {
			model_mesh.register_texture(specular_texture_id_in_shader, model_shader_program, specular_texture_ptr);
		}

		// Take loaded model and create ECS entity
		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();

		// Load ECS Entity into world::
		constexpr int BOX_QTY = 12;
		for (unsigned int i = 0; i < BOX_QTY; i++) {
			// calculate slightly random offsets
			const float xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			const float yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
			const float zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			registry_api.load_model_into_world(model_entity_id, model_pointer, { xPos , yPos, zPos }, true); // deferred rendering
		}

		// ==================================================================================================================================




















		// Load pointlight mesh
		QuestEngine::API::OpenGL::PointLightLoader pointlight_loader(10);
		pointlight_loader.load_pointlight_mesh(m_engine_api);

		// Load pointlight into registry
		//const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();
		//const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
		model_pointer = resource_api.get_indexed_model_pointer(QuestEngine::Constants::pointlight_model);






		// ====================================== G-Buffer Post Process ======================================
		// TODO: update lighting shader to not calculate pointlight based on shader uniforms (make a new text and shader program name): e.g. GBufferVertexLight_VOLUME_Pass, GBufferFRAGMENTLight_VOLUME_Pass
		// TODO: This new shader won't calcuation pointlight in the shader or based on unifrom values.  Rather, pointlight will be based on the created Pointlight mesh.  SOMEHOW distance is taken into acount for hte light to get less strong as you move away....
		// TODO for light distance, you would normally scale it by the light volume radius (that we calculated: see 'pointlight_max_radius' below)
		// TODO: somehow blend fragment values

		// *** Sphere radius must equal the size of the light volume radius!!!! probably need scale transformation system.... ***
		// *** Spheres are rendered in the DEFFERRED LIGHTING STAGE VIA BLENDING>>> ****

		// Load G-Buffer Light Pass Shader
		const std::string light_pass_shader_id{ QuestEngine::Constants::g_buffer_light_pass };
		//const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = m_engine_api.get_shader_loader_api();
		shader_loader.load_shader(light_pass_shader_id, m_base_gbuffer_shader_path + "GBufferVertexLightPass.glsl", m_base_gbuffer_shader_path + "GBufferFragmentLightPass.glsl", true, true);

		QuestGLCore::Shader::ShaderProgram& g_buffer_light_pass_shader_program = resource_api.get_shader(light_pass_shader_id);

		g_buffer_light_pass_shader_program.bind();

		// Lights (hardcoded in shader)
		constexpr int LIGHT_QTY = 12;
		for (unsigned int i = 0; i < LIGHT_QTY; i++) {
			// calculate slightly random offsets
			const float xPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			const float yPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 4.0);
			const float zPos = static_cast<float>(((rand() % 100) / 100.0) * 6.0 - 3.0);
			g_buffer_light_pass_shader_program.set_uniform("all_lights[" + std::to_string(i) + "].light_position", glm::vec3(xPos, yPos + 2.0f, zPos));

			// also calculate random color
			const float rColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			const float gColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			const float bColor = static_cast<float>(((rand() % 100) / 200.0f) + 0.5); // between 0.5 and 1.)
			g_buffer_light_pass_shader_program.set_uniform("all_lights[" + std::to_string(i) + "].color", glm::vec3(1.0, 1.0, 1.0)); // Setting all to white for now

			// Load mesh pointlight to wherever a light source originates
			registry_api.load_model_into_world("pointlight_" + std::to_string(i), model_pointer, { xPos , yPos, zPos }, true); // deferred rendering

		}

		// Set light pass pointlight uniforms
		constexpr float CONSTANT = 1.0f;
		constexpr float pointlight_linear = 0.7f;
		constexpr float pointlight_quadratic = 1.8f;
		g_buffer_light_pass_shader_program.set_uniform("linear", pointlight_linear);
		g_buffer_light_pass_shader_program.set_uniform("quadratic", pointlight_quadratic);

		// *** Calculate light volume (max distance to display light). ***
		// In the shader, we will discard any fragments outside this range for
		// light calculations

		// Note: This 'max_brightness' calculation clearly isn't necessary.  However, if you had a light color that was different than white, we would need the max r/g/b value for max_brightness.
		const float max_brightness = std::fmaxf(std::fmaxf(1.0f, 1.0f), 1.0f);

		float radius = (-pointlight_linear + std::sqrt(pointlight_linear * pointlight_linear - 4 * pointlight_quadratic * (CONSTANT - (256.0f / 5.0f) * max_brightness))) / (2.0f * pointlight_quadratic);
		g_buffer_light_pass_shader_program.set_uniform("pointlight_max_radius", radius);

		g_buffer_light_pass_shader_program.unbind();

	}





} // namespace QuestSandbox::Tests