#version 330 core
// Lighting Pass Fragment Shader

// ======== Structure Definitions =========
// G-Buffer color attachments:
// See FramebufferGBuffer class if adding more textures
struct Textures {
    sampler2D position;
    sampler2D normals;
    sampler2D color_spec;
};

struct Light {
    vec3 light_position;
    vec3 color;
};

const int LIGHT_QTY = 64;
const float CONSTANT = 1.0f; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
const float LINEAR = 0.7f;
const float QUADRATIC = 1.8f;

// ============ Global Uniforms ============
layout (std140) uniform ubo_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

// ======= Input from Vertex Shader ========
in vec2 frag_tex_coords;

// ============ Shader Uniforms ============
// G-Buffer color attachments:
uniform Textures all_textures;
uniform Light all_lights[LIGHT_QTY];

// =============== Output ==================
// Output to the default location (i.e. the windows framebuffer)
out vec4 frag_color; 

// ================== Main =================
void main(){             
    // Access data from G-Buffer textures
    // Note that its eye space because we did the eye space transformation in the 'GBufferShapeVertexGeometryPass' shader
    vec3 vertex_position_eye = texture(all_textures.position, frag_tex_coords).rgb;
    vec3 vertex_normal_eye = texture(all_textures.normals, frag_tex_coords).rgb;
    vec3 diffuse_color = texture(all_textures.color_spec, frag_tex_coords).rgb;
    float specular_amount = texture(all_textures.color_spec, frag_tex_coords).a;
    
    // Ambient (hard coded for now)
    vec3 lighting = diffuse_color * 0.1;

    for(int i = 0; i < LIGHT_QTY; ++i){

        // Convert light to eye space
        vec3 light_in_world_eye = vec3(view_matrix * vec4(all_lights[i].light_position, 1.0f));
        vec3 light_direction_from_surface_to_lightsource = normalize(light_in_world_eye - vertex_position_eye);

        // The value here gives us a scalar for how strong our light is (if light_dir and vertex_normals were at 90 degrees, the result would be zero): pg 80
        float light_dir_to_normals_dot = max(dot(light_direction_from_surface_to_lightsource, vertex_normal_eye), 0.0f);

        // Diffuse
        vec3 diffuse_lighting = light_dir_to_normals_dot * diffuse_color * all_lights[i].color;
        
        // Specular
        vec3 vector_towards_viewer = normalize(-vertex_position_eye.xyz);
        vec3 halfway_vector_btwn_lightsource_and_viewer = normalize(vector_towards_viewer + light_direction_from_surface_to_lightsource);          
        float specular_amt = pow(max(dot(halfway_vector_btwn_lightsource_and_viewer, vertex_normal_eye), 0.0f), 16.0f);
        vec3 specular_lighting = all_lights[i].color * specular_amt * specular_amount;

        // attenuation
        float distance_to_light = length(light_in_world_eye - vertex_position_eye);

        float attenuation = 1.0 / (1.0 + LINEAR * distance_to_light + QUADRATIC * distance_to_light * distance_to_light);
        diffuse_lighting *= attenuation;
        specular_lighting *= attenuation;
        
        lighting += diffuse_lighting + specular_lighting;
    }
    
    // Gamma Correction
    frag_color = vec4(pow(lighting, vec3(1.0f/2.2f)), 1.0);    
    // frag_color = vec4(lighting, 1.0);

} 