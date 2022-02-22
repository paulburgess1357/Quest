#pragma once
#include "QuestEngine/Engine/Engine.h"
#include "QuestEngine/Using/Resource.h"
#include <string>

namespace QuestEngine::API {

	class ResourceAPI {

	public:
		explicit ResourceAPI(Engine::Engine* engine);

		// ============ Resource Loading ============
		[[nodiscard]] Shader::ShaderProgram& get_shader(const std::string& shader_id) const;
		void load_shader(const std::string& shader_id, Shader::ShaderProgram& shader_program, const bool link_ubo_matrices) const;
		void load_shader(const std::string& shader_id, const std::unordered_map<Shader::ShaderEnum, std::string>& shader_string_map, const bool link_ubo_matrices) const;

		void load_model(const std::string& model_id, Model::StandardModel& model) const;
		void load_model(const std::string& model_id, std::vector<Model::StandardMesh>& meshes) const;

		void load_model(const std::string& model_id, Model::IndexedModel& model) const;
		void load_model(const std::string& model_id, std::vector<Model::IndexedMesh>& meshes) const;

		void load_camera(const std::string& camera_id, const Camera::Camera& camera) const;
		void load_camera(const std::string& camera_id, const glm::vec3& camera_position, const glm::vec3& pt_to_look_at_in_world) const;

		void load_texture2D(const std::string& texture_id, Texture::Texture& texture) const;

		// ============ Resource Interaction ============
		[[nodiscard]] Model::StandardModel* get_model_pointer(const std::string& model_id) const;
		[[nodiscard]] Model::IndexedModel* get_indexed_model_pointer(const std::string& model_id) const;
		[[nodiscard]] Texture::Texture* get_texture_pointer(const std::string& texture_id) const;
		[[nodiscard]] Shader::ShaderProgram* get_shader_pointer(const std::string& shader_id) const;

	private:
		Resource::ResourceManager& m_engine_resource_manager;
	};

} // namespace QuestEngine::API