#pragma once
#include "QuestGLCore/VertexData/VertexData.h"
#include "QuestGLCore/VertexData/VertexDataElement.h"
#include "QuestGLCore/Texture/TexUnitTracker.h"
#include "QuestGLCore/Texture/Typedefs.h"
#include "QuestGLCore/Texture/BlankTextureEnum.h"

namespace QuestGLCore::Model {

	template<typename T>
	class Mesh {

	public:
		explicit Mesh(T vertex_data)
			:m_vertex_data{ std::move(vertex_data) } {
		}

		void draw() const {
			// Bind materials
			m_tex_unit_tracker.bind();
			m_vertex_data.draw();
			// Unbind materials
			// m_tex_unit_tracker.unbind();
		}

		void register_texture(const Texture::TextureEnum texture_type, Shader::ShaderProgram* shader_program, Texture::TextureHandle* texture_handle) {
			m_tex_unit_tracker.register_texture(texture_type, shader_program, texture_handle);
		}

	private:
		T m_vertex_data;
		Texture::TexUnitTracker m_tex_unit_tracker;
	};

} // namespace QuestGLCore::Model 