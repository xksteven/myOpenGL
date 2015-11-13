#ifndef __WINDOWCALLBACKS_HPP__
#define __WINDOWCALLBACKS_HPP__

#include "View.hpp"
#include <iostream>
#include <stdio.h>

// View* SetupView(GLFWwindow *window);
void SetupView(GLFWwindow *window);
bool NeedtoRedraw();
void SetViewport (GLFWwindow *window);
void Error (int err, const char *msg);
void Display (GLFWwindow *window);
void Reshape (GLFWwindow *window, int wid, int ht);
void Key (GLFWwindow *window, int key, int scancode, int action, int mods);
void Visible (GLFWwindow *window, int state);


#endif