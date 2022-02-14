#pragma once
#include "QuestGLCore/Handle/Template/HandleTemplate.h"
#include "QuestGLCore/Handle/Traits/Framebuffer.h"
#include "QuestGLCore/Handle/Traits/Renderbuffer.h"

namespace QuestGLCore::Framebuffer {
	using FramebufferHandle = Handle::HandleTemplate<Traits::FramebufferTraits, Typedefs::GLHandle>;
	using RenderbufferHandle = Handle::HandleTemplate<Traits::RenderbufferTraits, Typedefs::GLHandle>;
} // namespace QuestGLCore::Texture