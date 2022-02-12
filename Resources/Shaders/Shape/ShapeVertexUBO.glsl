#version 330 core
layout (location = 0) in vec3 aPos;

layout (std140) uniform ubo_matrices {
    mat4 view_projection;
};

uniform mat4 model_matrix;

void main(){
    gl_Position = view_projection * model_matrix * vec4(aPos, 1.0f);
}