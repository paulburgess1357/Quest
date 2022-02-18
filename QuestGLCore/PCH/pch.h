#pragma once
// add headers that you want to pre-compile here
#include <Windows.h>
#include "framework.h"

// OglTypes
#include "QuestGLCore/OpenGLTypes/OpenGLTypeResolution.h"
#include "QuestGLCore/OpenGLTypes/OpenGLEnumResolution.h"
#include "QuestGLCore/OpenGLTypes/OpenGLFunctionResolution.h"
#include "QuestGLCore/OpenGLTypes/OpenGLTypeResoultionException.h"

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
#include "QuestGLCore/Shader/ExternalTypedefs.h"

// Vertex Data
#include "QuestGLCore/VertexData/VertexData.h"
#include "QuestGLCore/VertexData/VertexDataElement.h"

// Model
#include "QuestGLCore/Model/Model.h"
#include "QuestGLCore/Model/Mesh.h"
#include "QuestGLCore/Model/MeshQuad.h"
#include "QuestGLCore/Model/ExternalTypedefs.h"

// UBO
#include "QuestGLCore/UniformBufferObjects/UniformBufferObjects.h"
#include "QuestGLCore/UniformBufferObjects/UniformBufferExceptions.h"
#include "QuestGLCore/UniformBufferObjects/ExternalTypedefs.h"

// Misc
#include "QuestGLCore/Constants/Constants.h"
#include "QuestGLCore/LightState/LightState.h"

// Texture
#include "QuestGLCore/Texture/TextureCreator.h"
#include "QuestGLCore/Texture/TextureFormat.h"
#include "QuestGLCore/Texture/TexUnitTracker.h"
#include "QuestGLCore/Texture/Typedefs.h"
#include "QuestGLCore/Texture/ExternalTypedefs.h"

// Framebuffer
#include "QuestGLCore/Framebuffer/Framebuffer.h"
#include "QuestGLCore/Framebuffer/Typedefs.h"
#include "QuestGLCore/Framebuffer/ExternalTypedefs.h"
#include "QuestGLCore/Framebuffer/FramebufferPostProcess.h"
#include "QuestGLCore/Framebuffer/FramebufferEnum.h"