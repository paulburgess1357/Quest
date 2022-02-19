#version 330 core
out vec4 frag_color;

in vec2 frag_tex_coords;

uniform sampler2D post_process_texture;

void main(){
    vec3 output_color = texture(post_process_texture, frag_tex_coords).rgb;
    // output_color = 1 - output_color;\n // inversion test

	 // Gamma Correction 
    output_color = pow(output_color, vec3(1.0f/2.2f));

    frag_color = vec4(output_color, 1.0);
};