#version 330

uniform mat4 projection_view_model_xform;
uniform mat4 view_xform;
uniform mat4x3 model_xform;

in vec3 vertex_position;
in vec3 vertex_normal;
in vec3 vertex_tangent;
in vec2 vertex_texcoord;

out vec3 view_normal;
out vec3 view_position;
out vec2 texcoord;

void main(void) {
	vec3 world_normal = mat3(model_xform) * normalize(vertex_normal);
	view_normal = mat3(view_xform) * world_normal;
	vec3 world_position = model_xform * vec4(vertex_position, 1.0);
	view_position = vec3(view_xform * vec4(world_position, 1.0));
    texcoord = vertex_texcoord;
    gl_Position = projection_view_model_xform * vec4(vertex_position, 1.0);
}
