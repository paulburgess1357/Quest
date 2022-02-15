#pragma once
#include "QuestGLCore/Texture/Typedefs.h"
#include "QuestGLCore/Texture/TextureCreator.h"
#include <glad/glad.h>

namespace QuestGLCore::Texture {
	using Texture = TextureHandle;
	using StandardTextureCreator2D = StandardTextureCreator<GL_TEXTURE_2D>;
	using HDRTextureCreator2D = HDRTextureCreator<GL_TEXTURE_2D>;
} // namespace QuestEngine::Texture
