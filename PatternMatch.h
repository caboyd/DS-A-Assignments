#pragma once
#include <string>

const int SUBSTRING_NOT_FOUND = -99;
int charComparisons;
int totalCharComparisons;

//Read a while fil and return it as a tring
std::string readFile(std::string fileName);

/*	Perform the named algorimth starting at startIndex position
*	in text and serching for a match with pattern
*	Return SUBSTRING_NOT_FOUND if not found
*/
int bruteForce(int startIndex, std::string text, std::string pattern);
int boyerMoore(int startIndex, std::string text, std::string pattern);
int knuthMorrisPratt(int startIndex, std::string text, std::string pattern);

//Return min of two ints
int min(int a, int b);

//Returns the index in pattern for the last occurence of c
//return -1 if not found
int last(char c, std::string pattern);

//Generates the failure array for Knuth Morris Pratt algorithm
void failure(int failureArray[], std::string pattern);

/*	Reads a file given by textFileName and reads all patterns one line at a time
*	given by patternFileName. Performs the named algorithm with each pattern
*	until agaisnt the full text string. Prints out the line number and position in the line
*	for each time the pattern is found. Prints the total comparisons for each pattern and total
*	comparisons for all patterns in the text.
**/
void runBruteForce(std::string textFileName, std::string patternFileName, int _totalCharComparisons = 0);
void runBoyerMoore(std::string textFileName, std::string patternFileName, int _totalCharComparisons = 0);
void runKnuthMorrisPratt(std::string textFileName, std::string patternFileName, int _totalCharComparisons = 0);

//Runs the tests for different file examples against a single pattern
void testBruteForce();
void testBoyerMoore();
void testKnuthMorrisPratt();

//Matches a pattern only once agaisnt a string read from textFileName
void singleMatchBruteForce(std::string textFileName, std::string pattern);
void singleMatchBoyerMoore(std::string textFileName, std::string pattern);
void singleMatchKnuthMorrisPratt(std::string textFileName, std::string pattern);

//Returns the line number an index in text is found at
//Updates the index to be the index at that specific line in the text
int getLineNumberAtIndex(int& index, std::string text);

//Prints the line and position an index is found at in text
void printLineAndPosition(int index, std::string text);
