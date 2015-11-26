//***************************************************************************//
//Name: Mitchell Katz													*****//
//Program: songsearch													*****//
//Assignment: Song Search Database										*****//
//Date: Wednesday, April 30, 2014										*****//
//Class: COMP15															*****//
//***************************************************************************//

#ifndef  __songsearch_h__
#define	 __songsearch_h__

#include "hashfunc.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

struct indexWithFreq{
	size_t index;			//the index of the song in songList
	int freq;			//number of appearances in that song 
};

struct words {
	string word;			//the word
	vector<indexWithFreq> *elem;	//pointer to a vector of indexWithFreqs
};

struct songs {
	string name;			//name of the song
	string artist;			//artist of the song
	vector<string> *lyrics;		//pointer to a vector of lyrics
};

class Database {
public:
	Database();
	//constructor

	~Database();
	//destructor

	void readIn(const char * filename);
	//reads in songs

	void search();
	//searches for songs

private:	
	vector<songs> songList;
	//table that should contain all of the songs

	words* wordTable;
	//hash table that contains all of the words

	int wordCap;
	//the number of word the hash table can hold

	int numWords;
	//number of unique words stored in the hash table

	void expandHashTable();
	//expands the hash table and rehashes the values

	void storeWords(vector<string> *lyrics, size_t index);
	//takes in a song and hashes each word into wordTable and
	//stores the given index
	
	void findSong(size_t hash);
	//for a hash element, find the top 10 songs and call printSong

	size_t hashCode(string word, size_t attempt);
	//takes in a word and computes a string for it

	string alphaOnly(string s);
	//strips the non-alphabet/digit characters off of a string

	void printSong(songs *aSong, string word);
	//prints the appearances of the given word in the given song
};

#endif
