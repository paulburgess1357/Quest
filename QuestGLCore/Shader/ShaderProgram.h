#pragma once
#include "QuestGLCore/Shader/ShaderTypedefs.h"
#include "QuestGLCore/Shader/ShaderProgramCreator.h"

namespace QuestGLCore::Shader {

	class ShaderProgram {

	public:
		ShaderProgram(const std::string program_name, const ShaderProgramCreator shader_creator);
		// ShaderProgram(ShaderProgram&& source) noexcept;

	private:
		std::string m_program_name;
		ShaderProgramHandle m_handle;

	};

} // namespace QuestGLCore::ShaderProgram
