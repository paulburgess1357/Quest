#version 330 core
layout (location = 0) out vec4 scene_colors;
// Fragment Shader
// Textured Cube
// One diffuse texture and one specular texture

// ======== Structure Definitions =========
struct LightInfo {
    vec4 light_in_world;
    vec4 ambient_intensity;
    vec4 diffuse_intensity;
    vec4 specular_intensity;
    float shininess;
};

struct Textures {
    sampler2D diffuse;
    sampler2D specular;
};

// ======= Input from Vertex Shader ========
in vec3 vertex_position_eye;
in vec3 vertex_normal_eye;
in vec2 frag_tex_coords;

// ============ Global Uniforms ============
layout (std140) uniform ubo_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

// ============ Shader Uniforms ============
// Lights
uniform LightInfo light_info;

// Texture
uniform Textures all_textures;

// =============== Output ==================
out vec4 fragment_color;

// ========= Function Prototypes ==========
vec4 phong_lighting(vec3 vertex_position_eye_space, vec3 vertex_normal_eye_space);


// ================== Main =================
void main() {	
    scene_colors = phong_lighting(vertex_position_eye, vertex_normal_eye);	
}

vec4 get_specular_light(float light_dir_to_normals_dot, vec3 light_direction_from_surface_to_lightsource, vec3 vertex_position_eye_space, vec3 vertex_normal_eye_space){
    
    vec4 specular_light = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    
    // When light_dir_to_normals_dot is greater than 0, it means we have some lighting in effect from our lightsource to our object.
    if(light_dir_to_normals_dot > 0.01f){
        vec3 vector_towards_viewer = normalize(-vertex_position_eye_space.xyz);
        vec3 halfway_vector_btwn_lightsource_and_viewer = normalize(vector_towards_viewer + light_direction_from_surface_to_lightsource);              
        specular_light = light_info.specular_intensity * pow(max(dot(halfway_vector_btwn_lightsource_and_viewer, vertex_normal_eye_space), 0.0f), light_info.shininess);
        specular_light = specular_light * texture(all_textures.specular, frag_tex_coords);
    }

    return specular_light;

}

// ========= Function Definitions ===========
vec3 get_light_direction(vec3 vertex_position_eye_space_space){
    
    // Convert light to eye space
    vec3 light_in_world_eye = vec3(view_matrix * light_info.light_in_world);

    // Determine if light_position_in_world is a positional light or directional light
    vec3 light_direction_from_surface_to_lightsource = vec3(0.0f);
    if(light_info.light_in_world.w == 0.0f){
        // Directional light from object to lightsource
        light_direction_from_surface_to_lightsource = normalize(light_in_world_eye);
    } else {
        // Positional light
        // Convert light position to eye space & get direction
        light_direction_from_surface_to_lightsource = normalize(light_in_world_eye - vertex_position_eye_space_space);
    }

    return light_direction_from_surface_to_lightsource;

}

vec4 get_ambient_light(){
    return light_info.ambient_intensity * texture(all_textures.diffuse, frag_tex_coords);
}

vec4 get_diffuse_light(float light_dir_to_normals_dot){
    return light_info.diffuse_intensity * light_dir_to_normals_dot * texture(all_textures.diffuse, frag_tex_coords);
}

vec4 phong_lighting(vec3 vertex_position_eye_space, vec3 vertex_normal_eye_space){
    
    // Even though vertex_normal_eye is normalized in the vertex shader,
    // the interpolation process can create vectors that are not of unit length
    // As such, we must normalize the vertex_normal_eye once more.
    vec3 vertex_normal_eye_space_normalized = normalize(vertex_normal_eye_space);
    
    // Calculate light direction
    vec3 light_direction_from_surface_to_lightsource = get_light_direction(vertex_position_eye_space);

    // Lighting Calculations
    // The value here gives us a scalar for how strong our light is (if light_dir and vertex_normals were at 90 degrees, the result would be zero): pg 80
    float light_dir_to_normals_dot = max(dot(light_direction_from_surface_to_lightsource, vertex_normal_eye_space_normalized), 0.0f);

    // Ambient
    vec4 ambient_light = get_ambient_light();

    // Diffuse
    vec4 diffuse_light = get_diffuse_light(light_dir_to_normals_dot);

    // Specular
    vec4 specular_light = get_specular_light(light_dir_to_normals_dot, light_direction_from_surface_to_lightsource, vertex_position_eye_space, vertex_normal_eye_space_normalized);

    // Combine lights
    return ambient_light + diffuse_light + specular_light;
}