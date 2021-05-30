
CC=g++
CINCLUDE=-I/Users/soba/dev/code/opengl/include/ 
CLIB=-L/Users/soba/dev/code/opengl/lib/
CLIBS=-lglfw3 -lglad -framework Cocoa -framework OpenGL -framework IOKit
CFLAGS= $(CINCLUDE) $(CLIB) $(CLIBS)

opengl_test: main.cpp 
	$(CC) main.cpp -o OpenGlTest $(CFLAGS)

clean:
	rm OpenGlTest