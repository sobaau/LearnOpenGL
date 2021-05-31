
ifeq ($(OS),Windows_NT)
	CLIBS=-lglfw3 -lopengl32 -lUser32 -lGdi32 -lShell32
else
	CLIBS=-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif

CC=g++
CINCLUDE=-I$(CURDIR)/src/include
CLIB=-L$(CURDIR)/src/lib
CFLAGS= $(CINCLUDE) $(CLIB) $(CLIBS) -Wall
SRC=$(CURDIR)/src

learnopengl: $(SRC)/main.cpp $(SRC)/glad.c
	$(CC) $(SRC)/main.cpp $(SRC)/glad.c -o $(CURDIR)/bin/opengl $(CFLAGS)

clean:
