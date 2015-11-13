TARGET = gl

INCLUDE = -I/usr/local/include 
LDFLAGS = -L/usr/local/lib
#Use either glut or glfw
#LIBS = -lglut -lGL -lGLU -lGLEW 
LIBS = -lglfw -lGL -lGLU -lGLEW
OBJS = mainopengl.cpp shader.cpp WindowCallbacks.cpp View.cpp

all:
	g++ -std=c++11 $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)

clean:
	rm gl
