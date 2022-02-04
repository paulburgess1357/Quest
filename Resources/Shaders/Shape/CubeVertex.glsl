#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}