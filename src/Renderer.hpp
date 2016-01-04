#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <GL/glew.h> //The extension wrangler

#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp> //matrix and vec library
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>


#include "Shader.hpp"
#include "texture.hpp"
#include "objloader.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Used by devil currently not in use
// #define ILUT_USE_OPENGL	// This MUST be defined before calling the DevIL headers or we don't get OpenGL functionality
// #include <IL/il.h>
// #include <IL/ilu.h>
// #include <IL/ilut.h>

class Renderer 
{
	public:
		~Renderer();

		Renderer(const char* vertShader, const char* fragShader, const char* geoShader);

		void createObject();
		void setMatrices(glm::mat4 modelViewMat, glm::mat4 projectionMat);
		void renderScene();

    	GLuint  modelViewMatID, colorID, projMatID, textureID, lightID;
    	// bool inUse;
	    GLuint programID;

		GLuint image_ID[1]; 			

		GLuint* VertexArrayID;
		GLuint* VBO;
		GLuint* colorVBO;
		GLuint* textureVBO;
		GLuint* normalVBO;
		int numVerts;

	    glm::vec4 color = glm::vec4(1.0,0.0,0.0,1.0);


};

#endif