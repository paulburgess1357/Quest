#pragma once
#include "QuestEngine/Using/Resource.h"
#include <glm/glm.hpp>

namespace QuestEngine::Resource {

	class ResourceManager {

	public:
		ResourceManager();

		// ======================== Shader ========================
		[[nodiscard]] Shader::ShaderProgram& get_shader(const std::string& shader_id);
		[[nodiscard]] Shader::ShaderProgram* get_shader_pointer(const std::string& shader_id);
		void load_shader(const std::string& shader_id, const std::unordered_map<Shader::ShaderEnum, std::string>& shader_string_map, const bool link_ubo_matrices);
		void load_shader(const std::string& shader_id, Shader::ShaderProgram& shader_program, const bool link_ubo_matrices);
		void shader_qc() const;

		// ======================== Model ========================
		[[nodiscard]] Model::StandardModel& get_model(const std::string& model_id);
		[[nodiscard]] Model::StandardModel* get_model_pointer(const std::string& model_id);
		void load_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::StandardMesh>& meshes);
		void load_model(const std::string& model_id, Model::StandardModel& model);

		// ==================== Indexed Model ====================
		[[nodiscard]] Model::IndexedModel& get_indexed_model(const std::string& model_id);
		[[nodiscard]] Model::IndexedModel* get_indexed_model_pointer(const std::string& model_id);
		void load_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::IndexedMesh>& meshes);
		void load_model(const std::string& model_id, Model::IndexedModel& model);

		// ======================= Camera ========================
		[[nodiscard]] Camera::Camera& get_camera(const std::string& camera_id);
		[[nodiscard]] Camera::Camera* get_camera_pointer(const std::string& camera_id);
		void load_camera(const std::string& camera_id, const glm::vec3& camera_position, const glm::vec3& pt_to_look_at_in_world);
		void load_camera(const std::string& camera_id, const Camera::Camera& camera);

		// ========================= UBO =========================
		[[nodiscard]] UniformBufferObjects::UniformBufferObject& get_ubo(const std::string& ubo_id);
		[[nodiscard]] UniformBufferObjects::UniformBufferObject* get_ubo_pointer(const std::string& ubo_id);
		void load_ubo(const std::string& ubo_id);
		void load_ubo(const std::string& ubo_id, UniformBufferObjects::UniformBufferObject& ubo);

		// ======================= Texture ========================
		[[nodiscard]] Texture::Texture& get_texture(const std::string& texture_id);
		[[nodiscard]] Texture::Texture* get_texture_ptr(const std::string& texture_id);
		void load_texture2D(const std::string& texture_id, Texture::Texture& texture);

	private:
		void load_main_camera();
		void load_ubo_matrices();
		void load_default_texture();

		ShaderResource m_shader_resource;
		StandardModelResource m_standard_model_resource;
		IndexedModelResource m_indexed_model_resource;
		CameraResource m_camera_resource;
		UBOResource m_ubo_resource;
		TextureResource m_texture_resource;
		
	};

} // namespace QuestEngine::Resource