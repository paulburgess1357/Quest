#version 330 core
layout (location = 0) out vec4 scene_colors;

in vec2 frag_tex_coords;

// texture samplers
uniform sampler2D rainbow_texture;

void main(){
    scene_colors = texture(rainbow_texture, frag_tex_coords);
} 