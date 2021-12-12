#pragma once
#include "QuestGLCore/Shader/ShaderEnum.h"
#include "QuestGLCore/Shader/Typedefs.h"
#include "QuestGLCore/Handle/Typedefs.h"
#include <unordered_map>

namespace QuestGLCore::Shader {

	class ShaderProgramCreator {

	public:
		explicit ShaderProgramCreator(const std::unordered_map<ShaderEnum, std::string>& shader_string_map);
		[[nodiscard]] Typedefs::ShaderProgramHandle create() const;

	private:
		[[nodiscard]] static Typedefs::GLHandle load_glsl_shader(const ShaderEnum, const std::string& shader_string);
		
		static void check_shader(const Typedefs::GLHandle handle);
		static void check_shader_program(const Typedefs::GLHandle handle);

		std::unordered_map<ShaderEnum, std::string> m_shader_string_map{};

	};

} // namespace QuestGLCore::Shader