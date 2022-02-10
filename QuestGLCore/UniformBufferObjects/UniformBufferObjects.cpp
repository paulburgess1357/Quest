#include "pch.h"
#include "UniformBufferObjects.h"

namespace QuestGLCore::UniformBufferObjects {

	unsigned int UniformBufferObject::binding_point_to_set{ 0 };

	UniformBufferObject::UniformBufferObject(std::string uniform_id)
		:m_handle{ GL_UNIFORM_BUFFER },
		m_binding_point{ 0 },
		m_uniform_id{ std::move(uniform_id) }{
	}

	void UniformBufferObject::bind() const {
		m_handle.bind();
	}

	void UniformBufferObject::unbind() const {
		m_handle.unbind();
	}

	std::string UniformBufferObject::get_uniform_id() const {
		return m_uniform_id;
	}

	GLuint UniformBufferObject::get_binding_point() const {
		return m_binding_point;
	}

	void UniformBufferObject::allocate_buffer_memory(const int byte_num) {
		m_handle.bind();
		// Allocate data
		glBufferData(GL_UNIFORM_BUFFER, byte_num, nullptr, GL_DYNAMIC_DRAW);
		// Set binding point
		m_binding_point = binding_point_to_set;
		glBindBufferBase(GL_UNIFORM_BUFFER, m_binding_point, m_handle.get_handle());
		m_handle.unbind();

		// Update overall binding point for future ubos
		++binding_point_to_set;
	}

	// Overloads (only allowing glm types)
	void UniformBufferObject::send_data_to_buffer(const glm::vec2& data_to_send) const {
		send_data_to_buffer<glm::vec2>(data_to_send);
	}
	void UniformBufferObject::send_data_to_buffer(const glm::vec3& data_to_send) const{
		send_data_to_buffer<glm::vec3>(data_to_send);
	}
	void UniformBufferObject::send_data_to_buffer(const glm::vec4& data_to_send) const {
		send_data_to_buffer<glm::vec4>(data_to_send);
	}
	void UniformBufferObject::send_data_to_buffer(const glm::mat2& data_to_send) const {
		send_data_to_buffer<glm::mat2>(data_to_send);
	}
	void UniformBufferObject::send_data_to_buffer(const glm::mat3& data_to_send) const {
		send_data_to_buffer<glm::mat3>(data_to_send);
	}
	void UniformBufferObject::send_data_to_buffer(const glm::mat4& data_to_send) const {
		send_data_to_buffer<glm::mat4>(data_to_send);
	}

} // namespace QuestGLCore::Shader