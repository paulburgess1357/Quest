#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include <Windows.h>
#include "framework.h"

// Handle
#include "QuestGLCore/Handle/Template/HandleTemplate.h"
#include "QuestGLCore/Handle/Traits/Vao.h"
#include "QuestGLCore/Handle/Traits/Buffer.h"
#include "QuestGLCore/Handle/Traits/ShaderProgram.h"
#include "QuestGLCore/Handle/Typedefs.h"

// Shader Program
#include "QuestGLCore/Shader/ShaderProgramCreator.h"
#include "QuestGLCore/Shader/ShaderProgram.h"
#include "QuestGLCore/Shader/ShaderExceptions.h"
#include "QuestGLCore/Shader/ShaderEnum.h"
#include "QuestGLCore/Shader/Typedefs.h"

// Vertex Data
#include "QuestGLCore/VertexData/VertexData.h"
#include "QuestGLCore/VertexData/VertexDataElement.h"

// Include
#include "QuestGLCore/Include/Shader.h"

#endif //PCH_H
