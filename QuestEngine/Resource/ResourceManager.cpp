#include "pch.h"
#include "ResourceManager.h"
#include "QuestEngine/Constants/Constants.h"
#include "QuestUtility/Logging/LogHandler.h"

namespace QuestEngine::Resource {

	ResourceManager::ResourceManager() {
		load_main_camera();
		load_ubo_matrices();
	}

	// ======================== Shader ========================
	Shader::ShaderProgram& ResourceManager::get_shader(const std::string& shader_id) {
		return m_shader_resource[shader_id];
	}

	Shader::ShaderProgram* ResourceManager::get_shader_pointer(const std::string& shader_id) {
		return m_shader_resource.get_pointer(shader_id);
	}

	void ResourceManager::load_shader(const std::string& shader_id, const std::unordered_map<Shader::ShaderEnum, std::string>& shader_string_map, const bool link_ubo_matrices) {
		m_shader_resource.load(shader_id, shader_id, Shader::ShaderProgramCreator{ shader_string_map });

		if (link_ubo_matrices) {
			get_shader(shader_id).link_shader_to_ubo(get_ubo(Constants::ubo_matrices));
		}
	}

	void ResourceManager::load_shader(const std::string& shader_id, Shader::ShaderProgram& shader_program, const bool link_ubo_matrices) {
		m_shader_resource.load(shader_id, shader_program);

		if (link_ubo_matrices) {
			get_shader(shader_id).link_shader_to_ubo(get_ubo(Constants::ubo_matrices));
		}
	}

	void ResourceManager::shader_qc() const {
		QUEST_TRACE("Checking Shader Uniforms Initialized")
		for(const auto& [shader_id, shader] : m_shader_resource) {
			shader.check_uniforms_initialized();
		}
		QUEST_TRACE("Passed")
	}

	// ======================== Model ========================
	Model::StandardModel& ResourceManager::get_model(const std::string& model_id) {
		return m_standard_model_resource[model_id];
	}

	Model::StandardModel* ResourceManager::get_model_pointer(const std::string& model_id) {
		return m_standard_model_resource.get_pointer(model_id);
	}

	void ResourceManager::load_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::StandardMesh>& meshes) {
		m_standard_model_resource.load(model_id, shader_program, std::move(meshes));
	}

	void ResourceManager::load_model(const std::string& model_id, Model::StandardModel& model) {
		m_standard_model_resource.load(model_id, model);
	}


	// ==================== Indexed Model ====================
	Model::IndexedModel& ResourceManager::get_indexed_model(const std::string& model_id) {
		return m_indexed_model_resource[model_id];
	}

	Model::IndexedModel* ResourceManager::get_indexed_model_pointer(const std::string& model_id) {
		return m_indexed_model_resource.get_pointer(model_id);
	}

	void ResourceManager::load_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::IndexedMesh>& meshes) {
		m_indexed_model_resource.load(model_id, shader_program, std::move(meshes));
	}

	void ResourceManager::load_model(const std::string& model_id, Model::IndexedModel& model) {
		m_indexed_model_resource.load(model_id, model);
	}


	// ==================== Camera ====================
	void ResourceManager::load_main_camera() {
		load_camera(Constants::main_camera, { 0.0f, 0.0f, -6.0f }, { 0.0f, 0.0f, 0.0f });
	}

	Camera::Camera& ResourceManager::get_camera(const std::string& camera_id) {
		return m_camera_resource[camera_id];
	}

	Camera::Camera* ResourceManager::get_camera_pointer(const std::string& camera_id) {
		return m_camera_resource.get_pointer(camera_id);
	}

	void ResourceManager::load_camera(const std::string& camera_id, const glm::vec3& camera_position, const glm::vec3& pt_to_look_at_in_world) {
		m_camera_resource.load(camera_id, camera_position, pt_to_look_at_in_world);
	}

	void ResourceManager::load_camera(const std::string& camera_id, const Camera::Camera& camera) {
		m_camera_resource.load(camera_id, camera);
	}


	// ==================== UBO ====================
	UniformBufferObjects::UniformBufferObject& ResourceManager::get_ubo(const std::string& ubo_id) {
		return m_ubo_resource[ubo_id];
	}

	UniformBufferObjects::UniformBufferObject* ResourceManager::get_ubo_pointer(const std::string& ubo_id) {
		return m_ubo_resource.get_pointer(ubo_id);
	}

	void ResourceManager::load_ubo(const std::string& ubo_id) {
		m_ubo_resource.load(ubo_id, ubo_id); // map key; ubo id for construction
	}

	void ResourceManager::load_ubo(const std::string& ubo_id, UniformBufferObjects::UniformBufferObject& ubo) {
		m_ubo_resource.load(ubo_id, ubo);
	}

	void ResourceManager::load_ubo_matrices() {
		const std::string ubo_id{ Constants::ubo_matrices };
		UniformBufferObjects::UniformBufferObject ubo{ ubo_id };
		ubo.allocate_buffer_memory(sizeof(glm::mat4));
		load_ubo(ubo_id, ubo);
	}

	// ==================== Texture ====================

	void ResourceManager::load_texture2D(const std::string& texture_id, Texture::Texture& texture) {
		// Safe load ensures no 'reloading' of texture under the same id
		m_texture_resource.safe_load(texture_id, std::move(texture));
	}

	Texture::Texture& ResourceManager::get_texture(const std::string& texture_id) {
		return m_texture_resource[texture_id];
	}

	Texture::Texture* ResourceManager::get_texture_ptr(const std::string& texture_id) {
		return m_texture_resource.get_pointer(texture_id);
	}

} // namespace QuestEngine::Resource