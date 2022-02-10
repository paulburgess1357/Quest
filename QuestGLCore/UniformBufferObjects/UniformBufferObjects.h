#pragma once
#include "QuestGLCore/Handle/Template/HandleTemplate.h"
#include "QuestGLCore/Handle/Traits/Buffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace QuestGLCore::UniformBufferObjects {

	class UniformBufferObject {

	public:
		explicit UniformBufferObject(std::string uniform_id);
		void bind() const;
		void unbind() const;
		[[nodiscard]] std::string get_uniform_id() const;
		[[nodiscard]] GLuint get_binding_point() const;

		void allocate_buffer_memory(const int byte_num);
		void send_data_to_buffer(const std::string& buffer_id, const glm::vec2& data_to_send) const;
		void send_data_to_buffer(const std::string& buffer_id, const glm::vec3& data_to_send) const;
		void send_data_to_buffer(const std::string& buffer_id, const glm::vec4& data_to_send) const;
		void send_data_to_buffer(const std::string& buffer_id, const glm::mat2& data_to_send) const;
		void send_data_to_buffer(const std::string& buffer_id, const glm::mat3& data_to_send) const;
		void send_data_to_buffer(const std::string& buffer_id, const glm::mat4& data_to_send) const;

	private:
		template<typename T>
		void send_data_to_buffer(const std::string& buffer_id, const T& data_to_send) const {
			m_handle.bind();
			void* p_data = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
			memcpy(p_data, glm::value_ptr(data_to_send), sizeof(T));
			auto result = glUnmapBuffer(GL_UNIFORM_BUFFER);
			// m_ubo_map[buffer_id].unbind();
		}

		// < name, handle >
		Handle::HandleTemplate<Traits::BufferTraits, Typedefs::GLHandle> m_handle;
		GLuint m_binding_point;
		std::string m_uniform_id;

		static unsigned int binding_point_to_set;
	};

} // namespace QuestGLCore::Shader