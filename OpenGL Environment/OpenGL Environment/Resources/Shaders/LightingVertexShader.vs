#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

//out vec3 fragColor;
out vec2 fragTexCoord;
out vec3 fragPos;
out vec3 fragNormal;

uniform mat4 MVP;
uniform mat3 normalMatrix;
uniform mat4 model;

void main(void){
	gl_Position = MVP * vec4(position, 1.0);
	fragPos = vec3(model * vec4(position, 1.0f));
	fragNormal = normalMatrix * normal;
	fragTexCoord = texCoord;
}