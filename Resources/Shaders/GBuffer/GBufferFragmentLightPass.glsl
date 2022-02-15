#version 330 core
layout (location = 0) out vec4 scene_colors;

// Lighting Pass Fragment Shader

struct Textures {
    // Update FramebufferGBuffer if adding more textures
    sampler2D position;
    sampler2D normals;
    sampler2D color_and_specular;
};