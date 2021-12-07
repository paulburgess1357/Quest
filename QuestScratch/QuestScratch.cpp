#include "QuestUtility/Include/Logger.h"
#include "QuestEngine/Engine/Engine.h"
#include "QuestGLCore/Shader/ShaderProgram.h"
#include "QuestGLCore/Shader/ShaderProgramCreator.h"
#include "QuestGLCore/Shader/ShaderType.h"
#include "QuestEngine/Resource/TResource.h"


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

int main(){
    const QuestEngine::Engine::Engine game_engine;
    game_engine.run();



    ////// TODO Test shader creation
    std::unordered_map<QuestGLCore::Shader::ShaderType, std::string> shader_string_map;
    shader_string_map[QuestGLCore::Shader::ShaderType::VERTEX] = vertexShaderSource;



    QuestGLCore::Shader::ShaderProgramCreator shader_creator{ shader_string_map  };
    QuestGLCore::Shader::ShaderProgram shader_program{ "Test program", shader_creator};
    // auto testing = shader_creator.create();


    QuestEngine::Resource::TResource<std::string, QuestGLCore::Shader::ShaderProgram> shader_resource;
    shader_resource.load("shader_test_is_the_key", "waffle_shadder_is_my_name",  shader_creator);
    shader_resource.load("shader_test_is_the_key", "waffle_shadder_is_my_name", shader_creator);
    shader_resource.load("shader_test_is_the_key", "waffle_shadder_is_my_name", shader_creator);

    QuestEngine::Resource::TResource<std::string, QuestGLCore::Shader::ShaderProgram> shader_resource2 { std::move(shader_resource) };

}
