#pragma once
#include "QuestGLCore/Handle/Template/HandleTemplate.h"
#include "QuestGLCore/Handle/Traits/Texture.h"

namespace QuestGLCore::Texture {
	using TextureHandle = Handle::HandleTemplate<Traits::TextureTraits, Typedefs::GLHandle>;
} // namespace QuestGLCore::Texture