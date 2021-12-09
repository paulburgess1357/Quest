//#include "QuestUtility/Include/Logger.h"
//#include "QuestEngine/Engine/Engine.h"
//#include "QuestGLCore/Shader/ShaderProgram.h"
//#include "QuestGLCore/Shader/ShaderProgramCreator.h"
//#include "QuestGLCore/Shader/ShaderEnum.h"
//#include "QuestEngine/Resource/TResource.h"
#include "QuestEngine/API/EngineAPI.h"


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

int main(){

    const QuestEngine::API::QuestEngineAPI engine_api;

    std::string vertex_string { vertexShaderSource };

    std::pair test1{ QuestGLCore::Shader::ShaderEnum::VERTEX, vertex_string };
    std::pair test2{ QuestGLCore::Shader::ShaderEnum::VERTEX, vertex_string };
    std::pair test3{ QuestGLCore::Shader::ShaderEnum::VERTEX, vertex_string };


    engine_api.load_shader("shader_test", { test1 });


    engine_api.run();


    //const QuestEngine::Engine::Engine game_engine;
    //game_engine.run();

    //std::unordered_map<QuestGLCore::Shader::ShaderEnum, std::string> shader_string_map;
    //shader_string_map[QuestGLCore::Shader::ShaderEnum::VERTEX] = vertexShaderSource;

    //QuestGLCore::Shader::ShaderProgramCreator shader_creator{ shader_string_map  };
    //QuestGLCore::Shader::ShaderProgram shader_program{ "Test program", shader_creator};

    //QuestEngine::Resource::TResource<std::string, QuestGLCore::Shader::ShaderProgram> shader_resource;
    //shader_resource.load("shader_test_is_the_key", "waffle_shader_is_my_name",  shader_creator);
    //shader_resource.load("shader_test_is_the_key", "waffle_shader_is_my_name", shader_creator);
    //shader_resource.load("shader_test_is_the_key", "waffle_shader_is_my_name", shader_creator);

    //QuestEngine::Resource::TResource<std::string, QuestGLCore::Shader::ShaderProgram> shader_resource2 { std::move(shader_resource) };

}
