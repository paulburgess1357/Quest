#pragma once
#include "QuestEngine/Engine/Engine.h"
#include <string>

namespace QuestEngine::API {

	class ResourceAPI {

	public:
		explicit ResourceAPI(Engine::Engine* engine);

		// ============ Resource Loading ============
		[[nodiscard]] Shader::ShaderProgram& get_shader(const std::string& shader_id) const;
		void load_shader(const std::string& shader_id, Shader::ShaderProgram& shader_program) const;
		void load_shader(const std::string& shader_id, const std::initializer_list<std::pair<Shader::ShaderEnum, std::string>> shaders) const;

		void load_model(const std::string& model_id, Model::StandardModel& model) const;
		void load_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::StandardMesh>& meshes) const;

		void load_model(const std::string& model_id, Model::IndexedModel& model) const;
		void load_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::IndexedMesh>& meshes) const;

		void load_camera(const std::string& camera_id, const Camera::Camera& camera) const;
		void load_camera(const std::string& camera_id, const glm::vec3& camera_position, const glm::vec3& pt_to_look_at_in_world) const;

		// ============ Resource Interaction ============
		[[nodiscard]] Model::StandardModel* get_model_pointer(const std::string& model_id) const;
		[[nodiscard]] Model::IndexedModel* get_indexed_model_pointer(const std::string& model_id) const;

	private:
		Resource::ResourceManager& m_engine_resource_manager;
	};

} // namespace QuestEngine::API