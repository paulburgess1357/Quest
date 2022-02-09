#pragma once
#include "QuestEngine/API/Neutral/ResourceAPI.h"

namespace QuestEngine::API::OpenGL {

	class ShaderLoader {

	public:
		explicit ShaderLoader(ResourceAPI& resource_api);
		void load_shader_program(const std::string& shader_program_id, std::string vertex, std::string fragment, const bool from_file = true) const;

	private:
		ResourceAPI& m_resource_api;

	};

} // namespace QuestEngine::API::OpenGL