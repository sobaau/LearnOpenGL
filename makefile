
ifeq ($(OS),Windows_NT)
	CLIBS=-lglfw3 -lopengl32 -lUser32 -lGdi32 -lShell32
	PRG=/bin/opengl.exe
else
	CLIBS=-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
	PRG=/bin/opengl
endif

CC=g++
CINCLUDE=-I$(CURDIR)/src/include
CLIB=-L$(CURDIR)/src/lib
CFLAGS= $(CINCLUDE) $(CLIB) $(CLIBS) -Wall
SRC=$(CURDIR)/src

learnopengl: main.o glad.o shader.o
	$(CC) main.o shader.o glad.o -o $(CURDIR)$(PRG) $(CFLAGS)

main.o: $(SRC)/main.cpp glad.o shader.o $(SRC)/shader.h
	$(CC) $(SRC)/main.cpp glad.o shader.o $(SRC)/shader.h -c $(CINCLUDE)

shader.o: $(SRC)/shader.cpp $(SRC)/shader.h glad.o
	$(CC) $(SRC)/shader.cpp glad.o -c $(CINCLUDE)
glad.o:
	$(CC) $(SRC)/glad.c -c $(CINCLUDE)

clean:
	rm $(CURDIR)$(PRG)
	rm $(CURDIR)/*.o