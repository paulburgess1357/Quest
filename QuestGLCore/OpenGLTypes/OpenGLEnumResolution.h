#pragma once
#include <glad/glad.h>

#include "QuestGLCore/OpenGLTypes/OpenGLTypeResoultionException.h"
#include "QuestGLCore/Framebuffer/FramebufferEnum.h"

namespace QuestGLCore::OGLResolution {

	class FramebufferBlitResolution {
	public:
		static GLbitfield get_bitfield(const Framebuffer::FramebufferBlitEnum framebuffer_blit_enum) {
			if(framebuffer_blit_enum == Framebuffer::FramebufferBlitEnum::Depth) {
				return GL_DEPTH_BUFFER_BIT;
			}
			throw OGLTypeResolutionException();
		}
	};

} // namespace QuestGLCore::OGLResolution