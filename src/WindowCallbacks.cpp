
#include "WindowCallbacks.hpp"

View *view;

void SetupView(GLFWwindow *window)
{

	view = new View(window,800,600);
    view->InitRenderers();
    view->InitModelViewMatrix();
    view->InitProjMatrix();

    // return view;
}

bool NeedtoRedraw()
{
    return view->needsRedraw;
}

void SetViewport (GLFWwindow *window)
{
    int fbWidth, fbHeight;
    glfwGetFramebufferSize (window, &fbWidth, &fbHeight);
    glViewport(0, 0 , fbWidth, fbHeight);

}

void Error (int err, const char *msg)
{
    std::cerr << "[GLFW ERROR " << err << "] " << msg << std::endl;
}

/*! \brief Run the simulation and then redraw the animation.
 */
void Display (GLFWwindow *window)
{
    view = (View *)glfwGetWindowUserPointer(window);

  /* avoid drawing when we are invisible */
    if (! view->windowVisibility)
    return;


    view->Render();
    glfwSwapBuffers (window);


    view->needsRedraw = false;

} /* end of Display */

/*! \brief Window resize callback.
 *  \param wid the new width of the window.
 *  \param ht the new height of the window. 
 */
void Reshape (GLFWwindow *window, int windowWidth, int windowHeight)
{
    view = (View *)glfwGetWindowUserPointer(window);

    view->windowWidth = windowWidth;
    view->windowHeight = windowHeight;

  /* set the viewport */
    SetViewport (window);

  /* recompute the projection matrix */
    view->InitProjMatrix ();




} /* end of Reshape */

void cursor_Pos_Callback(GLFWwindow* window, double xpos, double ypos)
{

    // Get mouse location
    double prevxpos = view->prevxpos;
    double prevypos = view->prevypos;
    // printf("prevxpos = %f %d\n",prevxpos,!std::isnan(prevxpos));

    // Only want to move if user has clicked the left mouse button
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS && !std::isnan(prevxpos))
    {
        float mouseSpeed = 0.005f;

        // glfwGetTime is called only once, the first time this function is called
        static double lastTime = glfwGetTime();

        // Compute time difference between current and last frame
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime)*1000;

        printf("during prevxpos = %f prevypos = %f\n",prevxpos,prevypos);
        printf("deltaTime = %f \n",deltaTime);


        glm::vec3   camPos = view->camPos;     //!< camera position in world space
        glm::vec3   camAt = view->camAt;      //!< camera look-at point in world space
        glm::vec3   camUp = view->camUp;  

        printf("before camAt[0] = %f,camAt[1] = %f,camAt[2] = %f\n",
            camAt[0],camAt[1],camAt[2] );

        printf("before camUp[0] = %f,camUp[1] = %f,camUp[2] = %f\n",
            camUp[0],camUp[1],camUp[2] );

        glm::vec3 right = glm::normalize(glm::cross( camPos - camUp, camPos - camAt ));

        printf("right[0] = %f,right[1] = %f,right[2] = %f\n",
            right[0],right[1],right[2] );

        float mousedeltax = float(xpos - prevxpos);
        float mousedeltay = float(ypos - prevypos);
        printf("dx = %f dy = %f\n",mousedeltax,mousedeltay );
        float atLen = glm::length(camPos - camAt);
        camAt += right * mousedeltax * mouseSpeed;
        printf("middle camAt[0] = %f,camAt[1] = %f,camAt[2] = %f\n",
            camAt[0],camAt[1],camAt[2] );
        camAt = glm::normalize(camPos - camAt) * atLen + camPos;
        printf("after camAt[0] = %f,camAt[1] = %f,camAt[2] = %f\n",
            camAt[0],camAt[1],camAt[2] );

        camUp += glm::normalize(camPos - camAt) * mousedeltay * mouseSpeed;
        camUp = glm::normalize(camUp);

        printf("camUp[0] = %f,camUp[1] = %f,camUp[2] = %f\n",
            camUp[0],camUp[1],camUp[2] );

        // view->modelViewMat = glm::lookAt (
        // camPos,
        // camAt,
        // camUp);
        view->InitModelViewMatrix ();

        view->camPos = camPos;     //!< camera position in world space
        view->camAt = camAt;      //!< camera look-at point in world space
        view->camUp = camUp;

        view->needsRedraw = true;
        // Reset mouse positions
        // view->prevxpos = std::nan("1");
        // view->prevypos = std::nan("1");

        // For the next frame, the "last time" will be "now"
        lastTime = currentTime;
    } 
    else if (state != GLFW_PRESS)
    {
        view->prevxpos = std::nan("1");
        view->prevypos = std::nan("1");
    }
    else 
    {
        view->prevxpos = xpos;
        view->prevypos = ypos;
    }
}



/*! \brief Keyboard-event callback.
 *  \param window The window receiving the event
 *  \param key key token
 *  \param scancode unique scancode for physical key (ignored)
 *  \param action PRESS, REPEAT, or RELEASE
 *  \param mods modifier bits
 */
void Key (GLFWwindow *window, int key, int scancode, int action, int mods)
{
  // ignore releases, control keys, command keys, etc.

    // GLfloat cameraSpeed = 3.0f;

    if ((action != GLFW_RELEASE) || (mods & (GLFW_MOD_CONTROL|GLFW_MOD_ALT|GLFW_MOD_SUPER))) {
        
        view = (View *)glfwGetWindowUserPointer(window);

        switch (key) {
            case GLFW_KEY_Q:  // 'q' or 'Q' ==> quit
            case GLFW_KEY_ESCAPE: // 'ESC' ==> quit
                glfwSetWindowShouldClose (window, true);
                break;
            case GLFW_KEY_UP:
                view->camPos += (view->camPos - view->camAt)*0.1f;
                view->needsRedraw = true;
                view->InitModelViewMatrix ();
            break;
            case GLFW_KEY_DOWN:
                view->camPos -= (view->camPos - view->camAt)*0.1f;
                view->needsRedraw = true;
                view->InitModelViewMatrix ();
            break;
            // case GLFW_KEY_LEFT:
            //     view->angle = view->angle - cameraSpeed;
            //     view->MoveAround(); 
            //     view->needsRedraw = true;
            // break;
            // case GLFW_KEY_RIGHT:
            //     view->angle = view->angle + cameraSpeed;
            //     view->MoveAround(); 
            //     view->needsRedraw = true;
            // break;

            default: // ignore all other keys
                return;
        }
    }
} /* end of Key */

/*! \brief Visibility-change callback: sets the visibility state of the view.
 *  \param state the current state of the window; GL_TRUE for iconified, GL_FALSE otherwise.
 */
void Visible (GLFWwindow *window, int state)
{
    view = (View *)glfwGetWindowUserPointer(window);

    view->windowVisibility = (state == GL_FALSE);

} /* end of Visible */