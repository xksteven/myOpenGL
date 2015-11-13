TARGET = gl

ifdef DEBUG
CFLAGS = -g -Wall -std=c++11
else
CFLAGS = -std=c++11
endif
INCLUDE = -I/usr/local/include 
LDFLAGS = -L/usr/local/lib
#Use either glut or glfw
#LIBS = -lglut -lGL -lGLU -lGLEW 
LIBS = -lglfw -lGL -lGLEW
OBJS = MainOpengl.cpp Shader.cpp WindowCallbacks.cpp View.cpp

all:
	g++ $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)

clean:
	rm gl
