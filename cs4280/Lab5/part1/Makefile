PLAT:= $(shell uname)

CC=g++
ifeq ($(PLAT),Darwin)
CFLAGS= -framework OpenGL -framework GLUT -framework Foundation
else
CFLAGS= -IGL -IGLU -lglut
endif
SRCS=CameraDriver

all : $(SRCS)

CameraDriver: CameraDriver.o includes/Camera.o 
	$(CC) $(CFLAGS) -o CameraDriver CameraDriver.o includes/Camera.o

clean:
	rm $(SRCS)
	rm *.o
	rm includes/*.o

includes/header.o: includes/header.h

includes/Camera.o: includes/Camera.h
