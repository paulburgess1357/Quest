// ReSharper disable CppClangTidyClangDiagnosticExitTimeDestructors
#pragma once
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
        model_loader.load_indexed_model("Test Model", "Triangle Shader", { vertices }, { indices }, { 3 });
    }


    // ======================== Cube ========================
    void ShapeTests::load_standard_cube() const {
        const QuestEngine::API::OpenGL::ShaderLoader shader_loader{ m_engine_api };
        shader_loader.load_shader_program("Cube Shader", m_base_shader_path + "CubeVertex.glsl", m_base_shader_path + "CubeFragment.glsl", true);

		// Cubemap needs to be in clockwise winding order.  If its not,
		// face culling will prevent the texture from being visible

		const std::vector<float> vertices = {
			// back face
			-1.0f, -1.0f, -1.0f, // bottom right
			 1.0f, -1.0f, -1.0f, // bottom left   
			-1.0f,  1.0f, -1.0f,  // top right
			-1.0f,  1.0f, -1.0f,  // top right
			 1.0f, -1.0f, -1.0f, // bottom left
			 1.0f,  1.0f, -1.0f,  // top left			 

			// left face
			-1.0f, -1.0f,  1.0f,  // bottom right
			-1.0f, -1.0f, -1.0f, // bottom left	   
			-1.0f,  1.0f,  1.0f,  // top right
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

		const QuestEngine::API::OpenGL::ModelLoader model_loader{ m_engine_api };
		model_loader.load_model("Test Model", "Cube Shader", { vertices }, { 3 });
    }

    void ShapeTests::load_indexed_cube() const {
	    
    }



} // namespace QuestSandbox::Tests