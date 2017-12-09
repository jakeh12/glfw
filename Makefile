all:
	gcc -Wall -framework OpenGL -framework Cocoa utils.c matrix.c draw.c camera.c main.c -o demo -I/usr/local/include -L/usr/local/lib -lGLEW -lglfw
