#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;

uniform mat4 view;
uniform mat4 projection;
uniform int mode;
uniform sampler2D bezierTexture;
uniform sampler2D normalTexture;

out vec4 aNorm;
out vec3 aPos;
out vec2 aTex;
out vec3 aColor;

void main(){
	vec4 normal = texture(normalTexture, textureCoord);
	vec3 newPosition = texture(bezierTexture, textureCoord).rgb;
	gl_Position = projection * view * vec4(newPosition, 1.0f);
	aNorm = normal;
	aPos = position;
	aTex = textureCoord;
	switch(mode){
	case 0:
		aColor = vec3(aNorm);
		break;
	case 1:
		aColor = aPos * 0.5 + 0.5;
		break;
	case 2:
		aColor = vec3(textureCoord, 0.0f);
		break;
	default:
		break;
	}
}