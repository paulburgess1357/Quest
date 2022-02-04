#include "pch.h"
#include "ShaderLoader.h"
#include "QuestUtility/String/FileToString.h"

namespace QuestEngine::API::OpenGL {

	ShaderLoader::ShaderLoader(const QuestEngineAPI& engine_api)
		:m_engine_api{ engine_api } {
	}

	void ShaderLoader::load_shader_program(const std::string& shader_program_id, std::string vertex, std::string fragment, const bool from_file) const {
		if(from_file) {
			vertex = QuestUtility::String::FileToString::load(vertex);
			fragment = QuestUtility::String::FileToString::load(fragment);
		}

		m_engine_api.load_shader(shader_program_id, {
			std::pair{QuestGLCore::Shader::ShaderEnum::VERTEX, vertex },
			std::pair{QuestGLCore::Shader::ShaderEnum::FRAGMENT, fragment }
		});
	}

} // namespace QuestEngine::API::OpenGL