#version 430

layout (local_size_x = 16, local_size_y = 16) in;

layout (rgba32f, binding = 0) uniform image2D bezierPoints;
layout (rgba32f, binding = 1) uniform image2D controlPoints;

uniform int ControlSize;
uniform int bezierSize;

int factorial(int n){
int result = 1;
	for(int i = 1; i <= n; i++){
		result *= i;
	}
	return result;
}


float bernstein(float t, int i, int n)
{
	int ni = factorial(n);
	int ii = factorial(i);
	int ni_i = factorial(n-i);
	float binom = float(ni) / float(ii * ni_i);
	return binom * pow(t, i) * pow(1.0f - t, n - i);
}


void main() {
	ivec2 coord = ivec2(gl_GlobalInvocationID);
	vec4 bp = vec4(0.0f);
	for (int i = 0; i < ControlSize; i++){
		for(int j = 0; j < ControlSize; j++){
			vec4 cp = imageLoad(controlPoints, ivec2(i, j));
			float a = bernstein(float(coord.x) / (bezierSize - 1), i, ControlSize - 1);
			float b = bernstein(float(coord.y) / (bezierSize - 1), j, ControlSize - 1);
			bp +=  a * b * cp;
		}
	}
	imageStore(bezierPoints, coord, bp);
}