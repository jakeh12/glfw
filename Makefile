all:
	gcc -framework OpenGL -framework Cocoa empty.c -o empty -I/usr/local/include -L/usr/local/lib -lGLEW -lglfw
