#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices = 10) out;

//out GS_FS_VERTEX{
	//vec2 texCoord;
//} gs_out;

out vec2 texCoord;

in VS_GS_VERTEX{
	in vec4 position;
	in vec3 color; 
	in mat4 mvp;
	//in vec2 textureCoords;
}gs_in[];

void main(){
	//outColor = gs_in[0].color;

	gl_Position = gs_in[0].position;
	texCoord = vec2(0.0f, 0.0f); EmitVertex();	// 0
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(1.0f, 0.0f, 0.0f, 0.0f); 
	texCoord = vec2(1.0f, 0.0f);	EmitVertex();	// 1
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(1.0f, 1.0f, 0.0f, 0.0f);
	texCoord = vec2(1.0f, 1.0f); EmitVertex();	// 2
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(0.0f, 1.0f, 0.0f, 0.0f); 
	texCoord = vec2(0.0f, 1.0f); EmitVertex();	// 3

	EndPrimitive();

}