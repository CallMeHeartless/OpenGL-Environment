#version 450 core

in vec4 fragColor;
in vec2 fragTexCoord; // This would be used in applying textures

out vec4 color;

void main(void){
	color = vec4(fragColor);
	//color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}