#pragma once
#include <type_traits>
#include <glad/glad.h>

// Source for this idea:
// https://www.youtube.com/watch?v=BBSrEdhPM6s @1hr

namespace QuestGLCore::OGLResolution {

	//enum class OglDimensions {
	//	D1,
	//	D2,
	//	D3
	//};

	class OglTypeResolution {
	public:
		template<typename T>
		static GLenum get_type() {
			GLenum gl_type = GL_FLOAT;
			if constexpr (std::is_same<T, char>()) { gl_type = GL_BYTE; }
			if constexpr (std::is_same<T, unsigned char>()) { gl_type = GL_UNSIGNED_BYTE; }
			if constexpr (std::is_same<T, short>()) { gl_type = GL_SHORT; }
			if constexpr (std::is_same<T, unsigned short>()) { gl_type = GL_UNSIGNED_SHORT; }
			if constexpr (std::is_same<T, int>()) { gl_type = GL_INT; }
			if constexpr (std::is_same<T, unsigned int>()) { gl_type = GL_UNSIGNED_INT; }
			if constexpr (std::is_same<T, float>()) { gl_type = GL_FLOAT; }
			if constexpr (std::is_same<T, double>()) { gl_type = GL_DOUBLE; }
			return gl_type;
		}

	};

	class OglTextureFunctionResolution {
	public:
		template<GLenum TextureType>
		static auto get_function() {
			if constexpr (TextureType == GL_TEXTURE_1D) { return glTexImage1D; }
			if constexpr (TextureType == GL_TEXTURE_2D) { return glTexImage2D; }
			if constexpr (TextureType == GL_TEXTURE_3D) { return glTexImage3D; }
		}
	};

	//class OglFramebufferFunctionResolution {
	//public:
	//	template<GLenum TextureType>
	//	static auto get_function() {
	//		if constexpr (TextureType == GL_TEXTURE_2D) { return glFramebufferTexture2D; }
	//	}
	//};

} // namespace QuestGLCore::OGLResolution