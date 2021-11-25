#include <iostream>
#include "QuestEngine/Engine/Engine.h"

int main(){

    //const Qw::Window window{ 1920, 1080, 3, 3};

    //while (!window.close_window() && !Qw::KeyboardInput::is_pressed(Qw::Keyboard::ESCAPE)){
    //    glfwPollEvents();
    //    window.clear_buffer();
    //    window.swap_buffer();
    //}

    QuestEngine::Engine::Engine game_engine;
    game_engine.run();


}