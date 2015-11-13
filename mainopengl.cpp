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
    SetupView(window);


    // Initialize GLEW
    // glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return -1;
    }


    // set up callbacks
    glfwSetWindowRefreshCallback (window, Display);
    glfwSetWindowSizeCallback (window, Reshape);
    glfwSetWindowIconifyCallback (window, Visible);
    glfwSetKeyCallback (window, Key);

    //main loop
    do{
        if(NeedtoRedraw())
        {
            printf("NeedtoRedraw\n");
            Display (window);
        }

        // Swap buffers
        // glfwSwapBuffers(window);
        //Use this to poll events or wait for events to process
        glfwWaitEvents ();
        // glfwPollEvents();


    } // Check if the ESC or 'Q' key was pressed or the window was closed
    while( glfwWindowShouldClose(window) == 0 );

    glfwTerminate ();

    return 0;
}