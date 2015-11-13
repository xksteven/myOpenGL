TARGET = gl

INCLUDE = -I/usr/local/include 
LDFLAGS = -L/usr/local/lib
#Use either glut or glfw
#LIBS = -lglut -lGL -lGLU -lGLEW 
LIBS = -lglfw -lGL -lGLU -lGLEW

all:
	g++ -std=c++11 opengl.cpp -o $(TARGET) $(LDFLAGS) $(LIBS)

clean:
	rm gl
