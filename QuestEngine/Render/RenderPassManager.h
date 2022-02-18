#pragma once
#include "QuestEngine/Using/Framebuffer.h"
#include "QuestEngine/Using/Shader.h"
#include "QuestEngine/Using/Model.h"
#include "QuestEngine/Resource/ResourceManager.h"
#include <entt/entt.hpp>

namespace QuestEngine::Render {

	class RenderPassManager {

	public:
		RenderPassManager(const int width, const int height, entt::registry& active_registry, Resource::ResourceManager& resource_manager);
		void render() const;
		void set_active_registry(entt::registry& registry);
		void resize_attachments(const int width, const int height);

	private:
		void deferred_pass() const;
		void light_pass() const;
		void forward_pass() const;
		void default_framebuffer_pass() const;
		void draw_post_process() const;

		void load_shaders(Resource::ResourceManager& resource_manager);
		void set_pointlight_shader(Shader::ShaderProgram& shader_program);
		void set_postprocess_shader(Shader::ShaderProgram& shader_program);
		void set_pointlight_texture_uniforms() const;
		void set_postprocess_texture_uniforms() const;

		// RGBA16F_NEAREST, RGBA16F_NEAREST, RGBA_NEAREST
		// Position,        Normals,         Color + Specular
		Framebuffer::FramebufferGBuffer2D m_g_buffer;

		// RGBA_LINEAR
		// Scene colors
		Framebuffer::FramebufferPostProcessStandard2D m_post_process_framebuffer;

		Shader::ShaderProgram* m_pointlight_shader;
		Shader::ShaderProgram* m_postprocess_shader;

		Model::IndexedMeshQuad m_quad;
		entt::registry* m_active_registry;
	};


} // namespace QuestEngine::Render


