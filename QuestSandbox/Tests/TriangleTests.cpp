// ReSharper disable CppClangTidyClangDiagnosticExitTimeDestructors
#pragma once
#include "TriangleTests.h"
#include "QuestEngine/API/OpenGL/ShaderLoader.h"
#include "QuestEngine/API/OpenGL/ModelLoader.h"

namespace QuestSandbox::Tests {

    TriangleTests::TriangleTests(const QuestEngine::API::QuestEngineAPI& engine_api)
        :m_engine_api{ engine_api } {
    }

	void TriangleTests::load_standard_triangle() const {

        const QuestEngine::API::OpenGL::ShaderLoader shader_loader {m_engine_api};
        shader_loader.load_shader_program("Triangle Shader", m_vertex_str, m_fragment_str, false);

        // Standard model (Single Array Buffer)
        const std::vector<float> vertices = {
            -0.5f, -0.5f, 0.0f, // left  
             0.5f, -0.5f, 0.0f, // right 
             0.0f,  0.5f, 0.0f  // top   
        };

        const QuestEngine::API::OpenGL::ModelLoader model_loader { m_engine_api };
        model_loader.load_model("Test Model", "Triangle Shader", { vertices }, { 3 });

	}

    void TriangleTests::load_indexed_triangle() const {

        const QuestEngine::API::OpenGL::ShaderLoader shader_loader{ m_engine_api };
        shader_loader.load_shader_program("Triangle Shader", m_vertex_str, m_fragment_str, false);

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

    const std::string TriangleTests::m_vertex_str{
		R"(
        	#version 330 core
            layout(location = 0) in vec3 aPos;
        	void main(){
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }
    	)"
    };

    const std::string TriangleTests::m_fragment_str{
        R"(
			#version 330 core
			out vec4 FragColor;
			void main(){
			    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
			} 
    	)"
    };


} // namespace QuestSandbox::Tests