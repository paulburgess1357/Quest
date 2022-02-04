#pragma once
#include "QuestEngine/Using/Resource.h"
#include <glm/glm.hpp>

namespace QuestEngine::Resource {

	class ResourceManager {

	public:
		// ======================== Shader ========================
		[[nodiscard]] Shader::ShaderProgram& get_shader(const std::string& shader_id);
		[[nodiscard]] Shader::ShaderProgram* get_shader_pointer(const std::string& shader_id);
		void load_shader(const std::string& shader_id, const std::initializer_list<std::pair<Shader::ShaderEnum, std::string>> shaders);
		void shader_qc() const;

		// ======================== Model ========================
		[[nodiscard]] Model::StandardModel& get_model(const std::string& model_id);
		[[nodiscard]] Model::StandardModel* get_model_pointer(const std::string& model_id);
		void load_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::StandardMesh>& meshes);

		// ==================== Indexed Model ====================
		[[nodiscard]] Model::IndexedModel& get_indexed_model(const std::string& model_id);
		[[nodiscard]] Model::IndexedModel* get_indexed_model_pointer(const std::string& model_id);
		void load_indexed_model(const std::string& model_id, Shader::ShaderProgram& shader_program, std::vector<Model::IndexedMesh>& meshes);

		// ======================= Camera ========================
		[[nodiscard]] Camera::Camera& get_camera(const std::string& camera_id);
		[[nodiscard]] Camera::Camera* get_camera_pointer(const std::string& camera_id);
		void load_camera(const std::string& camera_id, const glm::vec3& camera_position, const glm::vec3& pt_to_look_at_in_world);

	private:
		ShaderResource m_shader_resource;
		StandardModelResource m_standard_model_resource;
		IndexedModelResource m_indexed_model_resource;
		CameraResource m_camera_resource;
		
	};

} // namespace QuestEngine::Resource