//
// read_lyrics.cpp
//
//   An example of Code to read in song data from a specified file.
//   You may use this code in your project.
//   
//   Note0: You do not have to use this method.  You can read in
//   the data using another outline, but this is a workable version.
//
//   Note1: This does not keep track of the line number in the song
//   Note2: You have to add code to process/store the data as it is read
//   Note3: You are free to change the parameters for this function or
//          use the logic in any other way you please.
//   Code written by Chris Gregg and Bruce Molay

#include <iostream>
#include <fstream>

using namespace std;

//
// read_lyics 
//   purp: read in song data from a disk file
//   args: the name of the file, bool to ask for progress status
//   rets: nothing
//   does: calls a function each time a word is found
//
void read_lyrics(char * filename, bool show_progress)
{
        ifstream in(filename);			// creates an input stream
        int song_count = 0;			// for progress indicator
	string artist, title, word;		// data from the file

	// -- While more data to read...
	while ( ! in.eof() ) 
	{
		// -- First line is the artist
		getline(in, artist);
		if (in.fail()) break;

		// -- Second line is the title
		getline(in, title);
		if (in.fail()) break;

		if ( show_progress )
		{
			song_count++;
			if (song_count % 10000 == 0) {
				cout << "At "       << song_count << 
					" Artist: " << artist     << 
					" Title:"   << title << endl;
			}
		}
		// -- Then read all words until we hit the 
		// -- special <BREAK> token
		while ( in >> word && word != "<BREAK>" ){
			//
			// -- Found a word
		}
		// -- Important: skip the newline left behind
		in.ignore();
	}
}
