#version 400 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;

uniform sampler2D texture_diffuse1;
uniform vec3 lightColour;
uniform float shine;
uniform float reflection;

void main()
{    
	vec3 unitNormal = normalize(surfaceNormal);
	vec3 unitLightVector = normalize(toLightVector);

	float nDot1 = dot(unitNormal, unitLightVector);
	float brightness = max(nDot1, 0.2);
	vec3 diffuse = brightness * lightColour;

    FragColor = vec4(diffuse,1.0) * texture(texture_diffuse1, TexCoords);
}

