
#include "View.hpp"


/* clip planes in world coordinates */
// #define NEAR_Z  0.2f 
// #define FAR_Z   500.0f

// #define FOVY        65.0f
#define NEAR_Z  0.1f 
#define FAR_Z   250.0f

#define FOVY        45.0f

View::View (GLFWwindow *window, int windowWidth, int windowHeight)
{
    // link the window and the view together
    glfwSetWindowUserPointer (window, this);
    this->window = window;

  /* view info */
    this->windowWidth 	= windowWidth;
    this->windowHeight			= windowHeight;
    this->windowVisibility			= GL_TRUE;
    this->closeWindow	= false;
    this->needsRedraw	= true;

  /* initialize the camera */
    this->angle = 0; 
    this->camPos = glm::vec3(0.0, 2.0, 4.0);
    this->camAt  = glm::vec3(0.0, 0.0, 0.0);
    this->camUp  = glm::vec3(0.0, 1.0, 0.0);


}




void View::InitRenderers ()
{
    // this->renderer = new Renderer("./shaders/TextureShader.vsh", "./shaders/TextureShader.fsh", NULL );
    // this->renderer = new Renderer("./shaders/SimpleLighting.vsh", "./shaders/SimpleLighting.fsh", NULL );
    this->renderer = new Renderer("./shaders/terrain.vsh", "./shaders/terrain.fsh", NULL );
    this->renderer->createObject();
}


/*! \brief initialize the projection matrix based on the current camera state. */
void View::InitProjMatrix ()
{
    this->projectionMat = glm::perspective (
    FOVY,
    (float)this->windowWidth / (float)this->windowHeight,
    NEAR_Z,
    FAR_Z);
}

/*! \brief initialize the model-view matrix based on the current camera state. */
void View::InitModelViewMatrix ()
{
    this->modelViewMat = glm::lookAt (
    this->camPos,
    this->camAt,
    this->camUp);

}


//All of this will be moved into a renderer class ********
void View::Render ()
{
    this->renderer->setMatrices(this->modelViewMat,this->projectionMat);
    this->renderer->renderScene();
}