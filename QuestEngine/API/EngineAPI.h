#pragma once
#include "QuestEngine/Engine/Engine.h"
#include <string>
#include <memory>

namespace QuestEngine::API {

	class QuestEngineAPI {

	public:
		QuestEngineAPI(const int width = 1920, const int height = 1080);
		void run() const;

		// Shader
		[[nodiscard]] Shader::ShaderProgram& get_shader(const std::string& shader_id) const;
		void load_shader(const std::string& shader_id, const std::initializer_list<std::pair<Shader::ShaderEnum, std::string>> shaders) const;

		// Standard Model
		[[nodiscard]] Model::StandardModel& get_model(const std::string& model_id) const;
		void load_model(const std::string& model_id, const Shader::ShaderProgram& shader_program, std::vector<Model::StandardMesh>& meshes) const;

		// Indexed Model
		[[nodiscard]] Model::IndexedModel& get_indexed_model(const std::string& model_id) const;
		void load_indexed_model(const std::string& model_id, const Shader::ShaderProgram& shader_program, std::vector<Model::IndexedMesh>& meshes) const;

	private:
		std::unique_ptr<Engine::Engine> m_engine = nullptr;
	};

} // namespace QuestEngine::API