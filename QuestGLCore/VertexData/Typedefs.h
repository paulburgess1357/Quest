#pragma once
#include "QuestGLCore/VertexData/VertexDataStruct.h"

namespace QuestGLCore::Typedefs {
	using VertexArray = VertexData::VertexDataStruct<GL_ARRAY_BUFFER>;
	using VertexElement = VertexData::VertexDataElementStruct<GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER>;
} // namespace OpenGLCore::VertexData