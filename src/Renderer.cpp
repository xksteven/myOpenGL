#include "Renderer.hpp"

static const GLfloat g_vertex_buffer_data[] = { 
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = { 
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};

// Two UV coordinatesfor each vertex. They were created with Blender.
static const GLfloat g_uv_buffer_data[] = { 
    0.000059f, 1.0f-0.000004f, 
    0.000103f, 1.0f-0.336048f, 
    0.335973f, 1.0f-0.335903f, 
    1.000023f, 1.0f-0.000013f, 
    0.667979f, 1.0f-0.335851f, 
    0.999958f, 1.0f-0.336064f, 
    0.667979f, 1.0f-0.335851f, 
    0.336024f, 1.0f-0.671877f, 
    0.667969f, 1.0f-0.671889f, 
    1.000023f, 1.0f-0.000013f, 
    0.668104f, 1.0f-0.000013f, 
    0.667979f, 1.0f-0.335851f, 
    0.000059f, 1.0f-0.000004f, 
    0.335973f, 1.0f-0.335903f, 
    0.336098f, 1.0f-0.000071f, 
    0.667979f, 1.0f-0.335851f, 
    0.335973f, 1.0f-0.335903f, 
    0.336024f, 1.0f-0.671877f, 
    1.000004f, 1.0f-0.671847f, 
    0.999958f, 1.0f-0.336064f, 
    0.667979f, 1.0f-0.335851f, 
    0.668104f, 1.0f-0.000013f, 
    0.335973f, 1.0f-0.335903f, 
    0.667979f, 1.0f-0.335851f, 
    0.335973f, 1.0f-0.335903f, 
    0.668104f, 1.0f-0.000013f, 
    0.336098f, 1.0f-0.000071f, 
    0.000103f, 1.0f-0.336048f, 
    0.000004f, 1.0f-0.671870f, 
    0.336024f, 1.0f-0.671877f, 
    0.000103f, 1.0f-0.336048f, 
    0.336024f, 1.0f-0.671877f, 
    0.335973f, 1.0f-0.335903f, 
    0.667969f, 1.0f-0.671889f, 
    1.000004f, 1.0f-0.671847f, 
    0.667979f, 1.0f-0.335851f
};


Renderer::Renderer (const char* vertShader, const char* fragShader, const char* geoShader)
{

    // Create and compile our GLSL program from the shaders
    // this->programID = LoadShaders( "SimpleVertexShader.vsh", "SimpleFragmentShader.fsh", NULL );
    this->programID = LoadShaders( vertShader, fragShader, NULL );


    // Get a handle for our "MV" uniform
    this->modelViewMatID = glGetUniformLocation(programID, "modelViewMat");

    // Get a handle for our "P" uniform
    this->projMatID = glGetUniformLocation(programID, "projMat");

    // Get a handle for our "color" uniform
    this->colorID = glGetUniformLocation(programID, "vertColor");

    // Get a handle for our "texture" uniform
    this->textureID = glGetUniformLocation(programID, "myTextureSampler");

    // Get a handle for our "light" uniform
    this->lightID = glGetUniformLocation(programID, "lightPosition_worldspace");

    this->terrHeight = glGetUniformLocation(programID, "fRenderHeight");
    this->maxTextU = glGetUniformLocation(programID, "fMaxTextureU");
    this->maxTextV = glGetUniformLocation(programID, "fMaxTextureV");
        
    this->heightMapScale = glGetUniformLocation(programID, "HeightmapScaleMatrix");
    // if (this->lightID == -1)
    // {
    //     this->inUse = false;
    // }
    // printf("textID = %d lightID = %d\n",textureID,lightID );
}

//All of this will be moved into a mesh class ********
void Renderer::createObject()
{
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    // glDepthFunc(GL_LESS); 

    // unsigned int image_ID;
    // const char* file_name = "./data/earthmap1k.png";
    // const char* file_name = "./data/uvtemplate.bmp";
    const char* file_name = "./data/virus-cells-texture-Stock-Photo.png";

    // Used by devil currently not in use
    // ilInit();
    // iluInit();
    // ilutInit();
    // ilutRenderer(ILUT_OPENGL);
    // this->image_ID[0] = ilutGLLoadImage((char*)file_name);


    this->image_ID[0] = loadImage((char*)file_name);
    printf("image loaded? %d\n", this->image_ID[0]);

    // An array of 3 vectors which represents 3 vertices

    this->VertexArrayID = new GLuint[1];
    this->VBO 			= new GLuint[1];
	this->colorVBO 		= new GLuint[1];
	this->textureVBO 	= new GLuint[1];
    this->normalVBO     = new GLuint[1];

    glGenVertexArrays(1, this->VertexArrayID);
    glBindVertexArray(*(this->VertexArrayID));


    GLuint Texture = this->image_ID[0];
    
    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID  = glGetUniformLocation(this->programID, "myTextureSampler");

    // glGenBuffers(1, this->VBO);
    // glBindBuffer(GL_ARRAY_BUFFER, *(this->VBO));
    // glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // // glGenBuffers(1, &colorVBO);
    // // glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    // // glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    // glGenBuffers(1, this->textureVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, *(this->textureVBO));
    // glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);


    // Read it in as object files as opposed to the hard coded arrays above
    // Read our .obj file
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; 
    bool res = loadOBJ("./data/earth.obj", vertices, uvs, normals);
    // bool res = loadOBJ("./data/cube.obj", vertices, uvs, normals);
    //How loading vertex buffer would change
    glGenBuffers(1, this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *(this->VBO));
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    this->numVerts = vertices.size();

    // GLuint uvbuffer;
    glGenBuffers(1, this->textureVBO);
    glBindBuffer(GL_ARRAY_BUFFER, *(this->textureVBO));
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);


    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // Set our "myTextureSampler" sampler to user Texture Unit 0
    glUniform1i(TextureID, 0);

    glGenBuffers(1, this->normalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, *(this->normalVBO));
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);


    //If you unbind VAO rebind it before you describe the VBO's
    glBindVertexArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, 0);

    this->htmap = new CMultiLayeredHeightmap();
    this->htmap->LoadHeightMapFromImage("./data/testImage.png");
    this->htmap->SetRenderSize(0.5f,5.0f);
    printf("%f %f %f\n", this->htmap->vRenderScale[0],this->htmap->vRenderScale[1],this->htmap->vRenderScale[2]);

}

