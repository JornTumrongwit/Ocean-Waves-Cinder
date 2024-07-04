#version 330 core
uniform float		uCheckSize;

in vec3             w;
out vec4			oColor;

vec2 checker(vec2 norm)
{
	return norm;
}

void main(void) {
	vec2 norm = w.yz;
	oColor = vec4(norm.x, norm.y, 0.0, 1.0);
}