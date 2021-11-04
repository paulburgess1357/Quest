#include "QuestWindow/Include/Window.h"

int main(){

    int x = 500;

    QuestWindow::Window window{ 1920, 1080, 3, 3};

    while (!window.close_window()){
        
        glfwPollEvents();
        window.clear_buffer();
        window.swap_buffer();
    }

}