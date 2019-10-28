#version 450 core

layout(location = 0) in vec3 position;

layout(location = 10) uniform mat4 lightVPMatrix;
layout(location = 11) uniform mat4 model;

void main(){
	gl_Position = lightVPMatrix * model * vec4(position, 1.0f);
}