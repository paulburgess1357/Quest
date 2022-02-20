#include "pch.h"
#include "RenderPassManager.h"
#include "QuestEngine/Using/LightState.h"
#include "QuestEngine/ECS/Systems/RenderSystem.h"

namespace QuestEngine::Render {

	//TODO 1) attachment resize should match imgui texture size
	// TODO2) the initlaization below should match (e.g. 500x500)
	//3) The handle_window_resize() should possibly be handle imgui viewport resize; not sure what happens if i expand the window itself but am still in an imgui viewport
	//4) when not showing us, i need to render to default framebuffer
	//5) i dont like that i have two 'handle window resize' functions (engine and here)

	//TODO the sizes for initlaization should be based on the viewport, NOT the window size i thinK!!!

	RenderPassManager::RenderPassManager(const Window::Window& window, entt::registry& active_registry)
		:m_window{ window },	
		m_window_width{ window.get_width() },
		m_window_height{ window.get_height() },	
		m_g_buffer{ m_window_width, m_window_height, { Texture::BlankTextureEnum::RGBA16F_NEAREST, Texture::BlankTextureEnum::RGBA16F_NEAREST, Texture::BlankTextureEnum::RGBA_NEAREST } },
		m_post_process_framebuffer{ m_window_width, m_window_height, { Texture::BlankTextureEnum::RGBA16F_LINEAR } },
		m_ui_framebuffer{ m_window_width, m_window_height, { Texture::BlankTextureEnum::RGBA16F_LINEAR } },
		m_pointlight_shader{ nullptr },
		m_postprocess_shader{ nullptr },
		m_quad_model_matrix{ 1.0f },
		m_active_registry{ &active_registry },
		m_user_interface{ window.get_window()}{
	}

	void RenderPassManager::render() {
		handle_window_resize(); // TODO maybet his should be handle_viewport_resize() since its based on imgui???
		handle_ui_toggle();

		deferred_pass();
		light_pass();
		forward_pass();

		if(show_ui) {
			imgui_viewport_pass(ui_viewport_width, ui_viewport_height);
		} else {
			default_framebuffer_pass();
		}
	}

	void RenderPassManager::handle_ui_toggle() {
		if(Window::KeyboardInput::is_initial_press(Window::Keyboard::F1)) {
			show_ui = !show_ui;
			if(show_ui) {
				resize_attachments(ui_viewport_width, ui_viewport_height);
			} else {
				resize_attachments(m_window_width, m_window_height);
			}
		}
	}


	void RenderPassManager::handle_window_resize() {
		if (Window::Window::get_width() != m_window_width || Window::Window::get_height() != m_window_height) {
			m_window_width = Window::Window::get_width();
			m_window_height = Window::Window::get_height();
			resize_attachments(m_window_width, m_window_height);
		}
		// m_projection_matrix.update_projection_matrix(m_window_width, m_window_height);
	}


	void RenderPassManager::deferred_pass() const {
		// Draw geometry/textures/normals to G-Buffer attachments

		// Draw Target: G-Buffer
		m_g_buffer.bind_write();
		Framebuffer::Framebuffer2D::clear_all_buffers();

		ECS::Systems::RenderSystem::render_deferred(*m_active_registry);
	}

	void RenderPassManager::light_pass() const {
		// Render G-Buffer attachments onto pointlight volume spheres to post-process framebuffer

		// Draw Target: Post-Process Framebuffer
		m_post_process_framebuffer.bind_write();
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

		// Bind G-Buffer Read (for depth info)
		// Bind Post-Process Write
		m_g_buffer.copy_to_framebuffer(m_post_process_framebuffer, Framebuffer::FramebufferBlitEnum::Depth);

		// Fully bind post-process framebuffer (blit does a read bind
		// from g-buffer and a write bind to post-process buffer)
		// m_post_process_framebuffer.bind_draw(); // TODO may not be necessary here because we aren't reading from it yet... ================ not sure why commenting this out fixes the zfighting stuff...
		ECS::Systems::RenderSystem::render_forward(*m_active_registry);
	}

	void RenderPassManager::default_framebuffer_pass() const {

		// Draw Target: Default Framebuffer (Window)
		m_post_process_framebuffer.unbind();
		Framebuffer::Framebuffer2D::clear_all_buffers();

		// Bind single color attachment that captures the final 'texture' of all the above processing
		draw_post_process();
	}

	void RenderPassManager::imgui_viewport_pass(const int width, const int height) const {

		// Draw Target: Ui Framebuffer
		m_ui_framebuffer.bind_write();
		Framebuffer::Framebuffer2D::clear_all_buffers();
		draw_post_process();
		
		// Imgui viewport requires default window bound:
		m_ui_framebuffer.unbind();
		Framebuffer::Framebuffer2D::clear_all_buffers();

		// Take post process color attachment texture handle and pass to Imgui
		draw_user_interface(reinterpret_cast<void*>(m_ui_framebuffer.get_color_attachment_raw_handle(0)), width, height);
	}

	void RenderPassManager::draw_post_process() const {
		m_postprocess_shader->bind();
		m_postprocess_shader->set_uniform(Constants::model_matrix, m_quad_model_matrix);
		m_post_process_framebuffer.bind_all_color_attachments();
		m_quad.draw();
	}

	void RenderPassManager::draw_user_interface(void* handle, const int width, const int height) const {
		UserInterface::UserInterface::begin_render();
		UserInterface::UserInterface::show_viewport(handle, width, height);
		m_user_interface.end_render();
	}

	void RenderPassManager::set_pointlight_shader(Shader::ShaderProgram& shader_program) {
		m_pointlight_shader = &shader_program;
	}

	void RenderPassManager::set_postprocess_shader(Shader::ShaderProgram& shader_program) {
		m_postprocess_shader = &shader_program;
	}

	void RenderPassManager::set_active_registry(entt::registry& registry) {
		m_active_registry = &registry;
	}

	void RenderPassManager::resize_attachments(const int width, const int height) {
		m_post_process_framebuffer.rescale_attachments(width, height);
		m_g_buffer.rescale_attachments(width, height);
		m_ui_framebuffer.rescale_attachments(width, height);
	}

} // namespace QuestEngine::Render