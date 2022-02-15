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
		FramebufferPostProcess(const int width, const int height, const std::initializer_list<Texture::BlankTextureEnum>& texture_types, Shader::ShaderProgram& shader_program)
			:Framebuffer<TextureType>{ width, height, texture_types },
			m_shader_program{ &shader_program }{
			init_quad();
		}

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
	class FramebufferPostProcessStandard : public FramebufferPostProcess<TextureType> {
	public:
		FramebufferPostProcessStandard(const int width, const int height, const std::initializer_list<Texture::BlankTextureEnum>& texture_types, Shader::ShaderProgram& shader_program)
			:FramebufferPostProcess<TextureType>(width, height, texture_types, shader_program){
			init_shader_uniforms();
			this->attachment_num_check(1, "The standard post processing framebuffer can only have a single texture attachment! If more are desired, create a specilized class or update the existing stand post-processing framebuffer!  This framebuffer is primarily meant for something like gamma correction or hdr.");
		}

		void draw() const {
			glDisable(GL_DEPTH_TEST);
			this->m_shader_program->bind();

			// First color attachment should be all draw data
			// ColorAttachment0, Tex Unit 0
			this->bind_color_attachment(0, 0);

			this->m_mesh->draw();
			glEnable(GL_DEPTH_TEST);
		}
	private:
		void init_shader_uniforms() const {
			this->m_shader_program->bind();
			this->m_shader_program->set_uniform("post_process_texture", 0);
			this->m_shader_program->unbind();
		}
	};

	template<GLenum TextureType>
	class FramebufferGBuffer : public FramebufferPostProcess<TextureType> {
	public:
		FramebufferGBuffer(const int width, const int height, const std::initializer_list<Texture::BlankTextureEnum>& texture_types, Shader::ShaderProgram& shader_program)
			:FramebufferPostProcess<TextureType>(width, height, texture_types, shader_program) {
			init_shader_uniforms();
			set_clear_color();
			this->attachment_num_check(3, "The expected quantity of color attachments for this G-Buffer is 3! If you don't need 3, please update or specialize the class: FramebufferGBuffer.  Note that 'init_shader_uniforms' will have to be updated to accomodate more textures!");
		}

		void draw() const {
			glDisable(GL_DEPTH_TEST); // TODO ==================================== Correct??
			this->m_shader_program->bind();
			// Bind all color attachments
			this->bind_all_color_attachments();
			this->m_mesh->draw();
			glEnable(GL_DEPTH_TEST); // TODO ==================================== Correct??
		}

	private:
		void init_shader_uniforms() const {
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