// ReSharper disable CppClangTidyClangDiagnosticExitTimeDestructors
#include "ShapeTests.h"
#include "QuestEngine/API/OpenGL/ShaderLoader.h"
#include "QuestEngine/API/OpenGL/ModelLoader.h"

namespace QuestSandbox::Tests {

    const std::string ShapeTests::m_base_shader_path{"../Resources/Shaders/Shape/"};

    ShapeTests::ShapeTests(const QuestEngine::API::QuestEngineAPI& engine_api)
        :m_engine_api{ engine_api } {
    }

    // ====================== Triangle ======================
	void ShapeTests::load_standard_triangle() const {

		// *** TODO: this test isn't being loaded into the registry!! 

        const QuestEngine::API::OpenGL::ShaderLoader shader_loader { m_engine_api };
        shader_loader.load_shader_program("Triangle Shader", m_base_shader_path + "TriangleVertex.glsl", m_base_shader_path + "TriangleFragment.glsl", true);

        // Standard model (Single Array Buffer)
        const std::vector<float> vertices = {
            -0.5f, -0.5f, 0.0f, // left  
             0.5f, -0.5f, 0.0f, // right 
             0.0f,  0.5f, 0.0f  // top   
        };

        const QuestEngine::API::OpenGL::ModelLoader model_loader { m_engine_api };
        model_loader.load_model("Test Model", "Triangle Shader", { vertices }, { 3 });

	}
    void ShapeTests::load_indexed_triangle() const {

		// *** TODO: this test isn't being loaded into the registry!! 

        const QuestEngine::API::OpenGL::ShaderLoader shader_loader{ m_engine_api };
        shader_loader.load_shader_program("Triangle Shader", m_base_shader_path + "TriangleVertex.glsl", m_base_shader_path + "TriangleFragment.glsl", true);

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

        const QuestEngine::API::OpenGL::ModelLoader model_loader{ m_engine_api };
        model_loader.load_model("Test Model", "Triangle Shader", { vertices }, { indices }, { 3 });
    }

    // ======================== Cube ========================
    void ShapeTests::load_standard_cube() const {
        const QuestEngine::API::OpenGL::ShaderLoader shader_loader{ m_engine_api };
        shader_loader.load_shader_program("Cube Shader", m_base_shader_path + "CubeVertex.glsl", m_base_shader_path + "CubeFragment.glsl", true);

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
		const QuestEngine::API::OpenGL::ModelLoader model_loader{ m_engine_api };
		model_loader.load_model(model_entity_id, "Cube Shader", { vertices }, { 3 });

		// Take loaded model and create ECS entity
		QuestEngine::Model::StandardModel* model_pointer = m_engine_api.get_model_pointer(model_entity_id);
		m_engine_api.load_model_into_registry(model_entity_id, model_pointer, { 0.0f, 3.0f, 0.0f });
 
    }
    void ShapeTests::load_indexed_cube() const {

		const QuestEngine::API::OpenGL::ShaderLoader shader_loader{ m_engine_api };
		shader_loader.load_shader_program("Indexed Cube Shader", m_base_shader_path + "CubeVertex.glsl", m_base_shader_path + "CubeFragment.glsl", true);

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
		const QuestEngine::API::OpenGL::ModelLoader model_loader{ m_engine_api };
		model_loader.load_model(model_entity_id, "Indexed Cube Shader", { vertices }, { indices }, { 3 });

		// Take loaded model and create ECS entity
		QuestEngine::Model::IndexedModel* model_pointer = m_engine_api.get_indexed_model_pointer(model_entity_id);
		m_engine_api.load_model_into_registry(model_entity_id, model_pointer, { 0.0f, 1.0f, 0.0f });
    }

} // namespace QuestSandbox::Tests