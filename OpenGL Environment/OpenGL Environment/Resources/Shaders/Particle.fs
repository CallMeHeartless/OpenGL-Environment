#version 450 core

in GS_FS_VERTEX{
	vec2 texCoord;	
}fs_in;

uniform sampler2D tex;
out vec4 color;

void main(){
	color = texture(tex, fs_in.texCoord);
}