/*

	Copyright 2010 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Tutorial 01 - Create a window
*/

#include <stdio.h>

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h> //The extension wrangler

//Include GLFW or freeglut they both provide the same functionality
// Include GLFW
// #include <GL/glfw.h>
#include <GL/freeglut.h>

// Include GLM
#include <glm/glm.hpp> //matrix and vec library
// using namespace glm;

GLuint VBO;
GLuint VertexArrayID;

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // glDrawArrays(GL_POINTS, 0, 1);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}

static void InitializeGlutCallbacks()
{
    glutDisplayFunc(RenderSceneCB);
}

static void CreateVertexBuffer()
{
    // An array of 3 vectors which represents 3 vertices

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // glm::vec3 g_vertex_buffer_data[] = {
    //     glm::vec3(-1.0f, -1.0f, 0.0f),
    //     glm::vec3(1.0f, -1.0f, 0.0f),
    //     glm::vec3(0.0f,  1.0f, 0.0f),
    // };

    // glm::vec3 g_vertex_buffer_data[1]; 
    // g_vertex_buffer_data[0] = glm::vec3(-1.0f, -1.0f, 0.0f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Steven's OpenGL");

    InitializeGlutCallbacks();

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return -1;
    }

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    CreateVertexBuffer();

    glutMainLoop();
    
    return 0;
}