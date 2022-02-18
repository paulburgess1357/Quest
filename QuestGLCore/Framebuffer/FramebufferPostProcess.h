#pragma once
#include "Framebuffer.h"
#include "QuestGLCore/Model/Mesh.h"
#include "QuestGLCore/Shader/ShaderProgram.h"
#include "QuestGLCore/VertexData/VertexDataElement.h"
#include "QuestUtility/Include/Logger.h"
#include <initializer_list>

namespace QuestGLCore::Framebuffer {

	template <GLenum TextureType>
	class FramebufferPostProcess : public Framebuffer<TextureType> {

	public:
		FramebufferPostProcess(const int width, const int height, const std::initializer_list<Texture::BlankTextureEnum>& texture_types)
			:Framebuffer<TextureType>{ width, height, texture_types },
			m_shader_program{ nullptr }{
			init_quad();
		}
		virtual ~FramebufferPostProcess() = default;

		void set_shader_program(Shader::ShaderProgram& shader_program) {
			m_shader_program = &shader_program;
			init_shader_uniforms();
		}

		virtual void init_shader_uniforms() const = 0;

	protected:
		void init_quad() {
			const std::vector<unsigned int> indices = {
				0, 1, 3,
				1, 2, 3
			};

			const std::vector<float> vertices = {
				// positions   // tex_coords
				-1.0f,  1.0f,  0.0f, 1.0f,
				-1.0f, -1.0f,  0.0f, 0.0f,
				 1.0f, -1.0f,  1.0f, 0.0f,
				 1.0f,  1.0f,  1.0f, 1.0f
			};

			VertexData::IndexedVertexData vertex_data_element{ GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_TRIANGLES };
			vertex_data_element.load_data(vertices, indices, { 2, 2 });
			m_mesh = std::make_unique<Model::Mesh<VertexData::IndexedVertexData>>(std::move(vertex_data_element));
		}

		Shader::ShaderProgram* m_shader_program;
		std::unique_ptr<Model::Mesh<VertexData::IndexedVertexData>> m_mesh;
	};


	template <GLenum TextureType>
	class FramebufferPostProcessStandard final : public FramebufferPostProcess<TextureType> {
	public:
		FramebufferPostProcessStandard(const int width, const int height, const std::initializer_list<Texture::BlankTextureEnum>& texture_types)
			:FramebufferPostProcess<TextureType>(width, height, texture_types){
			this->attachment_num_check(1, "The standard post processing framebuffer can only have a single texture attachment! If more are desired, create a specilized class or update the existing stand post-processing framebuffer!  This framebuffer is primarily meant for something like gamma correction or hdr.");
		}

		void render_to_quad() const {
			//glDisable(GL_DEPTH_TEST);
			this->m_shader_program->bind();

			// First color attachment should be all draw data
			// ColorAttachment0, Tex Unit 0
			this->bind_color_attachment(0, 0);

			this->m_mesh->draw();
			//glEnable(GL_DEPTH_TEST);
		}

		void draw_quad() const {
			this->m_mesh->draw();
		}
	private:
		void init_shader_uniforms() const override {
			this->m_shader_program->bind();
			this->m_shader_program->set_uniform("post_process_texture", 0);
			this->m_shader_program->unbind();
		}
	};

	template<GLenum TextureType>
	class FramebufferGBuffer final : public FramebufferPostProcess<TextureType> {
	public:

		// If adding more textures to the g-buffer:
		// 1) Update the geometry pass fragment shader (i.e. the 'layout (location = 2) out vec4 g_colors_spec;' additions
		// 2) Update the light pass shader to accept the newly bound texture type (Textures struct)
		// 3) Update the 'init_shader_uniforms' below to set the new tex unit uniform
		// 4) Update the 'attachment_num_check' function
		// 5) Update the g-buffer variable instantiation in Engine.cpp to have the new texture type in its initializer list

		FramebufferGBuffer(const int width, const int height, const std::initializer_list<Texture::BlankTextureEnum>& texture_types)
			:FramebufferPostProcess<TextureType>(width, height, texture_types) {
			set_clear_color();
			this->attachment_num_check(3, "The expected quantity of color attachments for this G-Buffer is 3! If you don't need 3, please update or specialize the class: FramebufferGBuffer.  Note that 'init_shader_uniforms' will have to be updated to accomodate more textures!  Remember to update both the geometry pass fragment shader AND the light pass fragment shader");
		}

		void draw_lighting_pass_to_quad() const {
			glDisable(GL_DEPTH_TEST); // TODO ==================================== Correct??
			this->m_shader_program->bind();
			// Bind all color attachments
			this->bind_all_color_attachments();
			this->m_mesh->draw();
			glEnable(GL_DEPTH_TEST); // TODO ==================================== Correct??
		}

		void draw_lighting_pass_to_pointlights_start() const {

			// pointlight light shader program...
			this->m_shader_program->bind();

			glDisable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendEquation(GL_FUNC_ADD);
			glBlendFunc(GL_ONE, GL_ONE);
		}

		void draw_lighting_pass_to_pointlights_end() const {
			glEnable(GL_DEPTH_TEST);
		}

		void bind_shader_program_TEMP_PUBLIC() const {
			this->m_shader_program->bind();
		}

	private:
		void init_shader_uniforms() const override {
			this->m_shader_program->bind();
			this->m_shader_program->set_uniform("all_textures.position", 0);
			this->m_shader_program->set_uniform("all_textures.normals", 1);
			this->m_shader_program->set_uniform("all_textures.color_spec", 2);
			this->m_shader_program->unbind();
		}

		static void set_clear_color() {
			// Black clear color to prevent leaking into G-Buffer
			glClearColor(0.00f, 0.00f, 0.00f, 1.0f);
		}
	};

}