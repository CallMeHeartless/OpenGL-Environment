#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices = 10) out;

out vec3 outColor;

in VS_GS_VERTEX{
	in vec4 position;
	in vec3 color; 
	in mat4 mvp;
}gs_in[];

void main(){
	outColor = gs_in[0].color;

	gl_Position = gs_in[0].position; EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(1.0f, 2.0f, 0.0f, 0.0f); EmitVertex();	// 1
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(-1.0f, 2.0f, 0.0f, 0.0f); EmitVertex();	// 2

	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(0.0f, 3.0f, 0.0f, 0.0f); EmitVertex();	// 3
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(1.0f, 1.0f, 0.0f, 0.0f); EmitVertex();	// 4
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(-1.0f, 1.0f, 0.0f, 0.0f); EmitVertex();	// 5

	

	EndPrimitive();

}



//		gl_Position = gs_in[0].position; EmitVertex();
	//gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(-1.0f, -2.0f, 0.0f, 0.0f); EmitVertex();	// 1
	//gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(2.0f, -1.0f, 0.0f, 0.0f); EmitVertex();	// 2

//	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(-2.0f, -1.0f, 0.0f, 0.0f); EmitVertex();	// 3
	//gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(1.0f, -2.0f, 0.0f, 0.0f); EmitVertex();	// 4
	//gl_Position = gs_in[0].position; EmitVertex();
	//gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(-1.0f, 1.0f, 0.0f, 0.0f); EmitVertex();	// 5