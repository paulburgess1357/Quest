#include "pch.h"
#include "ShaderLoaderAPI.h"
#include "QuestUtility/String/FileToString.h"

namespace QuestEngine::API::OpenGL {

	ShaderLoaderAPI::ShaderLoaderAPI(Engine::Engine* engine)
		:ResourceAPI{ engine } {
	}

	void ShaderLoaderAPI::load_shader(const std::string& shader_program_id, std::string vertex, std::string fragment, const bool from_file) const {
		if(from_file) {
			vertex = QuestUtility::String::FileToString::load(vertex);
			fragment = QuestUtility::String::FileToString::load(fragment);
		}

		ResourceAPI::load_shader(shader_program_id, {
			std::pair{QuestGLCore::Shader::ShaderEnum::VERTEX, vertex },
			std::pair{QuestGLCore::Shader::ShaderEnum::FRAGMENT, fragment }
		});
	}

} // namespace QuestEngine::API::OpenGL