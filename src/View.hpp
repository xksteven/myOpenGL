#ifndef __VIEW_HPP__
#define __VIEW_HPP__

#include <GL/glew.h> //The extension wrangler

#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp> //matrix and vec library
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

#include "Renderer.hpp"

// #include "Shader.hpp"
// #include "texture.hpp"

#include <iostream>
#include <stdio.h>

class View {
	public:
		View(GLFWwindow *window, int windowWidth, int windowHeight);
		~View();

	    GLFWwindow		*window;		//!< the application window
		bool needsRedraw;
		bool closeWindow;
		int windowWidth, windowHeight;
		bool windowVisibility;
	
		glm::mat4	modelViewMat;	//!< the current model-view matrix
	    glm::mat4	projectionMat;	//!< the current projection matrix

		glm::vec3	camPos;		//!< camera position in world space
	    glm::vec3	camAt;		//!< camera look-at point in world space
	    glm::vec3	camUp;	
	    float angle;

	    Renderer* renderer;

	    //All of this will be moved into the renderer class *********
 
    	// GLuint  modelViewMatID, colorID, projMatID,textureID;
	    // GLuint programID;
	    // glm::vec4 color = glm::vec4(1.0,0.0,0.0,1.0);

	    //End of All of this will be moved into the renderer class *********



	  //! \brief bind the framebuffer back to the screen. 
	   // void BindFrameBuffer(); 

	  //! \brief initializes the depth buffer for the view state
	    // void InitDepthBuffer(); 

	  //! \brief initialize the light's model-view, projection matrices and the shadow matrixx for the view state.
	    // void InitLightMatrices(); 

	  /*! \brief initialize the renderers by loading and compiling their shaders.
	   *  Note that this function needs to be called after the current
	   *  OpenGL context has been set.
	   */
	    void InitRenderers ();

	  /*! \brief initialize the projection matrix based on the current camera state. */
	    void InitProjMatrix ();

	  /*! \brief initialize the model-view matrix based on the current camera state. */
	    void InitModelViewMatrix ();

	  /*! \brief render the state of the scene
	   */
	    void Render ();

	    //to be deleted soon and moved to renderer
	    // void CreateVertexBuffer();

};

#endif