// ReSharper disable CppClangTidyClangDiagnosticExitTimeDestructors
#pragma once
#include "TriangleTests.h"

namespace QuestSandbox::Tests {

    TriangleTests::TriangleTests(const QuestEngine::API::QuestEngineAPI* engine_api)
        :m_engine_api{ engine_api } {
    }

	void TriangleTests::load_standard_triangle() const {

    	m_engine_api->load_shader("TriangleShader", {
	        std::pair{QuestGLCore::Shader::ShaderEnum::VERTEX, m_vertex_str },
	        std::pair{QuestGLCore::Shader::ShaderEnum::FRAGMENT, m_fragment_str }
        });

        // Standard model (Single Array Buffer)
        const std::vector<float> vertices = {
            -0.5f, -0.5f, 0.0f, // left  
             0.5f, -0.5f, 0.0f, // right 
             0.0f,  0.5f, 0.0f  // top   
        };

        // Load Vertex Data
        QuestGLCore::VertexData::VertexData vertex_data{ GL_ARRAY_BUFFER };
        vertex_data.load_data<float>(vertices, { 3 });

        // Move vertex data into mesh
        QuestGLCore::Model::Mesh standard_mesh{ std::move(vertex_data) };

        // Move mesh into vector
        std::vector<QuestGLCore::Model::Mesh<QuestGLCore::VertexData::VertexData>> meshes;
        meshes.push_back(std::move(standard_mesh));

        // Move vector of mesh's into model
        const auto& shader_program = m_engine_api->get_shader("TriangleShader");
        m_engine_api->load_model("Test Model", shader_program, meshes);

	}

    void TriangleTests::load_indexed_triangle() const {

        m_engine_api->load_shader("TriangleShader", {
		    std::pair{QuestGLCore::Shader::ShaderEnum::VERTEX, m_vertex_str },
		    std::pair{QuestGLCore::Shader::ShaderEnum::FRAGMENT, m_fragment_str }
        });

        const std::vector<float> vertices = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
        };
        const std::vector<unsigned int> indices = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        QuestGLCore::VertexData::IndexedVertexData vertex_data_element{ GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER };
        vertex_data_element.load_data(vertices, indices, { 3 });

        // Move vertex data into mesh
        QuestGLCore::Model::Mesh indexed_mesh{ std::move(vertex_data_element) };

        // Move mesh into vector
        std::vector<QuestGLCore::Model::Mesh<QuestGLCore::VertexData::IndexedVertexData>> indexed_meshes;
        indexed_meshes.push_back(std::move(indexed_mesh));

        // Move vector of mesh's into model
        const auto& shader_program = m_engine_api->get_shader("TriangleShader");
        m_engine_api->load_indexed_model("Test Model", shader_program, indexed_meshes);

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