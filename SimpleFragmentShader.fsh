#version 330 core


// uniform vec4 vertColor;
in vec3 fragmentColor;
// Ouput data
out vec4 color;

void main()
{

	// Output color = red 
	// color = vertColor;
	color = vec4(fragmentColor,1.0);

}