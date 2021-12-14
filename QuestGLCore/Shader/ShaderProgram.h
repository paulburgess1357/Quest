#pragma once
#include "QuestGLCore/Shader/ShaderProgramCreator.h"
#include "QuestGLCore/Shader/Typedefs.h"

namespace QuestGLCore::Shader {

	class ShaderProgram {

	public:
		ShaderProgram(const std::string program_name, const ShaderProgramCreator shader_creator);
		void bind() const;
		void unbind() const;

	private:
		std::string m_program_name;
		Typedefs::ShaderProgramHandle m_handle;

	};

} // namespace QuestGLCore::ShaderProgram
