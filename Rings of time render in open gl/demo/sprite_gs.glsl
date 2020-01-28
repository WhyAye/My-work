#version 330

uniform mat4 projection_xform;
uniform mat4 view_xform;

layout(points) in;
in float geometry_size[];
in vec4 geometry_rgba[];

layout(triangle_strip, max_vertices = 4) out;
out vec4 varying_colour;
out vec2 varying_texcoord;

void main()
{
    vec2 texcoords[] = vec2[](
        vec2(0, 0),
        vec2(1, 0),
        vec2(0, 1),
        vec2(1, 1));
    float s = 0.5 * geometry_size[0];
    vec2 offsets[] = vec2[](
        vec2(-s, -s),
        vec2(s, -s),
        vec2(-s, s),
        vec2(s, s));
    for (int i=0; i<4; ++i) {
        vec4 p = gl_in[0].gl_Position + vec4(offsets[i], 0, 0);
        gl_Position = projection_xform * p;
        varying_colour = geometry_rgba[0];
        varying_texcoord = texcoords[i];
        EmitVertex();
    }
}
