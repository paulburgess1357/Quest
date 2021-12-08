#include "pch.h"
#include "ShaderProgram.h"

namespace QuestGLCore::Shader {

	ShaderProgram::ShaderProgram(const std::string program_name, const ShaderProgramCreator shader_creator)
		:m_program_name{ std::move(program_name) },
		m_handle{ shader_creator.create() } {
		QUEST_TRACE("Shader Program Created: <{}> | Handle: <{}>", m_program_name, m_handle.get_handle());
	}

} // namespace QuestGLCore::ShaderProgram