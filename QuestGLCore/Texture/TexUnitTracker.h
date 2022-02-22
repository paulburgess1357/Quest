#pragma once
#include "QuestGLCore/Texture/Typedefs.h"
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
		[[nodiscard]] static std::unordered_map<TextureEnum, std::pair<std::string, GLuint>> get_tex_unit_mapping();

	private:
		// <texture_name_in_shader, <tex unit, texture handle>
		std::vector<TexUnitTexHandle> m_texture_tracker;

		// Constant map:
		// <texture_name_in_shader, tex_unit>
		const static std::unordered_map<TextureEnum, std::pair<std::string, GLuint>> m_tex_unit_mapping;

	};

}