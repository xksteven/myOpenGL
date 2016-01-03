#version 330

uniform sampler2D myTextureSampler;

/** Uniforms you will use for lighting (and maybe more...) **/
// uniform vec3 direction;
// uniform vec3 ambient;
// uniform vec3 intensity;
uniform vec4 vertColor;
// uniform bool to_texture;

// uniform vec4 vertColor;
// in vec3 fragmentColor;
// Ouput data
out vec4 color;

in vec2 fragmentTextureCoordinates;
// in vec3 f_normal;

// in vec4 gl_FragCoord ;

out vec4 fragColor;


void main ()
{
    // vec3 norm = normalize(f_normal); //renormalize the normal

    /* This is the color for the fragment without lighting. You will use the lighting equation
      defined in the project to compute the frag color with lighting included. */
    // if (to_texture) {
    // 	fragColor = vec4( (ambient + max(0, dot(-direction, norm)) * intensity), 1) * texture(sampler,f_tCoord);
    // } else {
	   //  fragColor = vec4( (ambient + max(0, dot(-direction, norm)) * intensity), 1) * vColor;
    // }
    fragColor = texture2D( myTextureSampler, fragmentTextureCoordinates );
    // fragColor = vec4(color, 1.0);
}


