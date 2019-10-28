#version 450 core

//in vec3 fragColor;
in vec2 fragTexCoord;
in vec3 fragPos;
in vec3 fragNormal;
in vec4 mWorldPos;

out vec4 color;

// Texture
uniform sampler2D tex;
// Ambience
uniform float ambientStrength; // 0.0f;
uniform vec3 ambientColor;		// glm::vec3(1.0f, 1.0f, 1.0f);
// Diffuse
uniform vec3 lightColor;		// glm::vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightPos;			// glm::vec3(5.0f, 5.0f, 5.0f);
// Specular
uniform float lightSpecStrength; // = 1.0f;
uniform vec3 camPos;			// = glm::vec3(1.0f, 1.0f, 3.0f);
uniform float shininess;		// = 32.0f;



void main(void){
	// Ambient
	vec3 ambient = ambientStrength * ambientColor;

	// Light direction
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(fragPos - lightPos);

	// Diffuse colour
	float diffuseStrength = max(dot(norm, -lightDir), 0.0f);
	vec3 diffuse = diffuseStrength * lightColor;

	// Specular Highlight
	vec3 negViewDir = normalize(camPos - fragPos);
	//vec3 reflectDir = reflect(lightDir, norm);
	vec3 halfwayVec = normalize(-lightDir + negViewDir);
	float spec = pow(max(dot(norm, halfwayVec), 0.0f), shininess);
	vec3 specular = lightSpecStrength * spec * lightColor;

	// Fog
	float d = distance(mWorldPos.xyz, camPos);
	float lerp = (d - 5.0f)/10.0f;
	lerp = clamp(lerp, 0.0, 1.0f);

	vec4 vFogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

	color = mix(vec4(ambient + diffuse + specular, 1.0f) *  texture(tex, fragTexCoord), vFogColor, lerp);
	//color = mix(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), vFogColor, lerp);
}