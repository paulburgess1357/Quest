#include "QuestWindow/Include/Window.h"

int main(){

    const QuestWindow::Window window{ 1920, 1080, 3, 3};

    while (!window.close_window() && !QuestWindow::KeyboardInput::is_pressed(QuestWindow::Keyboard::ESCAPE)){
        glfwPollEvents();
        window.clear_buffer();
        window.swap_buffer();
    }

}