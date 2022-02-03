#pragma once
#include "QuestEngine/API/EngineAPI.h"

namespace QuestEngine::API::OpenGL {

	class ShaderLoader {

	public:
		ShaderLoader(const QuestEngineAPI& engine_api);
		void load_shader_program(const std::string& shader_program_name, std::string vertex, std::string fragment, const bool from_file = true) const;

	private:
		const QuestEngineAPI& m_engine_api;

	};

} // namespace QuestEngine::API::OpenGL