#pragma once
#include "Framebuffer.h"
#include "QuestGLCore/Model/Mesh.h"
#include "QuestGLCore/Shader/ShaderProgram.h"
#include "QuestGLCore/VertexData/VertexDataElement.h"

namespace QuestGLCore::Framebuffer {

	template <template<GLenum> class FramebufferType, GLenum TextureType>
	class FramebufferPostProcess : public Framebuffer<FramebufferType, TextureType> {

	public:
		FramebufferPostProcess(const int width, const int height, const int color_attachment_num, Shader::ShaderProgram& shader_program)
			:Framebuffer<FramebufferType, TextureType>{ width, height, color_attachment_num },
			m_shader_program{ &shader_program }{
			init_shader();
			init_quad();
		}

		void draw() const {
			glDisable(GL_DEPTH_TEST);
			m_shader_program->bind();
			Framebuffer<FramebufferType, TextureType>::bind_scene_attachment();
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

			QuestGLCore::VertexData::IndexedVertexData vertex_data_element{ GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_TRIANGLES };
			vertex_data_element.load_data(vertices, indices, { 2, 2 });
			m_mesh = std::make_unique<Model::Mesh<VertexData::IndexedVertexData>>(std::move(vertex_data_element));
		}

		void init_shader() const {
			m_shader_program->bind();
			m_shader_program->set_uniform("post_process_texture", 0);
			m_shader_program->unbind();
		}

		Shader::ShaderProgram* m_shader_program;
		std::unique_ptr<Model::Mesh<VertexData::IndexedVertexData>> m_mesh;
	};


}