#pragma once
#include <glad/glad.h>

// Source for this idea:
// https://www.youtube.com/watch?v=BBSrEdhPM6s @1hr

namespace QuestGLCore::OGLResolution {

	//enum class OglDimensions {
	//	D1,
	//	D2,
	//	D3
	//};

	class OglTextureFunctionResolution {
	public:
		template<GLenum TextureType>
		static auto get_function() {
			if constexpr (TextureType == GL_TEXTURE_1D) { return glTexImage1D; }
			if constexpr (TextureType == GL_TEXTURE_2D) { return glTexImage2D; }
			if constexpr (TextureType == GL_TEXTURE_3D) { return glTexImage3D; }
		}
	};

	class OglFramebufferFunctionResolution {
	public:
		template<GLenum TextureType>
		static auto get_function() {
			if constexpr (TextureType == GL_TEXTURE_2D) { return glFramebufferTexture2D; }
		}
	};

} // namespace QuestGLCore::OGLResolution
