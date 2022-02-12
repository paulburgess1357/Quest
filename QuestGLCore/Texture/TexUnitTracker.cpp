#include "pch.h"
#include "TexUnitTracker.h"

namespace QuestGLCore::Texture {

	TexUnitTexHandle::TexUnitTexHandle(const GLenum tex_unit, TextureHandle* texture_handle)
		:m_tex_unit{ tex_unit }, m_handle{ texture_handle } {
	}

	void TexUnitTracker::register_texture(const std::string& texture_name_in_shader, Shader::ShaderProgram* shader_program, TextureHandle* texture_handle) {
		shader_program->bind();
		shader_program->set_uniform(texture_name_in_shader, m_current_tex_unit);
		m_texture_tracker.emplace_back(GL_TEXTURE0 + m_current_tex_unit, texture_handle);
		++m_current_tex_unit;
		shader_program->unbind();
	}

	void TexUnitTracker::bind() const {
		for(const auto& tex_unit_tex_handle : m_texture_tracker) {
			glActiveTexture(tex_unit_tex_handle.m_tex_unit);
			tex_unit_tex_handle.m_handle->bind();
		}
	}

	void TexUnitTracker::unbind() const {
		for (const auto& tex_unit_tex_handle : m_texture_tracker) {
			tex_unit_tex_handle.m_handle->unbind();
		}
	}

} // QuestGLCore::Texture