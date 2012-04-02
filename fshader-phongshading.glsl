#version 150
in vec3 position;
in vec3 vN;

in vec4 AmbientDiffuseColor;
in vec4 SpecularColor;
in float SpecularExponent;

uniform vec4 light_position;
uniform vec4 light_color;
uniform vec4 ambient_light;
uniform vec3 spot_direction;
uniform float spot_cutoff;
uniform float spot_exponent;

struct lightSource
{
	vec4 ambient;
	vec4 position;
	vec4 diffuse;
	vec4 specular;
	float constantAttenuation, linearAttenuation, quadraticAttenuation;
	float spot_cutoff, spotExponent,spotCosCutoff; // (range: [1.0,0.0],-1.0)
	vec3 spot_direction;
};
const int numberofLightSources = 4;
uniform lightSource lights[numberofLightSources];

vec4 scene_ambient = vec4(0.2, 0.2, 0.2, 1.0);
struct material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};


out vec4  fColor;

void main()
{
	

	vec4 amb = AmbientDiffuseColor * ambient_light;
	float  attenuation = 1;

	vec4 final_color = amb;
	vec3 L;

	for ( int index = 0; index < numberofLightSources;index++)
	{
		
		
		if ( lights[index].position.w == 0 ) // directional light
		{
			attenuation = 1;
			L = normalize( lights[index].position.xyz);// - position.xyz);
		}
		else // spot light
		{
			L = normalize( lights[index].position.xyz - position.xyz);
		
			if ( lights[index].spot_cutoff <= 90.0) // spotlight?
			{
					  float clampedCosine = max(0.0, dot(-L, normalize(lights[index].spot_direction.xyz)));
					  if (clampedCosine > cos(radians(lights[index].spot_cutoff))) // outside of spotlight cone?
					  {
						  attenuation = 0;
					  }
					  else
					  {
						  attenuation = 1;//attenuation * pow(clampedCosine, spot_exponent);   
					  }
			}
	
		}

		vec3 E = normalize(-position.xyz);
		vec3 N = normalize(vN);

		vec3 H = normalize(L+E);

		vec4 diff = attenuation*max(dot(L,N), 0.0) * AmbientDiffuseColor * lights[index].diffuse;

		vec4 spec = attenuation*pow( max (dot(N,H), 0.0), SpecularExponent) *  SpecularColor * lights[index].specular;
	
		if(dot(L,N) < 0.0){
			spec = vec4(0,0,0,1);
		}
	
		final_color += amb + diff + spec;
	}
	fColor = final_color;
}