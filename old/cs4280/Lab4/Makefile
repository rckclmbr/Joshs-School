PLAT:= $(shell uname)

CC=g++
ifeq ($(PLAT),Darwin)
CFLAGS= -framework OpenGL -framework GLUT -framework Foundation
else
CFLAGS= -IGL -IGLU -lglut
endif
SRCS=lab4

all : $(SRCS)

lab4: lab4.o includes/realrect.o includes/intrect.o includes/canvas.o includes/point2.o
	$(CC) $(CFLAGS) -o lab4 lab4.o includes/canvas.o includes/realrect.o includes/intrect.h includes/point2.o

clean:
	rm $(SRCS)
	rm *.o
	rm includes/*.o

includes/header.o: includes/header.h

includes/realrect.o: includes/realrect.h

includes/intrect.o: includes/intrect.h

includes/point2.o: includes/point2.h

includes/canvas.o: includes/canvas.h
