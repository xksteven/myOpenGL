TARGET = gl

CC = g++

CURR_DIR = $(shell pwd)

#make -e DEBUG=1
ifdef DEBUG
CFLAGS = -g -Wall -std=c++11 -DDEBUG
else
CFLAGS = -std=c++11
endif

INCLUDE = -I/usr/local/include 
ifdef devil
INCLUDE += -I$(CURR_DIR)/include/devil-1.7.99/build/include \
		-I$(CURR_DIR)/include/devil-1.7.99/include \
		-I$(CURR_DIR)/include/devil-1.7.99/build/include/IL 
else
INCLUDE += -I$(CURR_DIR)/include/SimpleOpenGLImageLibrary/src
endif

LDFLAGS = -L/usr/local/lib 

ifdef devil
LDFLAGS += -L$(CURR_DIR)/include/devil-1.7.99/build/lib \
	-L$(CURR_DIR)/include/devil-1.7.99/lib 
else 
LDFLAGS += -L$(CURR_DIR)/include/SimpleOpenGLImageLibrary/lib
endif

#Use either glut or glfw currently built with glfw
#LIBS = -lglut -lGL -lGLU -lGLEW 

ifeq ($(shell uname),Darwin)
    LIBS = -lglfw -framework OpenGL -framework Foundation
else
	LIBS = -lglfw -lGL -lGLEW
endif

ifdef devil
	IMAGE_LOADER = -lIL -lILU -lILUT
	# Also required adding devil-1.7.99/build/lib to LD_LIB_PATH OR to rpath as below
	LINKER = -Wl,-rpath $(CURR_DIR)/include/devil-1.7.99/build/lib
else
	IMAGE_LOADER = -lSOIL
	LINKER = -Wl,-rpath $(CURR_DIR)/include/SimpleOpenGLImageLibrary/lib
endif






OBJS = ./src/*.cpp

all: 
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) \
	$(INCLUDE) $(LDFLAGS) $(LIBS) \
	$(IMAGE_LOADER) $(LINKER)


devil:
	cd  ./include/devil-1.7.99/ ; mkdir -p build ; ./configure --enable-ILUT --enable-ILU --prefix=$(CURR_DIR)/include/devil-1.7.99/build ; \
	make ; \
	make install ; \
	cd ../.. ; 

soil:
	cd ./include/SimpleOpenGLImageLibrary/projects/makefile ; \
	mkdir -p obj ; \
	make ; \
	sudo make install ; \
	cd ../../../../ 

clean:
	rm gl

