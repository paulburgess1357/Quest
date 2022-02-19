#version 330 core
//  Output into G-buffer color attachments
layout (location = 0) out vec3 g_position;
layout (location = 1) out vec3 g_normals;
layout (location = 2) out vec4 g_colors_spec;

// ======== Structure Definitions =========
struct Textures {
    sampler2D diffuse;
    sampler2D specular;
};

// ======= Input from Vertex Shader ========
in vec3 vertex_position_eye;
in vec3 vertex_normal_eye;
in vec2 frag_tex_coords;

// ====== Texture Uniforms =====
// These are NOT the g-buffer attachments.  This is the objects texture values
// E.g. Wood texture and specular metal outside border.  
uniform Textures all_textures;

void main(){
    // Store fragment position in ColorAttachment0
    g_position = vertex_position_eye;

    // Store vertex normals in ColorAttachment1
    g_normals = normalize(vertex_normal_eye);

    // Store the diffuse texture colors in ColorAttachment2
    g_colors_spec.rgb = texture(all_textures.diffuse, frag_tex_coords).rgb;

    // Store specular intensity in the alpha component of ColorAttachment2
    g_colors_spec.a = texture(all_textures.specular, frag_tex_coords).r;
} 