#include "pch.h"
#include "ResourceAPI.h"

namespace QuestEngine::API {

	ResourceAPI::ResourceAPI(Engine::Engine* engine)
		:m_engine_resource_manager{ engine->get_resource_manager() }{
	}

	// ======================== Shader ========================
	Shader::ShaderProgram& ResourceAPI::get_shader(const std::string& shader_id) const {
		return m_engine_resource_manager.get_shader(shader_id);
	}

	void ResourceAPI::load_shader(const std::string& shader_id, Shader::ShaderProgram& shader_program, const bool link_ubo_matrices) const {
		m_engine_resource_manager.load_shader(shader_id, shader_program, link_ubo_matrices);
	}

	void ResourceAPI::load_shader(const std::string& shader_id, const std::unordered_map<Shader::ShaderEnum, std::string>& shader_string_map, const bool link_ubo_matrices) const {
		m_engine_resource_manager.load_shader(shader_id, shader_string_map, link_ubo_matrices);
	}

	// ======================== Model ========================
	// Standard
	void ResourceAPI::load_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::StandardMesh>& meshes) const {
		m_engine_resource_manager.load_model(model_id, shader_program, meshes);
	}

	void ResourceAPI::load_model(const std::string& model_id, Model::StandardModel& model) const {
		m_engine_resource_manager.load_model(model_id, model);
	}

	// Indexed
	void ResourceAPI::load_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::IndexedMesh>& meshes) const {
		m_engine_resource_manager.load_model(model_id, shader_program, meshes);
	}

	void ResourceAPI::load_model(const std::string& model_id, Model::IndexedModel& model) const {
		m_engine_resource_manager.load_model(model_id, model);
	}

	Model::StandardModel* ResourceAPI::get_model_pointer(const std::string& model_id) const {
		return m_engine_resource_manager.get_model_pointer(model_id);
	}

	Model::IndexedModel* ResourceAPI::get_indexed_model_pointer(const std::string& model_id) const {
		return m_engine_resource_manager.get_indexed_model_pointer(model_id);
	}

	// ======================== Camera ========================
	void ResourceAPI::load_camera(const std::string& camera_id, const glm::vec3& camera_position, const glm::vec3& pt_to_look_at_in_world) const {
		m_engine_resource_manager.load_camera(camera_id, camera_position, pt_to_look_at_in_world);
	}

	void ResourceAPI::load_camera(const std::string& camera_id, const Camera::Camera& camera) const {
		m_engine_resource_manager.load_camera(camera_id, camera);
	}

	// ======================== Texture ========================
	void ResourceAPI::load_texture2D(const std::string& texture_id, Texture::Texture& texture) const {
		m_engine_resource_manager.load_texture2D(texture_id, texture);
	}

	Texture::Texture* ResourceAPI::get_texture_pointer(const std::string& texture_id) const {
		return m_engine_resource_manager.get_texture_ptr(texture_id);
	}



} // namespace QuestEngine::API