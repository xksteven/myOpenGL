//Simple Vertex Shader
#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

// Values that stay constant for the whole mesh.
uniform mat4 modelViewMat;
uniform mat4 projMat;

void main()
{

    // gl_Position.xyz = vertexPosition_modelspace;
    // gl_Position.w = 1.0;
	gl_Position =  projMat * modelViewMat * vec4(vertexPosition_modelspace,1);

}
