#pragma once
#include "QuestGLCore/Handle/Template/HandleTemplate.h"
#include "QuestGLCore/Handle/Traits/Vao.h"
#include "QuestGLCore/Handle/Traits/Buffer.h"

namespace QuestGLCore::VertexData {

	template<GLenum VBOTarget>
	struct VertexDataStruct {

		void bind(const bool render = false) const {
			m_vao.bind();
		}

		void unbind(const bool render = false) const {
			m_vao.unbind();
		}

		void bind_data() const {
			bind();
			m_vbo.bind();
		}

		void unbind_data() const {
			unbind();
			m_vbo.unbind();
		}

		Handle::HandleTemplate<Traits::VAOTraits, Typedefs::HandleTypedef> m_vao;
		Handle::HandleTemplate<Traits::BufferTraits<VBOTarget>, Typedefs::HandleTypedef> m_vbo;
	};

	template<GLenum VBOTarget, GLenum EBOTarget>
	struct VertexDataElementStruct {

		void bind() const {
			m_vao_vbo.bind();
		}

		void unbind() const {
			m_vao_vbo.unbind();
		}

		void bind_data() const {
			m_vao_vbo.bind_data();
			m_ebo.bind();
		}

		void unbind_data() const {
			m_vao_vbo.unbind_data();
			m_ebo.unbind();
		}

		VertexDataStruct<VBOTarget> m_vao_vbo;
		Handle::HandleTemplate<Traits::BufferTraits<EBOTarget>, Typedefs::HandleTypedef> m_ebo;
		Typedefs::SizeTypedef m_index_count{ 0 };
	};

} // namespace QuestGLCore::VertexData


