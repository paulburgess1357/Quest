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

uniform float linear;
uniform float quadratic;
uniform float pointlight_max_radius;

// =============== Output ==================
// Output to the default location (i.e. the windows framebuffer)
out vec4 frag_color; 

// ================== Main =================
void main(){      

    vec2 frag_tex_coords = gl_FragCoord.xy/textureSize(all_textures.position, 0);

    // Access data from G-Buffer textures
    // Note that its eye space because we did the eye space transformation in the 'GBufferShapeVertexGeometryPass' shader
    vec3 vertex_position_eye = texture(all_textures.position, frag_tex_coords).rgb;
    vec3 vertex_normal_eye = texture(all_textures.normals, frag_tex_coords).rgb;
    vec3 diffuse_color = texture(all_textures.color_spec, frag_tex_coords).rgb;
    float specular_amount = texture(all_textures.color_spec, frag_tex_coords).a;
    
    // Ambient (hard coded for now)
    vec3 lighting = diffuse_color * 0.1;

        // I THINK instead of this loop, I do this...:
        // Write your lighting spheres to their own texture attachment in the normal g-buffer shader (prior to this)
        // In this shader, get the texture for the above (e.g. call it pointlight texture)
        // Instead of the loop below, I combine the colors of the pointlight texture (which is just sphere volumes that are while) with the below, and somehow use the equation
        // I dont understnad how to sacle the spheres color.  Do i fade it out to black in its original texture render? Or do I somehow do that in this shader?

        // Perhaps I need the z buffer information here as well? Soo maybe its this:
        // 1) Write depth infomrtion to texture in g-buffer
        // 2) access that depth information in the lighting pass...
        // 3) Use that to determine how to render light volumes?
        // 4) if a light volume is rendered, figure out how the blending comes into play........... ???
        // 5) as part of 4, how do the equations below work>? No loop and the equation is based on distance to light source?

        // nooooooooooo

        // perhaps this
        // when drawing to lighting shader:
        // disable depth (i think)'
        // draw light spheres
        // this filters down the lighting shader to just pixels impacted by these spheres???

    for(int i = 0; i < LIGHT_QTY; ++i){

        // Convert light to eye space
        vec3 light_in_world_eye = vec3(view_matrix * vec4(all_lights[i].light_position, 1.0f));
        vec3 light_direction_from_surface_to_lightsource = normalize(light_in_world_eye - vertex_position_eye);

        // Calculate distance (used for attenuation calculation).  This is also used to NOT do lighting calculations for 
        // objects outside the light radius range:
        float distance_to_light = length(light_in_world_eye - vertex_position_eye);             

        //if(distance_to_light < pointlight_max_radius){
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
            float attenuation = 1.0 / (1.0 + linear * distance_to_light + quadratic * distance_to_light * distance_to_light);
            diffuse_lighting *= attenuation;
            specular_lighting *= attenuation;
        
            lighting += diffuse_lighting + specular_lighting;
        //}

    }
    
    // Gamma Correction
    // frag_color = vec4(pow(lighting, vec3(1.0f/2.2f)), 1.0);    
    frag_color = vec4(lighting, 1.0);

} 