
#include "View.hpp"


/* clip planes in world coordinates */
#define NEAR_Z  0.2f 
#define FAR_Z   500.0f

#define FOVY        65.0f

GLuint VBO;
GLuint VertexArrayID;

static const GLfloat g_vertex_buffer_data[] = 
{
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};

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
    this->camPos = glm::vec3(0.0, 8.0, 10.0);
    this->camAt  = glm::vec3(0.0, 0.0, 0.0);
    this->camUp  = glm::vec3(0.0, 1.0, 0.0);


  /* initialize drawable objects */ 
    // Cube * c = new Cube(); 
    // Floor * f = new Floor(); 
    // this->drawables.push_back(f); 
    // this->drawables.push_back(c); 

}


static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // glDrawArrays(GL_POINTS, 0, 1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

}


static void CreateVertexBuffer()
{
    // An array of 3 vectors which represents 3 vertices

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // glm::vec3 g_vertex_buffer_data[] = {
    //     glm::vec3(-1.0f, -1.0f, 0.0f),
    //     glm::vec3(1.0f, -1.0f, 0.0f),
    //     glm::vec3(0.0f,  1.0f, 0.0f),
    // };

    // glm::vec3 g_vertex_buffer_data[1]; 
    // g_vertex_buffer_data[0] = glm::vec3(-1.0f, -1.0f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}


void View::InitRenderers ()
{

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

void View::Render ()
{
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );  
    
    CreateVertexBuffer();
    RenderSceneCB();

}