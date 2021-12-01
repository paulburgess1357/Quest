#pragma once
#include "QuestGLCore/Shader/ShaderType.h"
#include "QuestGLCore/Shader/ShaderTypedefs.h"
#include "QuestGLCore/Typedefs/Typedefs.h"
#include <unordered_map>

namespace QuestGLCore::Shader {

	class ShaderProgramCreator {

	public:
		explicit ShaderProgramCreator(const std::unordered_map<ShaderType, std::string>& shader_string_map);
		[[nodiscard]] ShaderProgramHandle create() const;

	private:
		[[nodiscard]] static Typedefs::HandleTypedef load_glsl_shader(const ShaderType, const std::string& shader_string);
		
		static void check_shader(const Typedefs::HandleTypedef handle);
		static void check_shader_program(const Typedefs::HandleTypedef handle);

		std::unordered_map<ShaderType, std::string> m_shader_string_map{};

	};

} // namespace QuestGLCore::Shader