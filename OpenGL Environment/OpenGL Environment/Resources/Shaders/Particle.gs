#version 450 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout (location = 3) uniform mat4 mvp;
layout (location = 4) uniform mat4 vp;
layout (location = 5) uniform vec3 cameraRight;
layout (location = 6) uniform vec3 cameraUp;

out GS_FS_VERTEX{
	vec2 texCoord;
} gs_out;

void main(){
	float size = 0.3f;
	vec3 p1 = gl_in[0].gl_Position.xyz + (-cameraRight - cameraUp) * size;
	gl_Position = vp * vec4(p1, 1.0f);
	gs_out.texCoord = vec2(0.0f, 1.0f); EmitVertex();

	vec3 p2 = gl_in[0].gl_Position.xyz + (-cameraRight + cameraUp) * size;
	gl_Position = vp * vec4(p2, 1.0f);
	gs_out.texCoord = vec2(0.0f, 0.0f); EmitVertex();

	vec3 p3 = gl_in[0].gl_Position.xyz + (cameraRight - cameraUp) * size;
	gl_Position = vp * vec4(p3, 1.0f);
	gs_out.texCoord = vec2(1.0f, 1.0f); EmitVertex();

	vec3 p4 = gl_in[0].gl_Position.xyz + (cameraRight + cameraUp) * size;
	gl_Position = vp * vec4(p4, 1.0f);
	gs_out.texCoord = vec2(1.0f, 0.0f); EmitVertex();

	EndPrimitive();

}