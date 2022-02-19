#pragma once
#include "QuestGLCore/OpenGLTypes/OpenGLTypeResoultionException.h"
#include "QuestGLCore/Framebuffer/FramebufferEnum.h"
#include "QuestGLCore/Model/ModelEnums.h"
#include <glad/glad.h>

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

	class ModelDrawTypeResolution {
	public:
		static GLenum get_draw_mode(const Model::ModelDrawMode draw_type) {
			if(draw_type == Model::ModelDrawMode::Triangles) {
				return GL_TRIANGLES;
			}
			throw OGLTypeResolutionException();
		}
	};

} // namespace QuestGLCore::OGLResolution