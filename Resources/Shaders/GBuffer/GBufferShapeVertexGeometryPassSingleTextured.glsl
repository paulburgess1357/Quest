#version 330 core
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

void main(){

    // Output variables (converted into eye space)
    vertex_position_eye = (view_matrix * model_matrix * vec4(vertex_position, 1.0)).xyz;
    vertex_normal_eye = normalize(normal_matrix * vertex_normal);
    frag_tex_coords = tex_coords;

    // Convert vertex position to clip space for fragment shader
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position, 1.0);
    
}