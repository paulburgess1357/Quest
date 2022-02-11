#pragma once
// add headers that you want to pre-compile here
#include <Windows.h>
#include "framework.h"

// OglTypes
#include "QuestGLCore/OpenGLTypes/OglTypeResolution.h"

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

// Model
#include "QuestGLCore/Model/Model.h"
#include "QuestGLCore/Model/Mesh.h"

// UBO
#include "QuestGLCore/UniformBufferObjects/UniformBufferObjects.h"
#include "QuestGLCore/UniformBufferObjects/UniformBufferExceptions.h"

// Misc
#include "QuestGLCore/Constants/Constants.h"

// Texture
#include "QuestGLCore/Texture/OpenGLTextureCreator.h"
#include "QuestGLCore/Texture/OpenGLTextureFormat.h"
#include "QuestGLCore/Texture/Typedefs.h"