void Renderer::setMatrices(glm::mat4 modelViewMat, glm::mat4 projectionMat)
{

    glUniformMatrix4fv(this->modelViewMatID, 1, GL_FALSE, &modelViewMat[0][0]);
    glUniformMatrix4fv(this->projMatID, 1, GL_FALSE, &projectionMat[0][0]);
    glUniform4fv(this->colorID, 1, &this->color[0]);

}

void Renderer::renderScene()
{


    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

    // Use our shader
    glUseProgram(this->programID);

    if (this->lightID != -1)
    {
        glm::vec3 lightPos = glm::vec3(4,4,4);
        glUniform3f(this->lightID, lightPos.x, lightPos.y, lightPos.z);
    }

    if (renderTerrain)
    {

        // Now we're ready to render - we are drawing set of triangle strips using one call, but we g otta enable primitive restart
        glBindVertexArray(this->htmap->uiVAO);
        glEnable(GL_PRIMITIVE_RESTART);
        int iRows = this->htmap->GetNumHeightmapRows();
        int iCols = this->htmap->GetNumHeightmapCols();
        glPrimitiveRestartIndex(iRows*iCols);
    
        glUniform1f(this->terrHeight, this->htmap->vRenderScale.y);
        glUniform1f(this->maxTextU, float(iCols)*0.1f);
        glUniform1f(this->maxTextV, float(iRows)*0.1f);
        glm::mat4 myMat = glm::scale(glm::mat4(1.0), glm::vec3(this->htmap->vRenderScale));
        glUniformMatrix4fv(this->heightMapScale, 1, GL_FALSE, &glm::scale(glm::mat4(1.0), glm::vec3(this->htmap->vRenderScale))[0][0]);

        int iNumIndices = (iRows-1)*iCols*2 + iRows-1;
        glDrawElements(GL_TRIANGLE_STRIP, iNumIndices, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glBindVertexArray(*(this->VertexArrayID));

        // Vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, *(this->VBO));
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
     
        // // Colors
        // glEnableVertexAttribArray(1);
        // glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, *(this->textureVBO));
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            2,                                // size : U+V => 2
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, *(this->normalVBO));
        glVertexAttribPointer(
            2,                                // attribute
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        // glDrawArrays(GL_POINTS, 0, 1);
        // To draw only really need to rebind VAO and relevant VBO's again
        // glDrawArrays(GL_TRIANGLES, 0, 12*3);
        glDrawArrays(GL_TRIANGLES, 0, this->numVerts);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }

}