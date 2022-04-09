#version 330 core

in vec4 aNorm;
in vec3 aPos;
in vec2 aTex;
in vec3 aColor;

out vec4 fragColor;

uniform vec3 cameraPosition;
uniform vec3 lightPosition[3];

vec3 lightColor = vec3(1.0f, 1.0f, 1.0f) * 0.7f;
vec3 objectColor = vec3(57.0f/255.0f, 174.0f/255.0f, 169.0f/255.0f);

float diffuse(vec3 normal, vec3 lightDir) {
	return max(dot(normal, lightDir), 0.0) * 0.5;
}

float specular(vec3 normal, vec3 lightPos, vec3 eyeView){
    vec3 lightDir = normalize(aPos - lightPos);
	vec3 viewDir  = normalize(eyeView - aPos);
	vec3 reflectDir = reflect(lightDir, normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), 64);
	return spec * 0.8;
}

void main(){
    vec3 result = vec3(0.0f);
    vec3 normal = vec3(aNorm);
	vec3 norm = -normalize(normal);
	
    //ambient
    vec3 ambient = 0.2 * lightColor;
	result = ambient;
	for(int i = 0; i < 3; i++){
	result += diffuse(norm, normalize(aPos - lightPosition[i]));
	result += specular(norm, lightPosition[i], cameraPosition) * lightColor;
	}
	
    result *= aColor;
    fragColor = vec4(result, 1.0f);
}