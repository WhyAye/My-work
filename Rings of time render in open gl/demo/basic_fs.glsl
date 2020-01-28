#version 330

uniform vec3 material_colour;
uniform sampler2D sampler_colour;
uniform bool use_texture;

in vec3 view_normal;
in vec3 view_position;
in vec2 texcoord;

out vec4 fragment_colour;

void main(void) {
	vec3 N = normalize(view_normal);
	vec3 V = -normalize(view_position);
	vec3 I = vec3(clamp(dot(V,N), 0.0, 1.0));
    vec3 colour = material_colour;
    if (use_texture) {
        colour *= texture(sampler_colour, texcoord).rgb;
    }
    fragment_colour = vec4(colour * I, 1.0);
}
