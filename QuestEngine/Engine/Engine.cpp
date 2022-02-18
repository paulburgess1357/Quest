#include "pch.h"
#include "Engine.h"
#include "QuestUtility/Include/Logger.h"
#include "QuestEngine/Constants/Constants.h"
#include "QuestEngine/Using/Texture.h"

namespace QuestEngine::Engine {

	Engine::Engine(const int width, const int height)
		:m_window{ width, height },
		m_active_camera{ nullptr },
		m_projection_matrix { Window::Window::get_width(), Window::Window::get_height() },
		m_systems_manager{ m_registry_manager.get_active_registry() },
		m_ubo_manager{ m_resource_manager.get_ubo(Constants::ubo_matrices) },
		m_user_interface{ m_window.get_window() },
		m_g_buffer{ width, height, { Texture::BlankTextureEnum::RGBA16F_NEAREST, Texture::BlankTextureEnum::RGBA16F_NEAREST, Texture::BlankTextureEnum::RGBA_NEAREST }},
		m_post_process_framebuffer{ width, height, { Texture::BlankTextureEnum::RGBA_LINEAR }},
		m_window_width{ Window::Window::get_width() },
		m_window_height{ Window::Window::get_height() }{
		QUEST_INFO("Quest Engine v{}.{} Initialized\n", 0, 1)
	}

	void Engine::run() {
		initialization();
		qc_checks();
		gameloop();
	}

	void Engine::initialization() {
		m_g_buffer.set_shader_program(m_resource_manager.get_shader(QuestEngine::Constants::g_buffer_light_pass)); // "g_buffer_light_pass"
		m_post_process_framebuffer.set_shader_program(m_resource_manager.get_shader(Constants::post_process_shader)); // "post_process_shader"
		set_active_camera(Constants::main_camera);
	}

	void Engine::set_active_camera(const std::string& camera_id) {
		if (auto* camera = m_resource_manager.get_camera_pointer(camera_id)) {
			m_active_camera = camera;
		}
	}

	void Engine::qc_checks() const {
		m_resource_manager.shader_qc();
	}

	void Engine::gameloop() {
		while (!shutdown()){
			m_ubo_manager.set_ubos(*m_active_camera, m_projection_matrix);
			m_systems_manager.update(*m_active_camera);

			handle_window_resize();
			draw_scene();
			// draw_user_interface();
			Window::Window::poll_events();

			m_window.swap_buffer();
		}
	}

	void Engine::handle_window_resize() {
		if (Window::Window::get_width() != m_window_width || Window::Window::get_height() != m_window_height) {
			m_window_width = Window::Window::get_width();
			m_window_height = Window::Window::get_height();
			m_post_process_framebuffer.rescale_attachments(m_window_width, m_window_height);
			m_g_buffer.rescale_attachments(m_window_width, m_window_height);
			m_projection_matrix.update_projection_matrix(m_window_width, m_window_height);
		}
	}

	void Engine::draw_scene() const {


		// --------------------------------------------------------------------------------------
		// ====== Deferred drawing pass ======                                                  |
		// - Store scene in geometry buffer (positions, normals, textures, etc.)                |      
		m_g_buffer.bind();//                                                                    | ----> Draw geometry/textures/normals to G-Buffer attachments 															   
		Framebuffer::Framebuffer2D::clear_buffer_no_bind(); //                                  |                           
		m_systems_manager.draw_deferred(); //                                                   |
		// --------------------------------------------------------------------------------------


		// --------------------------------------------------------------------------------------
		// ======= Lighting drawing pass ======                                                 |
		// - Take g-buffer stored data and draw lighting to post-process framebuffer            |
		m_post_process_framebuffer.bind(); //                                                   | ----> Render G-Buffer attachments onto pointlight volume spheres to post-process framebuffer
		Framebuffer::Framebuffer2D::clear_buffer_no_bind();
		//                                                                                      |
		// m_lighting_manager.init_light_pass_settings() // ogl functions                       |
		// m_lighting_manager.bind_pointlight_shader() // G-Buffer light pass                   |
		// m_lighting_manager.bind_all_fb_attachments(m_gbuffer)                                |
		// m_systems_manager.draw_pointlights();                                                |
		// m_lighting_manager.end_light_pass_settings()                                         |

		// PB Testing Changes ======================================================  
		// This is being drawn to the post-process framebuffer quad (shown above).
		m_g_buffer.draw_lighting_pass_to_pointlights_start();
		m_g_buffer.bind_all_color_attachments();
		m_systems_manager.draw_pointlight();

		// m_g_buffer.bind_shader_program_TEMP_PUBLIC();
		// bind shader program


		 // pointlights need to be updated to use correct shader....

		m_g_buffer.draw_lighting_pass_to_pointlights_end();
		// ==========================================================================

		// --------------------------------------------------------------------------------------

		
		// ---------------------------------------------------------------------------------------------------------------------------------------
		// Transfer g-buffer depth from 'm_g_buffer' to 'm_post_process_framebuffer'                                                              | 
		m_g_buffer.blit_depth_to_existing_fb(m_post_process_framebuffer, m_window_width, m_window_height, m_window_width, m_window_height); //    |
		//                                                                                                                                        |
		// ======== Forward drawing pass =======                                                                                                  | -----> Apply any forward rendering to post-process framebuffer
		// Fully bind post-process framebuffer                                                                                                    |
		m_post_process_framebuffer.bind(); //                                                                                                     |
		m_systems_manager.draw_forward(); //                                                                                                      | 
		// ---------------------------------------------------------------------------------------------------------------------------------------


		// ---------------------------------------------------------------------------------------------------------------------------------------
		// ============ Post-Process ===========                                                                                                 |
		// Draw post-process framebuffer to window                                                                                               |
		m_post_process_framebuffer.unbind(); //                                                                                                  | ----> Apply any post processing effects (gamma, hdr, bloom, etc.)
		m_window.clear_buffer(); //                                                                                                              |
		m_post_process_framebuffer.draw(); //                                                                                                    |
		// ---------------------------------------------------------------------------------------------------------------------------------------
	}

	void Engine::draw_user_interface() const {
		UserInterface::UserInterface::begin_render();
		UserInterface::UserInterface::show_demo();
		m_user_interface.end_render();
	}

	bool Engine::shutdown() const {
		return m_window.close_window() || Window::KeyboardInput::is_pressed(Window::Keyboard::ESCAPE);
	}

	Resource::ResourceManager& Engine::get_resource_manager() {
		return m_resource_manager;
	}

	ECS::RegistryManager& Engine::get_registry_manager() {
		return m_registry_manager;
	}

} // namespace QuestEngine::Engine