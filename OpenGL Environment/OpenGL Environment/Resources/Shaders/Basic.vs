#version 450 core

layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 normal;
layout (location = 1) in vec2 texCoord;

//out vec3 fragColor;
out vec2 fragTexCoord;
//out vec3 fragPos;
//out vec3 fragNormal;

void main(){
	gl_Position = vec4(position.xy, 0.0f, 1.0f);
	//fragPos = position;
	fragTexCoord = texCoord;
	//fragNormal = normal;
}