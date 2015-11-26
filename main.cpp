//***************************************************************************//
//Name: Mitchell Katz													*****//
//Program: songsearch													*****//
//Assignment: Song Search Database										*****//
//Date: Wednesday, April 30, 2014										*****//
//Class: COMP15															*****//
//***************************************************************************//

#include "songSearch.h"

int main(int argc, char *argv[]) {

	Database songSearch;

	if (argc == 2) {
		songSearch.readIn(argv[1]);
        	songSearch.search();
	}
	else {
		cout << "Usage: songsearch database.txt\n";
	}

	return 0;

}
