// ReSharper disable once CppUnusedIncludeDirective
#include <Windows.h>
#include "QuestEngine/API/EngineAPI.h"
#include "QuestGLCore/VertexData/VertexDataLoader.h"
#include "QuestUtility/String/FileToString.h"

int main(){

    const QuestEngine::API::QuestEngineAPI engine_api;

    std::string vertex_string =   QuestUtility::String::FileToString::load("../Resources/Shaders/Triangle/TriangleVertex.glsl");
    std::string fragment_string = QuestUtility::String::FileToString::load("../Resources/Shaders/Triangle/TriangleFragment.glsl");

    engine_api.load_shader("TriangleShader", {
    	std::pair{QuestGLCore::Shader::ShaderEnum::VERTEX, vertex_string },
    	std::pair{QuestGLCore::Shader::ShaderEnum::FRAGMENT, fragment_string }
    });

    // Testing loading of data to gpu:
    std::vector<float> vertices = {
        // first triangle
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f,  0.5f, 0.0f,  // top left 
        // second triangle
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };

    auto vertex_data_handles = QuestGLCore::VertexData::VertexDataLoader::load_data(vertices, { 3 });
    auto& shader_program = engine_api.get_shader("TriangleShader");

}
