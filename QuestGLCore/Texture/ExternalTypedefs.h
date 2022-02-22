#pragma once
#include "QuestGLCore/Texture/Typedefs.h"
#include "QuestGLCore/Texture/TextureCreator.h"
#include "QuestGLCore/Texture/BlankTextureEnum.h"
#include "QuestGLCore/Texture/TextureEnum.h"
#include <glad/glad.h>

namespace QuestGLCore::Texture {
	using Texture = TextureHandle;
	using StandardTextureCreator2D = StandardTextureCreator<GL_TEXTURE_2D>;
	using HDRTextureCreator2D = HDRTextureCreator<GL_TEXTURE_2D>;

	using BlankTextureEnum = BlankTextureEnum;
	using TextureEnum = TextureEnum;
} // namespace QuestEngine::Texture
