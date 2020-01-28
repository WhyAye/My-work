#version 330

uniform mat4 projection_xform;
uniform mat4 view_xform;

in vec3 sprite_position;
in float sprite_size;
in vec3 sprite_colour;
in float sprite_alpha;
in float sprite_rotation;

out float geometry_size;
out vec4 geometry_rgba;

void main(void)
{
    geometry_size = sprite_size;
    geometry_rgba = vec4(sprite_colour, sprite_alpha);
    gl_Position = view_xform * vec4(sprite_position, 1.0);
}
