#pragma once
#include "QuestEngine/Engine/Engine.h"
#include <string>
#include <memory>

namespace QuestEngine::API {

	class QuestEngineAPI {

	public:
		QuestEngineAPI(const int width = 1920, const int height = 1080);
		void run() const;

		void load_shader(const std::string& shader_id, const std::initializer_list<std::pair<QuestGLCore::Shader::ShaderEnum, std::string>> shaders) const;

	private:
		std::unique_ptr<Engine::Engine> m_engine = nullptr;
	};

} // namespace QuestEngine::API