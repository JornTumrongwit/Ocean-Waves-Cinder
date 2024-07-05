#version 330 core
uniform float		uCheckSize;
uniform vec3        ambient;
uniform vec3        diffuse;
uniform vec3        lightdir;
uniform float       shininess;
uniform float       lightstr;
uniform vec3        specular;

const float screenGamma = 2.2; // Assume the monitor is calibrated to the sRGB color space

in vec3             w;
in vec4             position;
out vec4			oColor;

vec2 checker(vec2 norm)
{
	return norm;
}

void main(void) {
	vec2 norm = w.yz;
	vec3 normal = normalize(vec3(norm.x, norm.y, 0.0));
	vec3 lightDir = normalize(lightdir);

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