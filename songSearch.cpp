//***************************************************************************//
//Name: Mitchell Katz													*****//
//Program: songsearch													*****//
//Assignment: Song Search Database										*****//
//Date: Tuesday, April 29, 2014											*****//
//Class: COMP15															*****//
//***************************************************************************//

#include "songSearch.h"

//********CONSTRUCTOR AND DESTRUCTOR********//

//contructor
//initializes variables, creates word table and initializes it to NULL
Database::Database() {
	wordTable = new words[100];
	numWords = 0;
	wordCap = 100;
	for (int i=0; i<wordCap; i++) {
		wordTable[i].word = "";
		wordTable[i].elem = NULL;
	}
}

//destructor
//destroys wordTable
Database::~Database() {
	delete [] wordTable;
}

//************PUBLIC  FUNCTIONS ************//

//args: the file to read in from
//reads in title, artist and lyrics from the file
//pushes lyrics onto a vector
//pushes the song onto songList
//calls storeWords
//returns void
void Database::readIn(const char * filename) {
	ifstream in(filename);			// creates an input stream
	string artist, title, word;
	// -- While more data to read...
	while (!in.eof()) {
		songs aSong;
		// -- First line is the artist
		getline(in, artist);
		if (in.fail()) break;
                aSong.artist = artist;
		// -- Second line is the title
		getline(in, title);
		if (in.fail()) break;
		aSong.name = title;
		// -- Then read all words until we hit the
		// -- special <BREAK> token
		aSong.lyrics = new vector<string>;
		while ( in >> word && word != "<BREAK>" )
			aSong.lyrics->push_back(word);
		// -- Important: skip the newline left behind
		in.ignore();
		songList.push_back(aSong);
		storeWords(aSong.lyrics, songList.size()-1);
	}
}
//inputs a string
//hashes the string
//calls findSong
//returns void
void Database::search() {
	string input;
	cin >> input;	//input a word
	while (input != "<BREAK>") {
		size_t attempt = 0;
		string aWord = alphaOnly(input); //convert to lowercase
		while (true) { //hash the word
			size_t hash = hashCode(aWord, attempt);
			if (wordTable[hash].word == aWord) {
				findSong(hash); //call findSong
				break;
			} else if ((wordTable[hash].word == " ")||
				   (wordTable[hash].word == "")) break;
				//element is empty- word does not exist
			else attempt++; //word not found
		}
		cout << "<END-OF-REPORT>" << endl;
		cin >> input;
	}
}

//************PRIVATE  FUNCTIONS************//

//args: a pointer to a vector of strings (the song lyrics), index of the song
//hashes the word and stores it in the hash table of words
//expands hash table if load factor > 3/5
//returns void
void Database::storeWords(vector<string> *lyrics, size_t index) {
	for (vector<string>::iterator word = lyrics->begin();
	    word != lyrics->end(); word++) {

	    //expand table if load factor>3/5
		if ((wordCap/5)*3 < numWords)
			expandHashTable();

		string aWord = alphaOnly(*word); //convert to lowercase
		size_t attempt = 0;
		while (true) {
			size_t hash =hashCode(aWord, attempt);//element is open
			if ((aWord == "") || (aWord == " "))
				break;

			indexWithFreq aFreq;	//create a new word struct
			aFreq.index = index;
			aFreq.freq = 1;

			//word does not exist in table
			if (wordTable[hash].word == "") {
				numWords++;	//push aFreq onto wordTable
				wordTable[hash].elem = new vector<indexWithFreq>;
				wordTable[hash].word = aWord;
				wordTable[hash].elem->push_back(aFreq);
				break;

			//word exists in table
			} else if (wordTable[hash].word == aWord) {
			    if (wordTable[hash].elem->back().index!=index)
					wordTable[hash].elem->push_back(aFreq);
			    else {		//same song
					indexWithFreq num=wordTable[hash].elem->back();
					num.freq++;	//different song
					wordTable[hash].elem->pop_back();
					wordTable[hash].elem->push_back(num);
			    } break;
			} else
				attempt++;	//different word in index
		}
	}
}

//args: string (the word) and a size_t (the attempt #)
//uses the given hash code, uses attempt to do a quadratic probe
//mods by the size of the hash table
//returns a hash (variable: size_t)
size_t Database::hashCode(string word, size_t attempt) {
	return (((hash_string(word))+(attempt*attempt))%(size_t)wordCap);
}	//hash word, quadratic probe, mod by wordTable size

//args: a string
//converts the string to all lowercase with no symbols
//returns a string
string Database::alphaOnly(string s) {
	ostringstream ss;
        for (size_t i=0; i<s.length(); i++) {
                if (isalnum(s[i]))
                        ss << (char)(tolower(s[i]));
        }
        return ss.str();
}

//no arguments
//expands the hashTable of words by a factor of 3
//returns void
void Database::expandHashTable(){
	wordCap *= 3;				//triple the capacity
	words *temp = new words[wordCap];	//create a new table
	for (int j = 0; j < wordCap; j++) {
		temp[j].elem = NULL;		//initialize table
		temp[j].word = "";
	} for (int i = 0; i < wordCap/3; i++) {
		size_t attempt = 0;
		while (true) {			//rehash elements
			size_t hash = hashCode(wordTable[i].word,attempt);
			//element is open
			if (temp[hash].word == "") {
				temp[hash].word = wordTable[i].word;
				temp[hash].elem = wordTable[i].elem;
				break;
			}
			//element is filled with a different word
			else attempt++;
		}
	}		//delete old table
	delete [] wordTable;
	wordTable = temp;
}

//args: index of a word in the hash table (size_t)
//iterates through a word's lyrics to find the top 10 hits
//calls printSong on the appropriate song
//returns void
void Database::findSong(size_t hash) {
	vector<indexWithFreq> temp;
	//make a temp vector that we can erase elements from
	for(vector<indexWithFreq>::iterator itr=wordTable[hash].elem->begin();
	    itr != wordTable[hash].elem->end(); itr++)
		temp.push_back(*itr);
	for (int i=0; i<10; i++) {    //repeat the following process 10 times
		vector<indexWithFreq>::iterator high = temp.begin();
		for(vector<indexWithFreq>::iterator itr = temp.begin();
	      		itr != temp.end(); itr++){
			//iterate through songs with a given word
				if (itr->freq > high->freq)
					high = itr;
			//if song has the highest frequency of a word,store it
	      	}
	  	if (temp.empty())
	  		return; //print that song

	  	printSong(&songList[high->index], wordTable[hash].word);
	  	temp.erase(high);
	  	//erase pointer to song so it can't be printed again
	}
}

//args: pointer to a song and a word (string)
//iterates through the lyrics and prints the appearances of the word
//returns void
void Database::printSong(songs *aSong, string aWord){
	for (vector<string>::iterator wordItr = aSong->lyrics->begin();
	     wordItr != aSong->lyrics->end(); wordItr++) {
		//iterate through a song's lyrics
		if (alphaOnly(*wordItr) == alphaOnly(aWord)) {
		//if word is the one we are searching for, print out the info
			cout << "Title: "  << aSong->name << endl
	  		     << "Artist: " << aSong->artist << endl
			     << "Context: ";

			//print the context (5 words before, 5 after)
			for (int j = -5; j <= 5; j++) {
				if (wordItr+j >= aSong->lyrics->end()) break;
				if (wordItr+j >= aSong->lyrics->begin())
					cout << *(wordItr+j) << " ";
			}
			cout << endl << endl;
		}
	}
}
