#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// #define ILUT_USE_OPENGL	// This MUST be defined before calling the DevIL headers or we don't get OpenGL functionality
// #include <IL/il.h>
// #include <IL/ilu.h>
// #include <IL/ilut.h>

#include <SOIL.h>
// Load a .BMP file using our custom loader
// GLuint loadBMP_custom(const char * imagepath);

	GLuint loadImage(const char * imagepath);

#endif