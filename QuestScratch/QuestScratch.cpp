#include <iostream>
#include "QuestUtility/ImageLoading/StandardImageLoader.h"
#include "QuestUtility/ImageLoading/HDRImageLoader.h"
#include "QuestGLCore/Texture/TextureCreator.h"
#include "QuestWindow/Include/Window.h"
#include <glad/glad.h>

int main(){

	QuestWindow::OpenGL::OGLWindow my_window{ 1920, 1080 };

	const auto image_loader = QuestUtility::ImageLoading::StandardImageLoaderFromFile("C:/users/paulb/desktop/maple.png", false);
	const QuestGLCore::Texture::StandardTextureCreator<GL_TEXTURE_2D> texture_generator { image_loader , true };
	auto result = texture_generator.generate_texture();


	std::cout << "hello world" << std::endl;
}
