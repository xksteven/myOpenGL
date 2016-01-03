//Simple Vertex Shader
#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

// Values that stay constant for the whole mesh.
uniform mat4 modelViewMat;
uniform mat4 projMat;

out vec3 fragmentColor;

void main()
{

    // gl_Position.xyz = vertexPosition_modelspace;
    // gl_Position.w = 1.0;
	gl_Position =  projMat * modelViewMat * vec4(vertexPosition_modelspace,1);
	fragmentColor = vertexColor;
}
