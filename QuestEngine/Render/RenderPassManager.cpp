#include "pch.h"
#include "RenderPassManager.h"
#include "QuestEngine/Using/LightState.h"
#include "QuestEngine/ECS/Systems/RenderSystem.h"
#include "QuestUtility/String/FileToString.h"

// todo possible optimnization (sending extra data currently to sphere loader...) normals and tex coords which aren't needed.

namespace QuestEngine::Render {

	RenderPassManager::RenderPassManager(const int width, const int height, entt::registry& active_registry, Resource::ResourceManager& resource_manager)
		:m_g_buffer{ width, height, { Texture::BlankTextureEnum::RGBA16F_NEAREST, Texture::BlankTextureEnum::RGBA16F_NEAREST, Texture::BlankTextureEnum::RGBA_NEAREST } },
		m_post_process_framebuffer{ width, height, { Texture::BlankTextureEnum::RGBA_LINEAR } },
		m_pointlight_shader{ nullptr },
		m_postprocess_shader{ nullptr },
		m_active_registry{ &active_registry }{
		load_shaders(resource_manager);
	}

	void RenderPassManager::load_shaders(Resource::ResourceManager& resource_manager) {

		// Post-Process Shader
		std::string vertex = QuestUtility::String::FileToString::load("../Resources/Shaders/PostProcess/PostProcessVertex.glsl");
		std::string fragment = QuestUtility::String::FileToString::load("../Resources/Shaders/PostProcess/PostProcessFragment.glsl");
		std::unordered_map<Shader::ShaderEnum, std::string> shader_map{
			{ Shader::ShaderEnum::VERTEX, vertex },
			{ Shader::ShaderEnum::FRAGMENT, fragment }
		};
		resource_manager.load_shader(Constants::post_process_shader, shader_map, false);
		set_postprocess_shader(resource_manager.get_shader(Constants::post_process_shader));

		// Pointlight Shader
		vertex = QuestUtility::String::FileToString::load("../Resources/Shaders/Pointlight/PointlightVertexLightpass.glsl");
		fragment = QuestUtility::String::FileToString::load("../Resources/Shaders/Pointlight/PointlightFragmentLightpass.glsl");
		shader_map = {
			{ Shader::ShaderEnum::VERTEX, vertex },
			{ Shader::ShaderEnum::FRAGMENT, fragment }
		};
		resource_manager.load_shader(Constants::pointlight_shader, shader_map, true);
		set_pointlight_shader(resource_manager.get_shader(Constants::pointlight_shader));
	}

	void RenderPassManager::render() const {
		deferred_pass();
		light_pass();
		forward_pass();
		default_framebuffer_pass();
	}

	void RenderPassManager::deferred_pass() const {
		// Draw geometry/textures/normals to G-Buffer attachments

		// Draw Target: G-Buffer
		m_g_buffer.bind();

		Framebuffer::Framebuffer2D::clear_all_buffers();
		ECS::Systems::RenderSystem::render_deferred(*m_active_registry);
	}

	void RenderPassManager::light_pass() const {
		// Render G-Buffer attachments onto pointlight volume spheres to post-process framebuffer

		// Draw Target: Post-Process Framebuffer
		m_post_process_framebuffer.bind();
		Framebuffer::Framebuffer2D::clear_all_buffers();

		QuestEngine::State::LightState::light_pass_start();
		ECS::Systems::RenderSystem::render_pointlight(*m_active_registry, m_pointlight_shader, m_g_buffer);
		QuestEngine::State::LightState::light_pass_end();
	}

	void RenderPassManager::forward_pass() const {

		// Draw Target: Post-Process Framebuffer

		// Copy depth information from g-buffer to post process framebuffer
		// Draw forward rendered objects to post-process framebuffer
		// i.e. This allows us to draw forward rendered objects within the
		// scene (rather than on top)
		m_g_buffer.copy_to_framebuffer(m_post_process_framebuffer, Framebuffer::FramebufferBlitEnum::Depth);

		// Fully bind post-process framebuffer (blit does a read bind
		// from g-buffer and a write bind to post-process buffer)
		m_post_process_framebuffer.bind(); // 
		ECS::Systems::RenderSystem::render_forward(*m_active_registry);
	}

	void RenderPassManager::default_framebuffer_pass() const {

		// Draw Target: Default Framebuffer (Window)
		m_post_process_framebuffer.unbind();
		Framebuffer::Framebuffer2D::clear_all_buffers();

		// Bind single color attachment that captures the final 'texture' of all the above processing
		draw_post_process();
	}

	void RenderPassManager::draw_post_process() const {
		m_postprocess_shader->bind();
		m_post_process_framebuffer.bind_all_color_attachments();
		m_quad.draw();
	}

	void RenderPassManager::set_pointlight_shader(Shader::ShaderProgram& shader_program) {
		m_pointlight_shader = &shader_program;
		set_pointlight_texture_uniforms();
	}

	void RenderPassManager::set_pointlight_texture_uniforms() const {
		m_pointlight_shader->bind();
		m_pointlight_shader->set_uniform("all_textures.position", 0);
		m_pointlight_shader->set_uniform("all_textures.normals", 1);
		m_pointlight_shader->set_uniform("all_textures.color_spec", 2);
		m_pointlight_shader->unbind();
	}

	void RenderPassManager::set_postprocess_shader(Shader::ShaderProgram& shader_program) {
		m_postprocess_shader = &shader_program;
		set_postprocess_texture_uniforms();
	}

	void RenderPassManager::set_postprocess_texture_uniforms() const {
		m_postprocess_shader->bind();
		m_postprocess_shader->set_uniform("post_process_texture", 0);
		m_postprocess_shader->unbind();
	}

	void RenderPassManager::set_active_registry(entt::registry& registry) {
		m_active_registry = &registry;
	}

	void RenderPassManager::resize_attachments(const int width, const int height) {
		m_post_process_framebuffer.rescale_attachments(width, height);
		m_g_buffer.rescale_attachments(width, height);
	}

} // namespace QuestEngine::Render