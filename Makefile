#piece.out: piece.cxx
#	g++ piece.cxx -g -v -o piece.out -lncurses
tetris.out: tetris.cpp
	g++ tetris.cpp piece.cxx -g -v -o  tetris.out -lncurses
