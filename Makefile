TARGET = gl

CC = g++

ifdef DEBUG
CFLAGS = -g -Wall -std=c++11 -DDEBUG
else
CFLAGS = -std=c++11
endif
INCLUDE = -I/usr/local/include 
LDFLAGS = -L/usr/local/lib
#Use either glut or glfw
#LIBS = -lglut -lGL -lGLU -lGLEW 

ifeq ($(shell uname),Darwin)
    LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglfw -lGL -lGLEW
endif

#OBJS = ./src/MainOpengl.cpp ./src/Shader.cpp \
#	./src/WindowCallbacks.cpp ./src/View.cpp

OBJS = ./src/*.cpp

all:
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)

clean:
	rm gl
