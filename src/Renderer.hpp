#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "Shader.hpp"
#include "texture.hpp"

class Renderer 
{
	public:
		~Renderer();

		void Render();

		void CreateVertexBuffer();

    	GLuint  modelViewMatID, colorID, projMatID,textureID;
	    GLuint programID;
	    glm::vec4 color = glm::vec4(1.0,0.0,0.0,1.0);


};

#endif