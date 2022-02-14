#pragma once
#include "QuestGLCore/Framebuffer/Framebuffer.h"
#include "QuestGLCore/Texture/BlankTextureCreator.h"
#include <glad/glad.h>

namespace QuestGLCore::Framebuffer {
	 using FramebufferStandard2D = Framebuffer<Texture::StandardBlankFramebufferTextureCreator, GL_TEXTURE_2D>;
	 using FramebufferStandardHD16F2D = Framebuffer<Texture::HD16FBlankFramebufferTextureCreator, GL_TEXTURE_2D>;
	 using FramebufferStandardHD32F2D = Framebuffer<Texture::HD32FBlankFramebufferTextureCreator, GL_TEXTURE_2D>;
} // namespace QuestGLCore::Texture#pragma once
