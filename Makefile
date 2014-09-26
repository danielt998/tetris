#piece.out: piece.cxx
#	g++ piece.cxx -g -v -o piece.out -lncurses
#for the moment, just including piece.cxx, but should really use headers...
tetris.out: tetris.cpp
	g++ tetris.cpp -g -v -o tetris.out -lncurses
