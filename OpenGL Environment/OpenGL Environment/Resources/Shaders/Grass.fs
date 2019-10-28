#version 450 core

//in GS_FS_VERTEX{
	//vec2 texCoord;
//} fs_in;

in vec2 texCoord;
out vec4 color;

uniform sampler2D tex;

void main(){
	color = texture(tex, vec2(texCoord.x, texCoord.y));

}