
#include "View.hpp"


/* clip planes in world coordinates */
// #define NEAR_Z  0.2f 
// #define FAR_Z   500.0f

// #define FOVY        65.0f
#define NEAR_Z  0.1f 
#define FAR_Z   100.0f

#define FOVY        45.0f


// static const GLfloat g_vertex_buffer_data[] = 
// {
//     -1.0f, -1.0f, 0.0f,
//     1.0f, -1.0f, 0.0f,
//     0.0f,  1.0f, 0.0f,
// };

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


  /* initialize drawable objects */ 
    // Cube * c = new Cube(); 
    // Floor * f = new Floor(); 
    // this->drawables.push_back(f); 
    // this->drawables.push_back(c); 

}



// //All of this will be moved into a renderer class ********
// void View::CreateVertexBuffer()
// {
//     // Enable depth test
//     glEnable(GL_DEPTH_TEST);
//     // Accept fragment if it closer to the camera than the former one
//     glDepthFunc(GL_LESS); 

//     // An array of 3 vectors which represents 3 vertices

//     glGenVertexArrays(1, &VertexArrayID);
//     glBindVertexArray(VertexArrayID);

//     // glm::vec3 g_vertex_buffer_data[] = {
//     //     glm::vec3(-1.0f, -1.0f, 0.0f),
//     //     glm::vec3(1.0f, -1.0f, 0.0f),
//     //     glm::vec3(0.0f,  1.0f, 0.0f),
//     // };

//     // glm::vec3 g_vertex_buffer_data[1]; 
//     // g_vertex_buffer_data[0] = glm::vec3(-1.0f, -1.0f, 0.0f);

//     glGenBuffers(1, &VBO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

//     // glGenBuffers(1, &colorVBO);
//     // glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
//     // glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

//     // Load the texture using any two methods
//     GLuint Texture = loadBMP_custom("uvtemplate.bmp");
//     // GLuint Texture = loadDDS("uvtemplate.DDS");
    
//     // Get a handle for our "myTextureSampler" uniform
//     GLuint TextureID  = glGetUniformLocation(this->programID, "myTextureSampler");

//     glGenBuffers(1, &textureVBO);
//     glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

//     // Bind our texture in Texture Unit 0
//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_2D, Texture);
//     // Set our "myTextureSampler" sampler to user Texture Unit 0
//     glUniform1i(TextureID, 0);

//     //If you unbind VAO rebind it before you describe the VBO's
//     glBindVertexArray (0);
//     glBindBuffer (GL_ARRAY_BUFFER, 0);
// }

// static void RenderSceneCB()
// {

//     glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

//     glBindVertexArray(VertexArrayID);

//     // Vertices
//     glEnableVertexAttribArray(0);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
 
//     // // Colors
//     // glEnableVertexAttribArray(1);
//     // glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
//     // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

//     // 2nd attribute buffer : UVs
//     glEnableVertexAttribArray(1);
//     glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
//     glVertexAttribPointer(
//         1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
//         2,                                // size : U+V => 2
//         GL_FLOAT,                         // type
//         GL_FALSE,                         // normalized?
//         0,                                // stride
//         (void*)0                          // array buffer offset
//     );

//     // glDrawArrays(GL_POINTS, 0, 1);
//     // To draw only really need to rebind VAO and relevant VBO's again
//     glDrawArrays(GL_TRIANGLES, 0, 12*3);

//     glDisableVertexAttribArray(0);
//     glDisableVertexAttribArray(1);
// }




void View::InitRenderers ()
{

    this->renderer = new Renderer("TextureShader.vsh", "TextureShader.fsh", NULL );
    this->renderer->CreateVertexBuffer();
    // // Create and compile our GLSL program from the shaders
    // // this->programID = LoadShaders( "SimpleVertexShader.vsh", "SimpleFragmentShader.fsh", NULL );
    // this->programID = LoadShaders( "TextureShader.vsh", "TextureShader.fsh", NULL );


    // // Get a handle for our "MV" uniform
    // this->modelViewMatID = glGetUniformLocation(programID, "modelViewMat");

    // // Get a handle for our "P" uniform
    // this->projMatID = glGetUniformLocation(programID, "projMat");

    // // Get a handle for our "color" uniform
    // this->colorID = glGetUniformLocation(programID, "vertColor");

    // // Get a handle for our "texture" uniform
    // this->textureID = glGetUniformLocation(programID, "myTextureSampler");


}
//End of all of this will be moved into a renderer class ********




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
    // glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    // // Clear the screen
    // // glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    
    // // Use our shader
    // glUseProgram(this->programID);


    // glUniformMatrix4fv(this->modelViewMatID, 1, GL_FALSE, &this->modelViewMat[0][0]);
    // glUniformMatrix4fv(this->projMatID, 1, GL_FALSE, &this->projectionMat[0][0]);
    // glUniform4fv(this->colorID, 1, &this->color[0]);


    this->renderer->SetMatrices(this->modelViewMat,this->projectionMat);
    this->renderer->RenderScene();
}