
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
    view = (View *)glfwGetWindowUserPointer(window);

    // Get mouse location
    double prevxpos = view->prevxpos;
    double prevypos = view->prevypos;
    // printf("prevxpos = %f %d\n",prevxpos,!std::isnan(prevxpos));

    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();

    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // Only want to move if user has clicked the left mouse button
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS && !std::isnan(prevxpos))
    {
        float mouseSpeed = 3.005f;

        #ifdef DEBUG
        printf("during prevxpos = %f prevypos = %f\n",prevxpos,prevypos);
        printf("deltaTime = %f \n",deltaTime);
        #endif

        glm::vec3   camPos = view->camPos;     //!< camera position in world space
        glm::vec3   camAt = view->camAt;      //!< camera look-at point in world space
        glm::vec3   camUp = view->camUp;  
        glm::vec3   tempV;

        #ifdef DEBUG
        printf("before camAt[0] = %f,camAt[1] = %f,camAt[2] = %f\n",
            camAt[0],camAt[1],camAt[2] );

        // printf("before camUp[0] = %f,camUp[1] = %f,camUp[2] = %f\n",
        //     camUp[0],camUp[1],camUp[2] );
        #endif

        glm::vec3 right = glm::normalize(glm::cross( camUp , camAt - camPos));

        #ifdef DEBUG
        printf("right[0] = %f,right[1] = %f,right[2] = %f\n",
            right[0],right[1],right[2] );
        #endif

        float mousedeltax = float(xpos - prevxpos);
        float mousedeltay = float(ypos - prevypos);

        #ifdef DEBUG
        printf("dx = %f dy = %f\n",mousedeltax,mousedeltay );
        #endif
        
        float atLen = glm::length(camAt - camPos);
        // GLfloat yaw = view->yaw;
        // GLfloat pitch = view->pitch;

        GLfloat angle = mousedeltax * mouseSpeed * deltaTime;
        tempV = glm::cos(glm::radians(angle)) * glm::normalize(camAt - camPos) 
                + glm::sin(glm::radians(angle)) * right; 

        // camAt = glm::normalize(camAt - camPos) + right * 1000.0f *  mousedeltax * deltaTime;
        // camAt += right * mousedeltax * mouseSpeed * deltaTime;

        #ifdef DEBUG
                // printf("angle = %f cos rad angle = %f\n",angle,glm::cos(glm::radians(angle)) );
        // printf("middle camAt[0] = %f,camAt[1] = %f,camAt[2] = %f\n",
        //     camAt[0],camAt[1],camAt[2] );
        #endif

        camAt = tempV * atLen + camPos; // * mousespeed


        angle = (-1.0f)*mousedeltay * mouseSpeed * deltaTime;
        right = glm::normalize(glm::cross( camUp , camAt - camPos));
        // pitch += mousedeltay;
        camUp = glm::cos(glm::radians(angle)) * camUp 
                + glm::sin(glm::radians(angle)) * glm::normalize(camAt - camPos);
        camUp = glm::normalize(camUp);
        tempV = glm::normalize(glm::cross( right , camUp));

        // camUp += glm::normalize(camAt - camPos) * mousedeltay * deltaTime; // * mousespeed
        camAt = tempV * atLen + camPos;

        #ifdef DEBUG
            printf("right[0] = %f,right[1] = %f,right[2] = %f\n",
                right[0],right[1],right[2] );
            printf("camAt[0] = %f,camAt[1] = %f,camAt[2] = %f\n",
                view->camAt[0],view->camAt[1],view->camAt[2] );
            printf("camPos[0] = %f,camPos[1] = %f,camPos[2] = %f\n",
                view->camPos[0],view->camPos[1],view->camPos[2] );
            printf("camUp[0] = %f,camUp[1] = %f,camUp[2] = %f\n",
                view->camUp[0],view->camUp[1],view->camUp[2] );
        #endif

        view->camPos = camPos;     //!< camera position in world space
        view->camAt = camAt;      //!< camera look-at point in world space
        view->camUp = camUp;

        view->InitModelViewMatrix ();


        view->needsRedraw = true;
    } 

    view->prevxpos = xpos;
    view->prevypos = ypos;

    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;
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

    GLfloat cameraSpeed = 0.1f;
    GLfloat strafeSpeed = 0.1f;


    if ((action != GLFW_RELEASE) || (mods & (GLFW_MOD_CONTROL|GLFW_MOD_ALT|GLFW_MOD_SUPER))) {
        
        view = (View *)glfwGetWindowUserPointer(window);

        glm::vec3   camPos = view->camPos;     //!< camera position in world space
        glm::vec3   camAt = view->camAt;      //!< camera look-at point in world space
        glm::vec3   camUp = view->camUp;
        glm::vec3   tempV;

        switch (key) {
            case GLFW_KEY_Q:  // 'q' or 'Q' ==> quit
            case GLFW_KEY_ESCAPE: // 'ESC' ==> quit
                glfwSetWindowShouldClose (window, true);
                break;
            case GLFW_KEY_W:
            case GLFW_KEY_UP:
                tempV = (view->camPos - view->camAt)*cameraSpeed;
                view->camAt -= tempV;
                view->camPos -= tempV;
                view->needsRedraw = true;
                view->InitModelViewMatrix ();
            break;
            case GLFW_KEY_S:
            case GLFW_KEY_DOWN:
                tempV = (view->camPos - view->camAt)*cameraSpeed;
                view->camAt += tempV;
                view->camPos += tempV;
                view->needsRedraw = true;
                view->InitModelViewMatrix ();
            break;
            case GLFW_KEY_A:
            case GLFW_KEY_LEFT:
                {
                    glm::vec3 right = glm::normalize(glm::cross( camUp, camAt - camPos));
                    float atLen = glm::length(camAt - camPos);
                    view->camAt += right*strafeSpeed;
                    view->camPos += right*strafeSpeed;
                    view->needsRedraw = true;
                    view->InitModelViewMatrix ();
                    #ifdef DEBUG
                        printf("right[0] = %f,right[1] = %f,right[2] = %f\n",
                            right[0],right[1],right[2] );
                        printf("camAt[0] = %f,camAt[1] = %f,camAt[2] = %f\n",
                            view->camAt[0],view->camAt[1],view->camAt[2] );
                        printf("camPos[0] = %f,camPos[1] = %f,camPos[2] = %f\n",
                            view->camPos[0],view->camPos[1],view->camPos[2] );
                        printf("camUp[0] = %f,camUp[1] = %f,camUp[2] = %f\n",
                            view->camUp[0],view->camUp[1],view->camUp[2] );
                    #endif
                }
            break;
            case GLFW_KEY_D:
            case GLFW_KEY_RIGHT:
                {
                    glm::vec3 right = glm::normalize(glm::cross( camUp, camAt - camPos));
                    float atLen = glm::length(camAt - camPos);
                    view->camAt -= right*strafeSpeed;
                    view->camPos -= right*strafeSpeed;
                    view->needsRedraw = true;
                    view->InitModelViewMatrix ();
                    #ifdef DEBUG
                        printf("right[0] = %f,right[1] = %f,right[2] = %f\n",
                            right[0],right[1],right[2] );
                        printf("camAt[0] = %f,camAt[1] = %f,camAt[2] = %f\n",
                            view->camAt[0],view->camAt[1],view->camAt[2] );
                        printf("camPos[0] = %f,camPos[1] = %f,camPos[2] = %f\n",
                            view->camPos[0],view->camPos[1],view->camPos[2] );
                        printf("camUp[0] = %f,camUp[1] = %f,camUp[2] = %f\n",
                            view->camUp[0],view->camUp[1],view->camUp[2] );
                    #endif
                }
            break;
            case GLFW_KEY_T:
                view->renderer->renderTerrain = !(view->renderer->renderTerrain);
            break;

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