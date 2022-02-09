#pragma once
#include "QuestEngine/API/Neutral/ResourceAPI.h"

namespace QuestEngine::API::OpenGL {

	class ShaderLoaderAPI : public ResourceAPI {

	public:
		explicit ShaderLoaderAPI(Engine::Engine* engine);
		void load_shader(const std::string& shader_program_id, std::string vertex, std::string fragment, const bool from_file = true) const;

	};

} // namespace QuestEngine::API::OpenGL