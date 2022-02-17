#version 330 core
//  Output into G-buffer color attachments
layout (location = 0) out vec3 g_position;
layout (location = 1) out vec3 g_normals;
layout (location = 2) out vec4 g_colors_spec;

// ======= Input from Vertex Shader ========
in vec3 vertex_position_eye;
in vec3 vertex_normal_eye;
in vec2 frag_tex_coords;

void main(){
    // Store fragment position in ColorAttachment0
    g_position = vertex_position_eye;

    // Store vertex normals in ColorAttachment1
    g_normals = normalize(vertex_normal_eye);

    // Solution White Color
    g_colors_spec.rgba = vec4(1.0f, 1.0f, 1.0f, 1.0f);
} 