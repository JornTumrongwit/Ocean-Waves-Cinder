#version 330 core
uniform float		uCheckSize;
uniform vec3        ambient;
uniform vec3        diffuse;
uniform vec3        lightdir;
uniform float       shininess;
uniform float       lightstr;
uniform vec3        specular;

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

const float screenGamma = 2.2; // Assume the monitor is calibrated to the sRGB color space

in vec4             position;
out vec4			oColor;

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
		vec2 div = f*dir*peak*wa*cos(theta);

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
	vec3 w = wave(position.xyz);
	vec2 norm = w.yz;
	vec3 normal = normalize(vec3(norm, 0.0));
	vec3 lightDir = normalize(-lightdir);

	vec3 viewDir = normalize(-position.xyz);

	vec3 halfDir = normalize(lightDir + viewDir);
	float lambertian = max(dot(lightDir, normal), 0.0);
	float specAngle = max(dot(halfDir, normal), 0.0);
	float spe = pow(specAngle, shininess);

	vec3 diff = lambertian * diffuse;
	vec3 spec = specular *spe;

	vec3 col = ambient + (diff + spec)*lightstr;

	vec3 colorGammaCorrected = pow(col, vec3(1.0 / screenGamma)); ///Thanks wikipedia!
	oColor = vec4(colorGammaCorrected, 1.0);
}