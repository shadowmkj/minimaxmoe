run: build
	./main

build:
	cc -o main main.c ai.c engine.c -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib \
		-framework CoreVideo -framework IOKit -framework Cocoa \
		-framework GLUT -framework OpenGL


