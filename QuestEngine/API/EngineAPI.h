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

		// Model
		void load_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::StandardMesh>& meshes) const;
		void load_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::IndexedMesh>& meshes) const;

		// Camera
		void load_camera(const std::string& camera_id, const glm::vec3& camera_position, const glm::vec3& pt_to_look_at_in_world) const;
		void set_active_camera(const std::string& camera_id) const;

		// Registry
		void load_model_into_registry(const std::string& model_id, const Model::ModelType model_type) const;

	private:
		// Model
		void load_model_into_registry_standard(const std::string& model_id, entt::entity& entity) const;
		void load_model_into_registry_indexed(const std::string& model_id, entt::entity& entity) const;

		std::unique_ptr<Engine::Engine> m_engine = nullptr;
	};

} // namespace QuestEngine::API