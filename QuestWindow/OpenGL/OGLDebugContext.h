// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#pragma once
#include "QuestUtility/Include/Logger.h"

// Source: https://learnopengl.com/In-Practice/Debugging

namespace QuestWindow::OpenGL {
    inline void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, 
        GLenum severity, GLsizei length, const char* message, const void* userParam) {

    	// Ignore non-significant error/warning codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
        QUEST_ERROR("Debug message: ({}): {}", id, message)
        switch (source) {
	        case GL_DEBUG_SOURCE_API:             QUEST_ERROR("Source: API") break;
	        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   QUEST_ERROR("Source: Window System") break;
	        case GL_DEBUG_SOURCE_SHADER_COMPILER: QUEST_ERROR("Source: Shader Compiler") break;
	        case GL_DEBUG_SOURCE_THIRD_PARTY:     QUEST_ERROR("Source: Third Party") break;
	        case GL_DEBUG_SOURCE_APPLICATION:     QUEST_ERROR("Source: Application") break;
	        case GL_DEBUG_SOURCE_OTHER:           QUEST_ERROR("Source: Other") break;
			default: QUEST_ERROR("Source: Default") break;
        }

        switch (type){
	        case GL_DEBUG_TYPE_ERROR:               QUEST_ERROR("Type: Error") break;
	        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: QUEST_ERROR("Type: Deprecated Behaviour") break;
	        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  QUEST_ERROR("Type: Undefined Behaviour") break;
	        case GL_DEBUG_TYPE_PORTABILITY:         QUEST_ERROR("Type: Portability") break;
	        case GL_DEBUG_TYPE_PERFORMANCE:         QUEST_ERROR("Type: Performance") break;
	        case GL_DEBUG_TYPE_MARKER:              QUEST_ERROR("Type: Marker") break;
	        case GL_DEBUG_TYPE_PUSH_GROUP:          QUEST_ERROR("Type: Push Group") break;
	        case GL_DEBUG_TYPE_POP_GROUP:           QUEST_ERROR("Type: Pop Group") break;
	        case GL_DEBUG_TYPE_OTHER:               QUEST_ERROR("Type: Other") break;
			default: QUEST_ERROR("Type: Default") break;
        }

        switch (severity){
	        case GL_DEBUG_SEVERITY_HIGH:         QUEST_ERROR("Severity: high") break;
	        case GL_DEBUG_SEVERITY_MEDIUM:       QUEST_ERROR("Severity: medium") break;
	        case GL_DEBUG_SEVERITY_LOW:          QUEST_ERROR("Severity: low") break;
	        case GL_DEBUG_SEVERITY_NOTIFICATION: QUEST_ERROR("Severity: notification") break;
			default: QUEST_ERROR("Severity: Default") break;
        }
		QUEST_BREAK()
    }

} // namespace QuestWindow::OpenGL

// Instantiate OpenGL debug context (must be during window initialization)
#ifdef DEBUG
#define InitOpenGLErrorCheck(...) int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags); if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) { QUEST_DEBUG("GLFW Debug Context Initiated") glEnable(GL_DEBUG_OUTPUT); glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); glDebugMessageCallback(glDebugOutput, nullptr); glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);}
#define InitGLFWOpenGLDebugContext(...) glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#else
#define InitOpenGLErrorCheck(...)
#define InitGLFWOpenGLDebugContext(...)
#endif
