TARGET = gl

CC = g++

CURR_DIR = $(shell pwd)

ifdef DEBUG
CFLAGS = -g -Wall -std=c++11 -DDEBUG
else
CFLAGS = -std=c++11
endif
INCLUDE = -I/usr/local/include \
		-I$(CURR_DIR)/include/devil-1.7.99/build/include
#		-I$(CURR_DIR)/include/devil-1.7.99/include 
#		-I$(CURR_DIR)/include/devil-1.7.99/build/include/IL
LDFLAGS = -L/usr/local/lib \
		-L$(CURR_DIR)/include/devil-1.7.99/build/lib 
#		-L$(CURR_DIR)/include/devil-1.7.99/lib 
#Use either glut or glfw
#LIBS = -lglut -lGL -lGLU -lGLEW 

ifeq ($(shell uname),Darwin)
    LIBS = -lglfw -framework OpenGL -framework Foundation
else
	LIBS = -lglfw -lGL -lGLEW
	#DEVIL_LIBS = -l:libIL.so -l:libILU.so -l:libILUT.so
	DEVIL_LIBS = -lIL -lILU -lILUT
	# Also required adding devil-1.7.99/build/lib to LD_LIB_PATH OR to rpath as below
	LINKER = -Wl,-rpath $(CURR_DIR)/include/devil-1.7.99/build/lib

endif



OBJS = ./src/*.cpp

all: 
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(INCLUDE) $(LDFLAGS) $(LIBS) \
	$(DEVIL_LIBS) $(LINKER)

devil:
	cd  ./include/devil-1.7.99/ ; mkdir -p build ; ./configure --enable-ILUT --enable-ILU --prefix=$(CURR_DIR)/include/devil-1.7.99/build ; \
	make ; \
	make install ; \
	cd ../.. ; 

clean:
	rm gl

