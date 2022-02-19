#version 330 core
//NOTE: This isn't using the g-buffer!!
layout (location = 0) out vec4 scene_colors;

in vec2 frag_tex_coords;

// texture samplers
uniform sampler2D shape_texture_test;

void main(){
    scene_colors = texture(shape_texture_test, frag_tex_coords);
} 