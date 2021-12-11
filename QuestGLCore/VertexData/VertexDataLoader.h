#pragma once
#include "VertexDataStruct.h"
#include <numeric>

namespace QuestGLCore::VertexData {

	class VertexDataLoader {

	public:

		// Specialized Functions: 
		static [[nodiscard]] VertexDataStruct<GL_ARRAY_BUFFER> load_float_data(const std::vector<float>& input_data, const std::vector<int>& vertex_description) {
			return load_data<float, GL_FLOAT, GL_ARRAY_BUFFER, GL_STATIC_DRAW>(input_data, vertex_description);
		}

		static [[nodiscard]] VertexDataElementStruct<GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER> load_float_data(const std::vector<float>& input_data, const std::vector<unsigned int>& indices,  const std::vector<int>& vertex_description) {
			return load_data<float, GL_FLOAT, GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW>(input_data, indices, vertex_description);
		}

	private:
		// Load data (no index)
		template<typename T, GLenum GLType, GLenum VBOTarget = GL_ARRAY_BUFFER, GLenum DrawType = GL_STATIC_DRAW>
		static VertexDataStruct<VBOTarget> load_data(const std::vector<T>& input_data, const std::vector<int>& vertex_description) {

			VertexDataStruct<VBOTarget> vertex_handles;
			vertex_handles.bind_data();

			// Store data
			glBufferData(VBOTarget, sizeof(T) * input_data.size(), input_data.data(), DrawType);

			// Describe attributes (for shader)
			const auto stride = static_cast<GLsizei>(std::accumulate(vertex_description.begin(), vertex_description.end(), 0) * sizeof(T));
			unsigned int offset = 0;

			for (int i = 0; i < vertex_description.size(); i++) {
				glVertexAttribPointer(i, vertex_description.at(i), GLType, GL_FALSE, stride,    (void*) (offset * sizeof(T))            );
				glEnableVertexAttribArray(i);
				offset += vertex_description.at(i);
			}

			vertex_handles.unbind_data();
			return vertex_handles;
		}

		// Load data (w/ element buffer index)
		template<typename T, GLenum GLType, GLenum VBOTarget = GL_ARRAY_BUFFER, GLenum EBOTarget = GL_ELEMENT_ARRAY_BUFFER, GLenum DrawType = GL_STATIC_DRAW>
		static VertexDataElementStruct<VBOTarget, EBOTarget> load_data(const std::vector<T>& input_data, const std::vector<unsigned int>& indices, const std::vector<int>& vertex_description) {

			VertexDataElementStruct<VBOTarget, EBOTarget> vertex_handles;
			vertex_handles.bind_data();

			// Store data
			glBufferData(VBOTarget, sizeof(T) * input_data.size(), input_data.data(), DrawType);

			// Store indices
			glBufferData(EBOTarget, sizeof(unsigned int) * indices.size(), indices.data(), DrawType);  // NOLINT(bugprone-narrowing-conversions)

			// Describe attributes (for shader)
			const auto stride = static_cast<GLsizei>(std::accumulate(vertex_description.begin(), vertex_description.end(), 0) * sizeof(T));
			unsigned int offset = 0;

			for (int i = 0; i < vertex_description.size(); i++) {
				glVertexAttribPointer(i, vertex_description.at(i), GLType, GL_FALSE, stride,   (void*) (offset * sizeof(T))      );
				glEnableVertexAttribArray(i);
				offset += vertex_description.at(i);
			}

			vertex_handles.unbind_data();
			return vertex_handles;
		}

	};

} // namespace QuestGLCore::VertexData