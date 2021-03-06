#include "pch.h"
#include "RenderPassManager.h"
#include "QuestEngine/Using/GraphicsState.h"
#include "QuestEngine/ECS/Systems/RenderSystem.h"

namespace QuestEngine::Render {

	RenderPassManager::RenderPassManager(const Window::Window& window, entt::registry& active_registry)
		:m_window{ window },	
		m_window_width{ Window::Window::get_width() },
		m_window_height{ Window::Window::get_height() },
		m_framebuffer_width{ m_window_width },
		m_framebuffer_height{ m_window_height },
		m_g_buffer{ m_window_width, m_window_height, { Texture::BlankTextureEnum::RGBA16F_NEAREST, Texture::BlankTextureEnum::RGBA16F_NEAREST, Texture::BlankTextureEnum::RGBA_NEAREST } },
		m_post_process_framebuffer{ m_window_width, m_window_height, { Texture::BlankTextureEnum::RGBA16F_LINEAR } },
		m_ui_framebuffer{ m_window_width, m_window_height, { Texture::BlankTextureEnum::RGBA16F_LINEAR } },
		m_deferred_shader{ nullptr },
		m_pointlight_shader{ nullptr },
		m_postprocess_shader{ nullptr },
		m_forward_shader{ nullptr },
		m_quad_model_matrix{ 1.0f },
		m_active_registry{ &active_registry },
		m_user_interface{ window.get_window() }{
	}

	void RenderPassManager::render() {
		handle_window_resize();

		// Set fb viewport size:
 		Graphics::State::set_viewport(0, 0, m_framebuffer_width, m_framebuffer_height);
		deferred_pass();
		light_pass();
		forward_pass();

		handle_ui_toggle();
		final_pass();
	}

	void RenderPassManager::deferred_pass() const {
		// Draw geometry/textures/normals to G-Buffer attachments

		// Draw Target: G-Buffer
		m_g_buffer.bind_write();
		Framebuffer::Framebuffer2D::clear_all_buffers();

		ECS::Systems::RenderSystem::render_deferred(*m_active_registry, m_deferred_shader);
	}

	void RenderPassManager::light_pass() const {
		// Render G-Buffer attachments onto pointlight volume spheres to post-process framebuffer

		// Draw Target: Post-Process Framebuffer
		m_post_process_framebuffer.bind_write();
		Framebuffer::Framebuffer2D::clear_all_buffers();

		QuestEngine::Graphics::State::light_pass_start();
		ECS::Systems::RenderSystem::render_pointlight(*m_active_registry, m_pointlight_shader, m_g_buffer);
		QuestEngine::Graphics::State::light_pass_end();
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

		// Draw Target: (Still Post-Process Framebuffer)
		ECS::Systems::RenderSystem::render_forward(*m_active_registry, m_forward_shader);
	}

	void RenderPassManager::final_pass() const {
		// UI for full window display based on user input:
		if (m_show_ui) {
			imgui_viewport_pass();
		} else {
			default_framebuffer_pass();
		}
	}

	void RenderPassManager::default_framebuffer_pass() const {
		// Draw Target: Default Framebuffer (Window)
		m_post_process_framebuffer.unbind();
		Framebuffer::Framebuffer2D::clear_all_buffers();

		// Bind single color attachment that captures the final 'texture' of all the above processing
		Graphics::State::set_viewport(0, 0, Window::Window::get_width(), Window::Window::get_height());
		draw_post_process();
	}

	void RenderPassManager::imgui_viewport_pass() const {
		// Draw Target: Ui Framebuffer
		m_ui_framebuffer.bind_write();
		Framebuffer::Framebuffer2D::clear_all_buffers();
		draw_post_process();

		// Imgui viewport requires default window bound:
		m_ui_framebuffer.unbind();
		Framebuffer::Framebuffer2D::clear_all_buffers();

		draw_user_interface(reinterpret_cast<void*>(static_cast<intptr_t>(m_ui_framebuffer.get_color_attachment_raw_handle(0))));  // NOLINT(performance-no-int-to-ptr)
	}

	void RenderPassManager::draw_post_process() const {
		m_postprocess_shader->bind();
		// m_postprocess_shader->set_uniform(Constants::model_matrix, m_quad_model_matrix);
		m_post_process_framebuffer.bind_all_color_attachments();
		m_quad.draw();
	}

	void RenderPassManager::draw_user_interface(void* handle) const {
		UserInterface::UserInterface::begin_render();
		m_user_interface.show_viewport(handle);
		UserInterface::UserInterface::show_metrics();
		m_user_interface.end_render();
	}

