TARGET = gl

CC = g++

ifdef DEBUG
CFLAGS = -g -Wall -std=c++11 -DDEBUG
else
CFLAGS = -std=c++11
endif
INCLUDE = -I/usr/local/include -I./include/devil-1.7.99/include 
		# -I./include/devil-1.7.99/include/IL
LDFLAGS = -L/usr/local/lib -L./include/devil-1.7.99/lib
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
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LIBS)

clean:
	rm gl
