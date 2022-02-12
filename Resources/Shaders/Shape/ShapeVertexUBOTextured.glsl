#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tex_coords;

layout (std140) uniform ubo_matrices {
    mat4 view_projection;
};

uniform mat4 model_matrix;
out vec2 frag_tex_coords;

void main(){
    gl_Position = view_projection * model_matrix * vec4(aPos, 1.0f);
    frag_tex_coords = tex_coords;
}