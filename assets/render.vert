uniform mat4	ciModelViewProjection;
uniform float   timepassed;

in vec4			ciPosition;
in vec2			ciTexCoord0;
out vec2		TexCoord0;

float offset(vec2 uv)
{
	return (sin(uv.x*3000.0f * 15.0+timepassed*0.1) +
		cos(uv.y*3000.0f * 7.0f + uv.x * 13.0f + timepassed*0.5f)) * 0.5f;
}

void main(void) {
	vec4 pos = ciPosition;
	pos.y = offset(ciTexCoord0) - 10.f;
	gl_Position = ciModelViewProjection * pos;
	TexCoord0 = ciTexCoord0;
}