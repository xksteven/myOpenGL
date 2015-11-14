#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <GL/glew.h> //The extension wrangler

#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp> //matrix and vec library
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include "Shader.hpp"
#include "texture.hpp"

class Renderer 
{
	public:
		~Renderer();

		Renderer(const char* vertShader, const char* fragShader, const char* geoShader);

		void CreateVertexBuffer();
		void SetMatrices(glm::mat4 modelViewMat, glm::mat4 projectionMat);
		void RenderSceneCB();

		GLuint* VertexArrayID;
		GLuint* VBO;
		GLuint* colorVBO;
		GLuint* textureVBO;

    	GLuint  modelViewMatID, colorID, projMatID,textureID;
	    GLuint programID;
	    glm::vec4 color = glm::vec4(1.0,0.0,0.0,1.0);


};

#endif