	void RenderPassManager::handle_ui_toggle() {
		if (Window::KeyboardInput::is_initial_press(Window::Keyboard::F1)) {
			m_show_ui = !m_show_ui;
			if(m_show_ui) {
				reset_quad();
			} else {
				// Ensures any necessary transform that was ignored while the
				// ui was open is now applied
				transform_quad();
			}
		}
	}

	void RenderPassManager::resize_attachments(const int width, const int height) {
		m_post_process_framebuffer.resize_attachments(width, height);
		m_g_buffer.resize_attachments(width, height);
		m_ui_framebuffer.resize_attachments(width, height);
	}

	void RenderPassManager::handle_window_resize() {

		// The window resize must run regardless if the ui is showing or not.
		// This is necessary because we need the framebuffer textures to be
		// resized when the ui is open.  For example, if the ui is open, and
		// the user makes the main window (while the ui is open) much larger.
		// The displayed texture in the ui will be pixelated because its size
		// was based on the previous window size.  Running this regardless of
		// if the ui is open or not will ensure the displayed texture will not
		// be pixelated in the ui

		if (Window::Window::get_width() != m_window_width || Window::Window::get_height() != m_window_height) {
			set_window_dimensions();
			set_framebuffer_dimensions();
			resize_attachments(m_framebuffer_width, m_framebuffer_height);

			// Quad is only transformed when its displayed to the main window (not ui)
			if(!m_show_ui) {
				transform_quad();
			}

		}
	}

	void RenderPassManager::reset_quad() const{

		// When the window is resized, viewport and framebuffers are also resized.
		// The framebuffer attachments and viewport take into account the desired 16:9
		// aspect ratio.  The draw to the postprocess quad takes the above 16:9 ratio
		// texture and draws it to a quad.  This quad has a model_matrix transformation
		// that moves it to the center of the screen.

		// The ui takes the above texture (aka what was drawn to the quad) and
		// renders it to the UI viewport.  The UI viewport has its own logic
		// (viewport_position) that moves the viewport to the center of the UI window.
		// Once the viewport is in the center of the window, the quad is displayed.
		// Since the entire UI viewport is moved to the center of the UI window,
		// there is no need to do the model_matrix quad transformation.  The quad
		// needs to maintain its normalized device coordinates.

		// In summary, the difference is this:
		// Window Render: Quad is moved to the center of the screen via a model_matrix transformation to its Normalized Device Coordinates.
		// UI render: Viewport is centered; Quad displays on entire viewport

		m_postprocess_shader->bind();
		m_postprocess_shader->set_uniform(Constants::model_matrix, glm::mat4(1.0));
		m_postprocess_shader->unbind();
	}

	void RenderPassManager::set_window_dimensions() {
		m_window_width = Window::Window::get_width();
		m_window_height = Window::Window::get_height();
	}

	void RenderPassManager::set_framebuffer_dimensions() {
		const float aspect_ratio = Window::Window::get_aspect_ratio();
		m_framebuffer_width = static_cast<int>(static_cast<float>(m_window_height) * aspect_ratio);
		m_framebuffer_height = static_cast<int>(static_cast<float>(m_window_width) * 1.0f / aspect_ratio);

		if (m_window_height > m_framebuffer_height) {
			m_framebuffer_width = m_window_width;
		} else {
			m_framebuffer_height = m_window_height;
		}
	}

	void RenderPassManager::transform_quad() {
		glm::vec2 scale = glm::vec2{ m_framebuffer_width, m_framebuffer_height } / glm::vec2{ m_window_width, m_window_height };
		m_quad_model_matrix = glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
		m_postprocess_shader->bind();
		m_postprocess_shader->set_uniform(Constants::model_matrix, m_quad_model_matrix);
		m_postprocess_shader->unbind();
	}

	void RenderPassManager::set_pointlight_shader(Shader::ShaderProgram& shader_program) {
		m_pointlight_shader = &shader_program;
	}

	void RenderPassManager::set_deferred_shader(Shader::ShaderProgram& shader_program) {
		m_deferred_shader = &shader_program;
	}

	void RenderPassManager::set_forward_shader(Shader::ShaderProgram& shader_program) {
		m_forward_shader = &shader_program;
	}

	void RenderPassManager::set_postprocess_shader(Shader::ShaderProgram& shader_program) {
		m_postprocess_shader = &shader_program;
		m_postprocess_shader->bind();
		m_postprocess_shader->set_uniform(Constants::model_matrix, m_quad_model_matrix);
		m_postprocess_shader->unbind();
	}

	void RenderPassManager::set_active_registry(entt::registry& registry) {
		m_active_registry = &registry;
	}

} // namespace QuestEngine::Render