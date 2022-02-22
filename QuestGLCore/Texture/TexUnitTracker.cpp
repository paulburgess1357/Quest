#include "pch.h"
#include "TexUnitTracker.h"
#include "QuestGLCore/Constants/Constants.h"

namespace QuestGLCore::Texture {

	const std::unordered_map<TextureEnum, std::pair<std::string, GLuint>> TexUnitTracker::m_tex_unit_mapping{
		{ TextureEnum::Diffuse, {Constants::default_diffuse_shader_name, 0} },
		{ TextureEnum::Specular, {Constants::default_specular_shader_name, 1} },
		{ TextureEnum::Normal, {Constants::default_normal_shader_name, 2} },
	};

	TexUnitTexHandle::TexUnitTexHandle(const GLenum tex_unit, TextureHandle* texture_handle)
		:m_tex_unit{ tex_unit }, m_handle{ texture_handle } {
	}

	void TexUnitTracker::register_texture(const TextureEnum texture_type, Shader::ShaderProgram* shader_program, TextureHandle* texture_handle) {
		// The shader program isn't necessary here.  It is possible to simply
		// initialize the shader tex unit handles (e.g. diffuse, 0) elsewhere.
		// However, keeping this here has the advantage of ensuring that the
		// texture I am registering with the mesh exists in the shader program.
		// This is only done on load, so its impact is extremely small.
		shader_program->bind();
		const auto& [shader_uniform_name, tex_unit] = m_tex_unit_mapping.at(texture_type);
		shader_program->set_uniform(shader_uniform_name, tex_unit);
		shader_program->unbind();
		m_texture_tracker.emplace_back(GL_TEXTURE0 + tex_unit, texture_handle);
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

	std::unordered_map<TextureEnum, std::pair<std::string, GLuint>> TexUnitTracker::get_tex_unit_mapping() {
		return m_tex_unit_mapping;
	}

} // QuestGLCore::Texture