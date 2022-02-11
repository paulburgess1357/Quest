#pragma once
#include "QuestUtility/Include/Logger.h"
#include <glad/glad.h>

namespace QuestGLCore::Texture {

	class OpenGLTextureFormat {
	public:
		static GLint  get_internal_format(const int color_channels) {
			// Update the below if statement when gamma correction custom framebuffer is added
			if (glIsEnabled(GL_FRAMEBUFFER_SRGB)) {
				// Texture format if working in linear space
				return get_format_gamma_correction_enabled(color_channels);
			}
			// Texture format (no gamma correction)
			QUEST_WARN("Loading texture NOT in linear space.  Gamma correction is not enabled according to <glIsEnabled(GL_FRAMEBUFFER_SRGB)>.  If gamma correction is enabled via custom framebuffer, the texture loading function needs to be updated!")
			return get_format_gamma_correction_disabled(color_channels);
		}

		static GLint  get_pixel_format(const int color_channels) {
			return get_format_gamma_correction_disabled(color_channels);
		}

	private:
		static GLint  get_format_gamma_correction_enabled(const int color_channels) {
			GLint  result{ 0 };
			switch (color_channels) {
				case 1:
					result = GL_RED;
					break;
				case 3:
					result = GL_SRGB;
					break;
				case 4:
					result = GL_SRGB_ALPHA;
					break;
				default:
					QUEST_ERROR("Unknown texture internal format being loaded in linear space!")
					break;
				}
			return result;
		}

		static GLint  get_format_gamma_correction_disabled(const int color_channels) {
			GLint  result{ 0 };
			switch (color_channels) {
				case 1:
					result = GL_RED;
					break;
				case 3:
					result = GL_RGB;
					break;
				case 4:
					result = GL_RGBA;
					break;
				default:
					QUEST_ERROR("Unknown texture internal format being loaded in non-linear space!")
					break;
				}
			return result;
		}
	};

} // namespace QuestGLCore::Texture