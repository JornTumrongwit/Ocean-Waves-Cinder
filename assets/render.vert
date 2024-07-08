#version 330 core
uniform mat4	ciModelViewProjection;
uniform float   timepassed;
uniform float   offset;
uniform float   zoff;
uniform float   seed;
uniform float   seed_mult;
uniform float   amplitude;
uniform float   amp_mult;
uniform float   frequency;
uniform float   freq_mult;
uniform int     wave_count;
uniform float   speed;
uniform float   speed_mult;
uniform float   peak;
uniform float   peak_offset;
uniform float   drag;

in vec4			ciPosition;
in vec2			ciTexCoord0;
out vec3        w;
out vec4        position;

vec3 wave(vec3 uv)
{
	float a = amplitude;
	float f = frequency;
	float s = speed;
	float sd = seed;
	
	float rise = 0.0;
	vec2 norm = vec2(0.0);
	vec3 p = uv;

	float amp_total = 0.0;
	for( int i = 0; i < wave_count; i++) {
		vec2 dir = normalize(vec2(cos(sd), sin(sd)));
		float theta = f*dot(p.xz, dir) + s*timepassed;
		float wa = a*exp(sin(theta) * peak - peak_offset);
		vec2 div = f*dir*peak*wa*cos(peak);

		rise += wa;
		norm+=div;

		p.xz += -div * a * drag;
		
		amp_total += a;

		a *= amp_mult;
		f *= freq_mult;
		s *= speed_mult;
		sd += seed_mult;
	}

	vec3 w = vec3(rise, norm.x, norm.y)/amp_total;
	w.x += - offset;
	return w;
}

void main(void) {
	vec4 pos = ciPosition;
	w = wave(pos.xyz);
	pos.y = w.x;
	pos.z += zoff;
	gl_Position = ciModelViewProjection * pos;
	position = ciModelViewProjection * pos;
}