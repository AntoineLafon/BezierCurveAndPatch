#version 430

layout (local_size_x = 16, local_size_y = 16) in;

layout (rgba32f, binding = 0) uniform image2D bezierPoints;
layout (rgba32f, binding = 1) uniform image2D normalTexture;

void main() {
	ivec2 coord = ivec2(gl_GlobalInvocationID.xy);
	vec3 left = vec3(imageLoad(bezierPoints, coord + ivec2(-1, 0)));
	vec3 right = vec3(imageLoad(bezierPoints, coord + ivec2(1, 0)));
	vec3 top = vec3(imageLoad(bezierPoints, coord + ivec2(0, -1)));
	vec3 bottom = vec3(imageLoad(bezierPoints, coord + ivec2(0, 1)));
	vec4 normalVector = vec4(normalize(cross(top - bottom, right - left)), 0.0f);
	imageStore(normalTexture, coord, normalVector);
}