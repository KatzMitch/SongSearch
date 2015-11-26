#
# Makefile for SongSearch
#

CXX = clang++
FLAGS = -Wall -Wextra -Wconversion -g

songsearch: main.cpp songSearch.cpp songSearch.h hashfunc.h hashfunc.cpp
	${CXX} ${FLAGS} -o songsearch main.cpp songSearch.cpp hashfunc.cpp

clean:
	rm -f songsearch
