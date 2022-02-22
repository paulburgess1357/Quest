#pragma once
#include "QuestGLCore/Texture/Typedefs.h"
#include "QuestGLCore/Shader/ShaderProgram.h"
#include "QuestGLCore/Texture/TextureEnum.h"

namespace QuestGLCore::Texture {

	struct TexUnitTexHandle {
		TexUnitTexHandle(const GLenum tex_unit, TextureHandle* texture_handle);
		GLenum m_tex_unit;
		TextureHandle* m_handle;
	};

	class TexUnitTracker {

	public:
		void register_texture(const TextureEnum texture_type, Shader::ShaderProgram* shader_program, TextureHandle* texture_handle);
		void bind() const;
		void unbind() const;

	private:
		// <texture_name_in_shader, <tex unit, texture handle>
		std::vector<TexUnitTexHandle> m_texture_tracker;
		GLuint m_current_tex_unit{ 0 };

		// Constant map:
		// <texture_name_in_shader, tex_unit>
		const static std::unordered_map<TextureEnum, std::pair<std::string, GLuint>> m_tex_unit_mapping;

	};

}