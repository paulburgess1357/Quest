#pragma once

namespace QuestEngine::Camera {

	class Camera {

	public:
		Camera(const glm::vec3& camera_position, const glm::vec3& pt_to_look_at_in_world);
		[[nodiscard]] glm::mat4 get_view_matrix() const;

	private:
		void init_camera(const glm::vec3& pt_to_look_at_in_world);
		void set_view_matrix();

		glm::vec3 m_camera_position;
		glm::vec3 m_camera_forward;
		glm::vec3 m_camera_right;
		glm::vec3 m_camera_up;

		glm::vec3 m_world_up;
		glm::mat4 m_view_matrix;
	};

} // namespace QuestEngine::Camera