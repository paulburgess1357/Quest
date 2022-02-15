#pragma once
#include "Framebuffer.h"
#include "QuestGLCore/Model/Mesh.h"
#include "QuestGLCore/Shader/ShaderProgram.h"
#include "QuestGLCore/VertexData/VertexDataElement.h"
#include <initializer_list>

namespace QuestGLCore::Framebuffer {

	template <GLenum TextureType>
	class FramebufferPostProcess : public Framebuffer<TextureType> {

	public:
		FramebufferPostProcess(const int width, const int height, const std::initializer_list<Texture::BlankTextureEnum>& texture_types, Shader::ShaderProgram& shader_program)
			:Framebuffer<TextureType>{ width, height, texture_types },
			m_shader_program{ &shader_program }{
			init_shader_uniforms();
			init_quad();
		}

		void draw() const {
			glDisable(GL_DEPTH_TEST);
			m_shader_program->bind();
			// First color attachment should be all draw data
			this->bind_color_attachment(0, 0);
			m_mesh->draw();
			glEnable(GL_DEPTH_TEST);
		}

	private:
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

		void init_shader_uniforms() const {
			m_shader_program->bind();
			m_shader_program->set_uniform("post_process_texture", 0);
			m_shader_program->unbind();
		}

		Shader::ShaderProgram* m_shader_program;
		std::unique_ptr<Model::Mesh<VertexData::IndexedVertexData>> m_mesh;
	};


}