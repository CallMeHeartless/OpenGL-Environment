#version 450 core

const unsigned int MAX_JOINTS = 100;
const unsigned int MAX_WEIGHTS = 4;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in ivec4 boneIds;
layout (location = 4) in vec4 weights;

out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragPos;

layout (location = 5) uniform mat4 vp;
layout (location = 6) uniform mat4 model;
layout (location = 7) uniform mat4 jointTransforms[MAX_JOINTS];

void main(void){
	vec4 totalLocalPosition = vec4(0.0f);
	vec4 totalNormal = vec4(0.0f);

	for(unsigned int i = 0; i < MAX_WEIGHTS; ++i){
		vec4 posePosition = jointTransforms[boneIds[i]] * vec4(position, 1.0f);
		totalLocalPosition += posePosition * weights[i];

		vec4 worldNormal = jointTransforms[boneIds[i]] * vec4(normal, 0.0f);
		totalNormal += worldNormal * weights[i];
	}

	gl_Position = vp * model * totalLocalPosition;

	fragTexCoord = texCoord;
	fragPos = vec3(model * vec4(position, 1.0f));
	fragNormal = mat3(transpose(inverse(model))) * normal;

}