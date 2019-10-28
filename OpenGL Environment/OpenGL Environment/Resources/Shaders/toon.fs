#version 450 core

//in vec3 fragColor;
in vec2 fragTexCoord;
in vec3 fragPos;
in vec3 fragNormal;

out vec4 color;

uniform vec3 lightPos;
uniform sampler2D tex;

void main(){
	//vec3 lightDir = normalize(fragPos - lightPos);
	vec3 lightDir = normalize(lightPos - fragPos);
	float intensity = dot(lightDir, normalize(fragNormal));
	vec4 colorResult;

	if(intensity > 0.95){
		colorResult = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}else if(intensity > 0.5f){
		colorResult = vec4(0.6f, 0.6f, 0.6f, 1.0f);
	}else if(intensity > 0.25f){
		colorResult = vec4(0.4f, 0.4f, 0.4f, 1.0f);
	}else{
		colorResult = vec4(0.1f, 0.1f, 0.1f, 1.0f);
	}

	color = texture(tex, fragTexCoord) * colorResult;

}