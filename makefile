
ifeq ($(OS),Windows_NT)
	CLIBS=-lglfw3 -lopengl32 -lUser32 -lGdi32 -lShell32
else
	CLIBS=-lglfw3 -lglad -framework Cocoa -framework OpenGL -framework IOKit
endif

CC=g++
CINCLUDE=-I$(CURDIR)/include
CLIB=-L$(CURDIR)/lib
CFLAGS= $(CINCLUDE) $(CLIB) $(CLIBS) -Wall

learnopengl: main.cpp glad.c
	$(CC) main.cpp glad.c -o $(CURDIR)/bin/opengl $(CFLAGS)

clean:
