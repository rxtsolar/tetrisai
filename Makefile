all:
	g++ display.cpp tetris.cpp pieces.cpp ai.cpp -lglut -lGLU -lGL -o play -g
