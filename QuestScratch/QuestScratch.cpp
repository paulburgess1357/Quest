#include <iostream>
#include "TemplateTest/WindowScratch.h"

int main(){

    TemplateTest::Window<TemplateTest::OGLWindow> ogl_window;
    ogl_window.swap_buffer();


    TemplateTest::Window<TemplateTest::VulkanWindow> vulkan_window;
    vulkan_window.swap_buffer();


    std::cout << "Hello World!\n";
}