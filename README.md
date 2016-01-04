# myOpenGL
This is my work towards creating a frame work for future use in working with OpenGL 

Tested on Ubuntu 15.10

Dependencies

###Ubuntu 

Requires glfw3, glm, g++, glew, make

One can install on Ubuntu with the following on the command line:

sudo apt-get install make g++ libglfw3-dev libglm-dev glew1.5-dev

run make -e DEBUG=1 for debugging mode

To install run:

make includes      <- This only needs to be run once

make

##To Do

- Test on Mac OSX
- Lighting
- Shadow Mapping + Normal Mapping
- Mesh and model class
- Mesh class will contain vertex, texture, index, and normal buffers
- Model class will contain the new matrix to move the meshes around
- Keyboard and mouse controls 
- Reading in input files to make it more easily configured
- Finally Deferred Rendering
