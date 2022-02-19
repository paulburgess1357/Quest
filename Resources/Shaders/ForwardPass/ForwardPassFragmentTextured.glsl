#version 330 core
layout (location = 0) out vec4 scene_colors;
struct Textures {
    sampler2D diffuse;
};

in vec2 frag_tex_coords;

// texture samplers
uniform Textures all_textures;

void main(){
    scene_colors = texture(all_textures.diffuse, frag_tex_coords);
} 