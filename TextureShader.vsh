#version 330

// Values that stay constant for the whole mesh.
uniform mat4 modelViewMat;
uniform mat4 projMat;


layout (location = 0) in vec3 vertexPosition_modelspace;
// layout (location = 1) in vec3 normal;
layout (location = 1) in vec2 tCoord;

out vec2 fragmentTextureCoordinates;
// out vec3 fragmentNormal;

void main () {
	gl_Position =  projMat * modelViewMat * vec4(vertexPosition_modelspace,1);    
	fragmentTextureCoordinates = tCoord;
    // fragmentNormal = normal;
}
