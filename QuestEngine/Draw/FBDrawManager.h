#pragma once
#include "QuestEngine/Using/Window.h"
#include "QuestEngine/Using/Framebuffer.h"
#include "QuestEngine/ECS/Manage/SystemManager.h"
#include "QuestEngine/Using/Shader.h"

namespace QuestEngine::Draw {

	class FBDrawManager {
	public:
		FBDrawManager(const int width, const int height, const ECS::SystemManager& systems_manager);
		void draw() const;
		void set_pointlight_shader(Shader::ShaderProgram& shader_program);

	private:
		void deferred_pass() const;
		void light_pass() const;
		void forward_pass() const;
		void window_pass() const;

		const ECS::SystemManager& m_systems_manager;

		Framebuffer::FramebufferGBuffer2D m_g_buffer;
		Framebuffer::FramebufferPostProcessStandard2D m_post_process_framebuffer;

		Shader::ShaderProgram* m_pointlight_shader;
		Shader::ShaderProgram* m_postprocess_shader;

	};

} // namespace QuestEngine::Draw


