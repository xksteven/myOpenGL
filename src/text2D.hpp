#ifndef TEXT2D_HPP
#define TEXT2D_HPP

#include <vector>
#include <cstring>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.hpp"
#include "texture.hpp"

void initText2D(const char * texturePath);
void printText2D(const char * text, int x, int y, int size);
void cleanupText2D();

#endif