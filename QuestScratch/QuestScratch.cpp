#include "QuestEngine/Engine/Engine.h"
#include "QuestEngine/Engine/Engine.h"
#include "QuestGLCore/Shader/ShaderProgram.h"
#include "QuestGLCore/Shader/ShaderProgramCreator.h"

//TODO Add logger to QuestGLCore

int main(){
    const QuestEngine::Engine::Engine game_engine;
    game_engine.run();
    QuestGLCore::Shader::ShaderProgram shader_program;

    // TODO Test shader creation
    std::unordered_map<QuestGLCore::Shader::ShaderType, std::string> shader_string_map;

    shader_string_map[QuestGLCore::Shader::ShaderType::VERTEX] = "test";

    QuestGLCore::Shader::ShaderProgramCreator shader_creator{ shader_string_map  };
    auto testing = shader_creator.create();
}