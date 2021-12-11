// ReSharper disable once CppUnusedIncludeDirective
#include <Windows.h>
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

}
