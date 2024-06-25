uniform mat4	ciModelViewProjection;
uniform float   timepassed;

in vec4			ciPosition;
in vec2			ciTexCoord0;
out vec2		TexCoord0;

float offset(vec3 uv, float time)
{
	return exp(sin(0.5*uv.x + time)) + exp(sin(1*uv.x + 0.125*time)) + exp(0.5*sin(uv.x + 0.05*time)) + 
			2 * exp(sin(0.3*uv.z + 0.25*time)) + 0.2 * exp(sin(1.25*uv.z + 0.45*time)) + 0.8 * exp(sin(uv.z + 0.35*time));
}

void main(void) {
	vec4 pos = ciPosition;
	pos.y = offset(pos.xyz, timepassed*0.7) * 0.25;
	gl_Position = ciModelViewProjection * pos;
	TexCoord0 = ciTexCoord0;
}