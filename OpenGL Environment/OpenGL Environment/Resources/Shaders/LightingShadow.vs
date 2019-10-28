#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

//out vec3 fragColor;
out vec2 fragTexCoord;
out vec3 fragPos;
out vec3 fragNormal;
out vec4 FragPosLightSpace;

layout(location = 3) uniform mat4 model;
layout(location = 4) uniform mat4 MVP;
layout(location = 5) uniform mat3 normalMatrix;
layout(location = 6) uniform mat4 lightVPMatrix;

void main(void){
	gl_Position = MVP * vec4(position, 1.0);
	fragPos = vec3(model * vec4(position, 1.0f));
	fragNormal = normalMatrix * normal;
	fragTexCoord = texCoord;
	FragPosLightSpace = lightVPMatrix * vec4(fragPos, 1.0f);
}