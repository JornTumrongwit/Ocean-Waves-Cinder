uniform mat4	ciModelViewProjection;
uniform float   timepassed;
uniform float   offset;
uniform float   zoff;
uniform float   seed;
uniform float   amplitude;
uniform float   amp_mult;
uniform float   frequency;
uniform float   freq_mult;

in vec4			ciPosition;
in vec2			ciTexCoord0;
out vec2		TexCoord0;

vec3 wave(vec3 uv)
{
	float a = amplitude;
	float f = frequency;
	
	float rise = 0.0;
	int i = 0
	while(i<1){
		vec2 dir = normalize(vec2(cos(seed), sin(seed)));
		float theta = f*dot(uv.xz, dir) + 1.5*timepassed;
		vec3 w = vec3(0.0);
		rise += a*exp(sin(theta));
		a *= amp_mult;
		f *= freq_mult;
		i += 1;
	}
	w.x = rise - offset;
	return w;
}

void main(void) {
	vec4 pos = ciPosition;
	vec3 w = wave(pos.xyz);
	pos.y = w.x;
	pos.z += zoff;
	gl_Position = ciModelViewProjection * pos;
	TexCoord0 = ciTexCoord0;
}