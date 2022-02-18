#include "pch.h"
#include "FBDrawManager.h"
#include "QuestEngine/Using/LightState.h"

namespace QuestEngine::Draw {

	FBDrawManager::FBDrawManager(const int width, const int height, const ECS::SystemManager& systems_manager)
		:m_systems_manager{ systems_manager },
		m_g_buffer{ width, height, { Texture::BlankTextureEnum::RGBA16F_NEAREST, Texture::BlankTextureEnum::RGBA16F_NEAREST, Texture::BlankTextureEnum::RGBA_NEAREST } },
		m_post_process_framebuffer{ width, height, { Texture::BlankTextureEnum::RGBA_LINEAR } },
		m_pointlight_shader{ nullptr },
		m_postprocess_shader{ nullptr }{
	}

	void FBDrawManager::draw() const {
		deferred_pass();
		light_pass();
		forward_pass();
		window_pass();
	}

	void FBDrawManager::deferred_pass() const {
		// Draw geometry/textures/normals to G-Buffer attachments
		m_g_buffer.bind();//                                                              														   
		Framebuffer::Framebuffer2D::clear_buffer_no_bind();
		m_systems_manager.draw_deferred(); //      
	}

	void FBDrawManager::light_pass() const {
		// Render G-Buffer attachments onto pointlight volume spheres to post-process framebuffer
		m_post_process_framebuffer.bind();
		Framebuffer::Framebuffer2D::clear_buffer_no_bind();

		QuestEngine::State::LightState::light_pass_start();
		m_pointlight_shader->bind();
		m_g_buffer.bind_all_color_attachments();
		m_systems_manager.draw_pointlight();
		QuestEngine::State::LightState::light_pass_end();
	}

	void FBDrawManager::forward_pass() const {
		// Copy depth information from g-buffer to post process framebuffer
		// Draw forward rendered objects to post-process framebuffer
		// i.e. This allows us to draw forward rendered objects within the
		// scene (rather than on top)


		// m_g_buffer.blit_depth_to_existing_fb(m_post_process_framebuffer, m_window_width, m_window_height, m_window_width, m_window_height);


		// Fully bind post-process framebuffer (blit does a read bind
		// from g-buffer and a write bind to post-process buffer)
		m_post_process_framebuffer.bind(); // 
		m_systems_manager.draw_forward(); // 
	}

	void FBDrawManager::window_pass() const {
		// Draw post-process framebuffer to window
		m_post_process_framebuffer.unbind();



		// m_window.clear_buffer();



		m_post_process_framebuffer.render_to_quad(); //TODO i think its possible to drop the depth disable by setting the z component in the vertex shader to zero.
	}


	void FBDrawManager::set_pointlight_shader(Shader::ShaderProgram& shader_program) {
		m_pointlight_shader = &shader_program;
	}


} // namespace QuestEngine::Draw
