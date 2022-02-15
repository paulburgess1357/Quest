#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 tex_coords;

layout (std140) uniform uniform_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

uniform mat4 model_matrix;
out vec2 frag_tex_coords;

void main(){
    gl_Position = projection_matrix * view_matrix* model_matrix * vec4(aPos, 1.0f);
    frag_tex_coords = tex_coords;
}