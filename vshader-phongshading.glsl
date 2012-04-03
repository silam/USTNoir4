#version 150
#define NUM_LIGHTS 5
in vec4 vPosition;
in vec4 vAmbientDiffuseColor;
in vec3 vNormal;
in vec4 vSpecularColor;
in float vSpecularExponent;
in vec4 vIsOn;

//out vec4 color;
out vec3 position;
out vec3 vN;

out vec4 AmbientDiffuseColor;
out vec4 SpecularColor;
out float SpecularExponent;
out vec4 IsOn;

uniform mat4 model_view;
uniform mat4 projection;
flat out int lightOn[NUM_LIGHTS];

void
main()
{
	vec4 vNormal = vec4(vNormal, 0.0);
    
	AmbientDiffuseColor = vAmbientDiffuseColor;
	SpecularColor = vSpecularColor;
	SpecularExponent = vSpecularExponent;

	//IsOn = vIsOn;

	vec4 veyepos = model_view*vPosition;
		
	vN = normalize(model_view * vNormal).xyz;
	int i;
	for (i = 0; i<NUM_LIGHTS; ++i)
	{
		if ( i < 3)
		{
			lightOn[i] = 1;
		}
		if ( i >= 3 )
		{
			if ( vIsOn.w == 0 )
			{
				lightOn[i] = 0;
			}
			else
			{
				lightOn[i] = 1;
			}
		}
    }

	
	position = veyepos.xyz;
	gl_Position = projection * veyepos;
	

}