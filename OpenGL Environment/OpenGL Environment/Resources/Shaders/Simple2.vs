#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) uniform vec3 tPosition;

void main(){
	gl_Position = vec4(position, 1.0f);
	//gl_Position = vec4(tPosition, 1.0f);
}