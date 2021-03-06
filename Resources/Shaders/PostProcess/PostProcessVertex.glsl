#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 tex_coords;

out vec2 frag_tex_coords;
uniform mat4 model_matrix; // used for aspect ratio resize

void main(){
    frag_tex_coords = tex_coords;
    gl_Position = model_matrix * vec4(position.x, position.y, 0.0, 1.0);
}