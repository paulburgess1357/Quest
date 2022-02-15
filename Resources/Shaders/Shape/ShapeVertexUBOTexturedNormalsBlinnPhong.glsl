#version 330 core
// Vertex Shader
// Directional Light
// OGL4 Shader Language Cookbook Pg. 118
// Pg. 86 for general light diagram
// Shading calculations done in fragment shader

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 tex_coords;

// ============ Global Uniforms ============
layout (std140) uniform ubo_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

// ============ Shader Uniforms ============
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

// =============== Output ==================
out vec3 vertex_position_eye;
out vec3 vertex_normal_eye;
out vec2 frag_tex_coords;

// ========= Function Prototypes ==========
// *** Pay close attention to out variables! ***
void convert_norm_pos_to_eye_space(out vec3 out_vertex_position, out vec3 out_vertex_normal);


// ================== Main =================
void main(){	

    // Convert cube normals and cube position to view space (eye/camera space)
    // Note that the model matrix has already been multiplied by the view matrix by the time its sent to the shader (for normal matrix calculation)
    convert_norm_pos_to_eye_space(vertex_position_eye, vertex_normal_eye);
    
    // Output texture coordinates (No change)
    frag_tex_coords = tex_coords;
   
    // Convert vertex position to clip space for fragment shader
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position, 1.0);
}


// ========= Function Definitions ===========
void convert_norm_pos_to_eye_space(out vec3 out_vertex_position, out vec3 out_vertex_normal){  
    out_vertex_position = (view_matrix * model_matrix * vec4(vertex_position, 1.0)).xyz;
    out_vertex_normal = normalize(normal_matrix * vertex_normal);
}