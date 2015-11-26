
Name: Mitchell Katz

Program: songsearch

Assignment: Song Search Database

Date: Tuesday, April 29, 2014

Class: COMP15

Purpose:
To make a database of songs where you can search for a word and get the top 10
songs that have the most appearance of that word in the lyrics. The database
should be capabable of scaling to relatively larege sizes. It takes the program
approximately 3.7 seconds to read in a database of 13300 songs on my 2.9 GHz Intel
Core i5 machine, and negligable time to search said database.

Included Files:
main.cpp - contains the main for the program
songSearch.h - the header file. Includes a definition for the Database class
songSearch.cpp - the implementation file for the Database class
hashfunc.h - hash function header file (courtesy of Bob Jenkins)
hashfunc.cpp - hash function implementation file (courtsey of Bob Jenkins)
Makefile - use to compile program
13300Songs.txt - Sample input file

How to Compile:
Use included Makefile. The command "make songsearch" compiles the program.

How to Run:
The command "./songsearch <database>" will run the program

Data Structures:
I have three structs: indexWithFreq which stores the index that a word is in 
as well as the number of appearances in that song, words which has a pointer 
to a vector of indexWithFreq's and a string for the word, and songs which has 
a pointer to a vector of lyrics, a string for the name, and a string for the 
artist. The songs are contained in a vector of songs, and the words are stored 
in a hash table (a dynamic array).

Algorithms:
Read In Song:
When I read in a song, I store the lyrics in the song.lyric vector, then I 
push the song onto the songList vector. After every song, I pass that song to 
storeWords where it hashes every word to wordTable. Collisions are managed 
with a quadratic probe (I have a while loop until it is broken by hashing a 
song or updating a frequency). If a song already exists in the table, I check 
if it exists from the current song. If so, I add one to the frequency. If not, 
I add a new index with a frequency of one. I expand the hash table whenever 
the load factor is greater than 3/5.
Search for Word:
I input the word, and hash the alphaOnly of it, checking the same things as 
when I hash the word originally (is the element empty, does it contain the 
word, or another word). When I find the hash, I call findSong to find the top 
10 songs, which then calls printSong to print out every appearance of the word 
in a given song.

Thanks to Chris Gregg and Bruce Molay for the readin code that I modified and the 
alphaOnly function, and Bob Jenkins for the hash code.
