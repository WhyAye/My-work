#version 330

uniform sampler2D sampler_colour;
uniform bool use_texture;

in vec4 varying_colour;
in vec2 varying_texcoord;

out vec4 fragment_colour;

void main(void)
{
    vec4 col = varying_colour;
    if (use_texture) {
        col *= texture(sampler_colour, varying_texcoord);
    }
    
    fragment_colour = col;
}
