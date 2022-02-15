// ReSharper disable CppClangTidyClangDiagnosticExitTimeDestructors
#include "ShapeTests.h"
#include "QuestEngine/API/OpenGL/ShaderLoaderAPI.h"
#include "QuestEngine/API/OpenGL/ModelLoaderAPI.h"

namespace QuestSandbox::Tests {

    const std::string ShapeTests::m_base_shader_path{"../Resources/Shaders/Shape/"};

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
        model_loader.load_model("Test Model", shader_id, { vertices }, { 3 });

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
        model_loader.load_model("Test Model", shader_id, { vertices }, { indices }, { 3 });
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
		model_loader.load_model(model_entity_id, shader_id, { vertices }, { 3 });

		// Take loaded model and create ECS entity
		const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
		QuestEngine::Model::StandardModel* model_pointer = resource_api.get_model_pointer(model_entity_id);

		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();
		registry_api.load_model_into_world(model_entity_id, model_pointer, { 0.0f, 3.0f, 0.0f });
 
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
		model_loader.load_model(model_entity_id, shader_id, { vertices }, { indices }, { 3 });

		// Take loaded model and create ECS entity
		const QuestEngine::API::ResourceAPI& resource_api = m_engine_api.get_resource_api();
		QuestEngine::Model::IndexedModel* model_pointer = resource_api.get_indexed_model_pointer(model_entity_id);

		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();
		registry_api.load_model_into_world(model_entity_id, model_pointer, { 0.0f, 1.0f, 0.0f });
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
		model_loader.load_model(model_entity_id, shader_id, { vertices }, { indices }, { 3, 2 });

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
		//texture_api.load_texture2D(texture_id_in_resource, base_texture_path + "abstract_texture.jpg", QuestEngine::Texture::TextureType::Standard, false, true);
		//texture_api.load_texture2D(texture_id_in_resource, base_texture_path + "abstract_texture.jpg", QuestEngine::Texture::TextureType::Standard, false, true);
		//texture_api.load_texture2D(texture_id_in_resource, base_texture_path + "abstract_texture.jpg", QuestEngine::Texture::TextureType::Standard, false, true);
		const auto texture_ptr = resource_api.get_texture_pointer(texture_id_in_resource);

		auto& mesh_vector = model_pointer->get_mesh_vector();
		QuestGLCore::Shader::ShaderProgram* model_shader_program = model_pointer->get_shader_program();

		// For each mesh, register the texture
		for(auto& model_mesh : mesh_vector) {
			model_mesh.register_texture(texture_name_in_shader, model_shader_program, texture_ptr);
		}

		// Texture test 2 which will be deleted
		 //const std::string texture2_name{ "yellow_texture" };
		 //texture_api.load_texture2D(texture2_name, base_texture_path + "yellow_texture.jpg", QuestEngine::Texture::TextureType::Standard, false, true);
		 //auto texture_ptr2 = resource_api.get_texture_pointer(texture2_name);

		 //for (auto& model_mesh : mesh_vector) {
		 //	 model_mesh.register_texture("shape_texture_test2", model_shader_program, texture_ptr2);
		 //}
		// ====================================


		// Take loaded model and create ECS entity
		const QuestEngine::API::RegistryAPI registry_api = m_engine_api.get_registry_api();
		registry_api.load_model_into_world(model_entity_id, model_pointer, { 0.0f, 1.0f, 0.0f });
	}


} // namespace QuestSandbox::Tests