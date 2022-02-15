#pragma once
#include "QuestGLCore/Framebuffer/Framebuffer.h"
#include "QuestGLCore/Framebuffer/FramebufferPostProcess.h"
#include <glad/glad.h>

namespace QuestGLCore::Framebuffer {
	using Framebuffer2D = Framebuffer<GL_TEXTURE_2D>;
	using FramebufferPostProcess2D = FramebufferPostProcess<GL_TEXTURE_2D>;
} // namespace QuestGLCore::Texture#pragma once
