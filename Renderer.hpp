#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include "shader.hpp"
#include "View.hpp"

class Renderer 
{
	public:
		~Renderer();

		void Render();

    	GLuint  modelViewMatID, colorID, projMatID;
};

#endif