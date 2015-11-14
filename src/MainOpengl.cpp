#include <stdio.h>

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h> //The extension wrangler

//Include GLFW or freeglut they both provide the same functionality
// Include GLFW
#include <GLFW/glfw3.h>
// #include <GL/freeglut.h>

// // Include GLM
// #include <glm/glm.hpp> //matrix and vec library

#include "WindowCallbacks.hpp"
#include "Shader.hpp"
// #include "View.hpp"

int main(int argc, char** argv)
{
    glfwSetErrorCallback (Error);

    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    SetViewport (window);

    //not caused seg fault so I might be able to keep view in
    // callback class
    // View *view = SetupView(window);

    // GLenum  err;
    // while ((err = glGetError()) != GL_NO_ERROR) {
    //     std::cerr << "OpenGL1 error: " << err << std::endl;
    // }

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return -1;
    }

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "this is a know error with glew Init and can be ignored: " << err << std::endl;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);



    // The ordering of when create shaders is called is important
    // Must be called after glewInit()
    SetupView(window);


    // // Create and compile our GLSL program from the shaders
    // GLuint programID = LoadShaders( "SimpleVertexShader.vsh", "SimpleFragmentShader.fsh", NULL );



    // set up callbacks
    glfwSetWindowRefreshCallback (window, Display);
    glfwSetWindowSizeCallback (window, Reshape);
    glfwSetWindowIconifyCallback (window, Visible);
    glfwSetKeyCallback (window, Key);
    glfwSetCursorPosCallback(window, cursor_Pos_Callback);

    //main loop
    do{
        if(NeedtoRedraw())
        {
            printf("NeedtoRedraw\n");
            Display (window);
        }

        // // Use our shader
        // glUseProgram(programID);

        // Swap buffers
        // glfwSwapBuffers(window);
        //Use this to poll events or wait for events to process
        glfwWaitEvents ();
        // glfwPollEvents();
        
        // check OpenGL error
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << err << std::endl;
        }

    } // Check if the ESC or 'Q' key was pressed or the window was closed
    while( glfwWindowShouldClose(window) == 0 );

    glfwTerminate ();

    return 0;
}