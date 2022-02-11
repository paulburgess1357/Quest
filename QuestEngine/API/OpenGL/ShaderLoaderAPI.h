#pragma once
#include "QuestEngine/API/Neutral/ResourceAPI.h"

namespace QuestEngine::API::OpenGL {

	class ShaderLoaderAPI : public ResourceAPI {

	public:
		explicit ShaderLoaderAPI(Engine::Engine* engine);
		void load_shader(const std::string& shader_program_id, std::string vertex, std::string fragment, const bool from_file, const bool link_ubo_matrices) const;
		void load_shader(const std::string& shader_id, const std::initializer_list<std::pair<Shader::ShaderEnum, std::string>>& shaders, const bool link_ubo_matrices) const;

	};

} // namespace QuestEngine::API::OpenGL