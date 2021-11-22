#include <iostream>
#include "QuestWindow/Include/Window.h"

int main(){

    const Qw::Window window{ 1920, 1080, 3, 3};

    while (!window.close_window() && !Qw::KeyboardInput::is_pressed(Qw::Keyboard::ESCAPE)){
        glfwPollEvents();
        window.clear_buffer();
        window.swap_buffer();
        auto test = Qw::Input::MouseManager::get_coords();

        std::cout << test.m_pos_x << std::endl;
    }

}