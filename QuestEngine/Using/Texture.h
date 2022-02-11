#pragma once
#include "QuestGLCore/Texture/Typedefs.h"
#include "QuestGLCore/Texture/OpenGLTextureCreator.h"

namespace QuestEngine::Texture {
	using Texture = QuestGLCore::Texture::TextureHandle;
	using StandardTextureCreator2D = QuestGLCore::Texture::StandardTextureCreator<GL_TEXTURE_2D>;
	using HDRTextureCreator2D = QuestGLCore::Texture::HDRTextureCreator<GL_TEXTURE_2D>;
} // namespace QuestEngine::Texture
