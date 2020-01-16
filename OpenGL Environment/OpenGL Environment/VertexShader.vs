#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal; // This would be utilised to incorporate lighting
layout (location = 2) in vec2 texCoord;

out vec2 fragTexCoord;
out vec4 fragColor;

layout(location = 5) uniform mat4 MVP;
layout(location = 6) uniform vec4 colour;

void main(){
	gl_Position = MVP * vec4(position, 1.0f);
	//gl_Position = vec4(position, 1.0f);
	fragTexCoord = texCoord;
	fragColor = colour;
}