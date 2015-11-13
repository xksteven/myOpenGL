
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
    // view->InitProjMatrix ();




} /* end of Reshape */
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