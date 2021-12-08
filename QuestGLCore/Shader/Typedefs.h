#pragma once
#include "QuestGLCore/Handle/Template/HandleTemplate.h"
#include "QuestGLCore/Handle/Traits/ShaderProgram.h"

namespace QuestGLCore::Typedefs {
	using ShaderProgramHandle = Handle::HandleTemplate<Traits::ShaderProgramTraits, Typedefs::HandleTypedef>;
 } // QuestGLCore::ShaderProgram
