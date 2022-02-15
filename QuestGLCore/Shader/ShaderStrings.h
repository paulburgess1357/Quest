#pragma once
#include <string>

namespace QuestGLCore::Shader {

	class ShaderStrings {
	public:
		[[nodiscard]] static std::string get_vertex_post_process() {
			return "#version 330 core\n"
					"layout (location = 0) in vec2 position;\n"
					"layout (location = 1) in vec2 tex_coords;\n"

					"out vec2 frag_tex_coords;\n"

					"void main(){\n"
					"    frag_tex_coords = tex_coords;\n"
					"    gl_Position = vec4(position.x, position.y, 0.0, 1.0);\n"
					"}";
		}
		[[nodiscard]] static std::string get_fragment_post_process() {
			return "#version 330 core\n"
					"out vec4 frag_color;\n"

					"in vec2 frag_tex_coords;\n"

					"uniform sampler2D post_process_texture;\n"

					"void main(){\n"
					"    vec3 output_color = texture(post_process_texture, frag_tex_coords).rgb;\n"

					"	 // Gamma Correction \n"
					"    output_color = pow(output_color, vec3(1.0f/2.2f));\n"

					"    frag_color = vec4(output_color, 1.0);\n"
					"}";
		}
	};
}