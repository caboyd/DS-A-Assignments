#include <iostream>
#include <fstream>
#include "PatternMatch.h"

using namespace std;

int main()
{
	testBruteForce();
	testBoyerMoore();
	testKnuthMorrisPratt();

	cout << "\nBrute Force with text.txt and pattern.txt" << endl;
	runBruteForce("text.txt", "pattern.txt");
	cout << "\nBoyer Moore with text.txt and pattern.txt" << endl;
	runBoyerMoore("text.txt", "pattern.txt");
	cout << "\nKnuth Morris Pratt with text.txt and pattern.txt" << endl;
	runKnuthMorrisPratt("text.txt", "pattern.txt");


	return 0;
}


string readFile(std::string fileName)
{
	ifstream input(fileName.c_str());
	string s((std::istreambuf_iterator<char>(input)),
		std::istreambuf_iterator<char>());
	input.close();
	return s;
}

int bruteForce(int startIndex, string text, string pattern)
{
	int m = pattern.length();
	int n = text.length();

	for (int i = startIndex; i <= n - m; i++)
	{
		int j = 0;
		charComparisons++;
		while (j < m && text[i + j] == pattern[j])
		{
			charComparisons++;
			j++;
		}
		if (j == m)
			return i;
	}
	return SUBSTRING_NOT_FOUND;
}

int boyerMoore(int startIndex, string text, string pattern)
{
	if (pattern.length() > text.length())
		return SUBSTRING_NOT_FOUND;
	int n = text.length();
	int m = pattern.length();
	int i = m - 1 + startIndex;
	int j = m - 1;
	do
	{
		charComparisons++;
		if (pattern[j] == text[i])
		{
			if (j == 0)
				return i;
			else
			{
				i--;
				j--;
			}
		} else
		{
			i = i + m - min(j, 1 + last(text[i], pattern));
			j = m - 1;
		}
	} while (i <= n - 1);
	return SUBSTRING_NOT_FOUND;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

int last(char c, string pattern)
{
	int m = pattern.length();
	for (int i = m - 1; i >= 0; i--)
	{
		charComparisons++;
		if (c == pattern[i])
			return i;
	}
	return -1;
}

int knuthMorrisPratt(int startIndex, string text, string pattern)
{
	int m = pattern.length();
	int n = text.length();
	int* failureArray = new int[pattern.length()];
	failure(failureArray, pattern);
	int i = startIndex;
	int j = 0;

	while (i < n)
	{
		charComparisons++;
		if (pattern[j] == text[i])
		{
			if (j == m - 1)
				return i - m + 1;
			i++;
			j++;
		} else if (j < 0)
		{
			j = failureArray[j - 1];
			if (i - j + m > n)
				break;
		} else
		{
			i++;
			if (i + m > n)
				break;
		}
	}
	return SUBSTRING_NOT_FOUND;
}

void failure(int failureArray[], string pattern)
{
	int m = pattern.length();
	int i = 1;
	int j = 0;
	failureArray[0] = 0;
	while (i < m)
	{
		charComparisons++;
		if (pattern[j] == pattern[i])
		{
			failureArray[i] = j + 1;
			i++;
			j++;
		} else if (j > 0)
		{
			j = failureArray[j - 1];
		} else
		{
			failureArray[i] = 0;
			i++;
		}
	}
}

void runBruteForce(string textFileName, string patternFileName, int _totalCharComparisons)
{
	totalCharComparisons = _totalCharComparisons;
	string pattern;
	ifstream input(patternFileName);
	while (getline(input, pattern))
	{
		cout << "Pattern: " << pattern << endl;

		charComparisons = 0;
		string text = readFile(textFileName);
		int index = -1;
		while (index != SUBSTRING_NOT_FOUND)
		{
			index = bruteForce(index + 1, text, pattern);
			printLineAndPosition(index, text);
		}
		cout << "Comparisons: " << charComparisons << endl;
		totalCharComparisons += charComparisons;
	}
	cout << "Total Brute Force comparisons: " << totalCharComparisons << endl << endl;
	input.close();
}

void runBoyerMoore(string textFileName, string patternFileName, int _totalCharComparisons)
{
	//Do boyer Moore 
	totalCharComparisons = _totalCharComparisons;
	cout << "Boyer Moore" << endl;
	string pattern;
	ifstream input(patternFileName);
	while (getline(input, pattern))
	{
		cout << "Pattern: " << pattern << endl;
		charComparisons = 0;
		string text = readFile(textFileName);
		int index = -1;
		while (index != SUBSTRING_NOT_FOUND)
		{
			index = boyerMoore(index + 1, text, pattern);
			printLineAndPosition(index, text);
		}
		cout << "Comparisons: " << charComparisons << endl;
		totalCharComparisons += charComparisons;
	}
	totalCharComparisons += charComparisons;
	cout << "Total Boyer Moor comparisons: " << totalCharComparisons << endl << endl;
	input.close();
}

void runKnuthMorrisPratt(string textFileName, string patternFileName, int _totalCharComparisons)
{
	//Do knuthMorrisPratt
	totalCharComparisons = _totalCharComparisons;
	cout << "Knuth Morris Pratt" << endl;
	string pattern;
	ifstream input(patternFileName);
	while (getline(input, pattern))
	{
		cout << "Pattern: " << pattern << endl;
		charComparisons = 0;
		string text = readFile(textFileName);
		int index = -1;
		while (index != SUBSTRING_NOT_FOUND)
		{
			index = knuthMorrisPratt(index + 1, text, pattern);
			printLineAndPosition(index, text);
		}
		cout << "Comparisons: " << charComparisons << endl;
		totalCharComparisons += charComparisons;
	}
	cout << "Total Knuth Morris Pratt Comparisons: " << totalCharComparisons << endl << endl;
}

void testBruteForce()
{
	totalCharComparisons = 0;
	string pattern;
	ifstream input("proofPattern.txt");
	getline(input, pattern);

	cout << "Brute Force Test" << endl << endl;
	cout << "Pattern: " << pattern << endl;

	cout << "Brute Force Test with No Match" << endl;
	charComparisons = 0;
	singleMatchBruteForce("proofTextNoMatch.txt", pattern);

	cout << "Brute Force Test with Match at Beginning" << endl;
	charComparisons = 0;
	singleMatchBruteForce("proofTextMatchBeginning.txt", pattern);

	cout << "Brute Force Test with Match in Middle" << endl;
	charComparisons = 0;
	singleMatchBruteForce("proofTextMatchMiddle.txt", pattern);

	cout << "Brute Force Test with Match split on two lines" << endl;
	charComparisons = 0;
	singleMatchBruteForce("proofTextMatchMiddleSplitTwoLines.txt", pattern);

	cout << "Brute Force Test with multiple matches" << endl;
	charComparisons = 0;
	runBruteForce("proofTextMatchMultiple.txt", "proofPattern.txt", totalCharComparisons);

	input.close();
}

void testBoyerMoore()
{
	totalCharComparisons = 0;
	string pattern;
	ifstream input("proofPattern.txt");
	getline(input, pattern);

	cout << "Boyer Moore Test" << endl << endl;
	cout << "Pattern: " << pattern << endl;

	cout << "Boyer Moore Test with No Match" << endl;
	charComparisons = 0;
	singleMatchBoyerMoore("proofTextNoMatch.txt", pattern);

	cout << "Boyer Moore Test with Match at Beginning" << endl;
	charComparisons = 0;
	singleMatchBoyerMoore("proofTextMatchBeginning.txt", pattern);

	cout << "Boyer Moore Test with Match in Middle" << endl;
	charComparisons = 0;
	singleMatchBoyerMoore("proofTextMatchMiddle.txt", pattern);

	cout << "Boyer Moore Test with Match split on two lines" << endl;
	charComparisons = 0;
	singleMatchBoyerMoore("proofTextMatchMiddleSplitTwoLines.txt", pattern);

	cout << "Boyer Moore Test with multiple matches" << endl;
	charComparisons = 0;
	runBoyerMoore("proofTextMatchMultiple.txt", "proofPattern.txt", totalCharComparisons);

	input.close();
}

void testKnuthMorrisPratt()
{
	totalCharComparisons = 0;
	string pattern;
	ifstream input("proofPattern.txt");
	getline(input, pattern);

	cout << "Knuth Morris Pratt Test" << endl << endl;
	cout << "Pattern: " << pattern << endl;

	cout << "Knuth Morris Pratt Test with No Match" << endl;
	charComparisons = 0;
	singleMatchKnuthMorrisPratt("proofTextNoMatch.txt", pattern);

	cout << "Knuth Morris Pratt Test with Match at Beginning" << endl;
	charComparisons = 0;
	singleMatchKnuthMorrisPratt("proofTextMatchBeginning.txt", pattern);

	cout << "Knuth Morris Pratt Test with Match in Middle" << endl;
	charComparisons = 0;
	singleMatchKnuthMorrisPratt("proofTextMatchMiddle.txt", pattern);

	cout << "Knuth Morris Pratt Test with Match split on two lines" << endl;
	charComparisons = 0;
	singleMatchKnuthMorrisPratt("proofTextMatchMiddleSplitTwoLines.txt", pattern);

	cout << "Knuth Morris Pratt Test with multiple matches" << endl;
	charComparisons = 0;
	runKnuthMorrisPratt("proofTextMatchMultiple.txt", "proofPattern.txt", totalCharComparisons);

	input.close();
}

void singleMatchBruteForce(string textFileName, string pattern)
{
	charComparisons = 0;
	string text = readFile(textFileName);
	int index = bruteForce(0, text, pattern);
	printLineAndPosition(index, text);
	cout << "Comparisons: " << charComparisons << endl;
	totalCharComparisons += charComparisons;
}

void singleMatchBoyerMoore(string textFileName, string pattern)
{
	charComparisons = 0;
	string text = readFile(textFileName);
	int index = boyerMoore(0, text, pattern);
	printLineAndPosition(index, text);
	cout << "Comparisons: " << charComparisons << endl;
	totalCharComparisons += charComparisons;
}


void singleMatchKnuthMorrisPratt(string textFileName, string pattern)
{
	charComparisons = 0;
	string text = readFile(textFileName);
	int index = knuthMorrisPratt(0, text, pattern);
	printLineAndPosition(index, text);
	cout << "Comparisons: " << charComparisons << endl;
	totalCharComparisons += charComparisons;
}

int getLineNumberAtIndex(int& index, string text)
{
	int lineCount = 1;
	int positionInLine = 0;
	for (int i = 0; i < index; i++)
	{
		positionInLine++;
		if (text[i] == '\n')
		{
			lineCount++;
			positionInLine = 0;
		}
	}
	index = positionInLine;
	return lineCount;
}


void printLineAndPosition(int index, string text)
{
	if (index != SUBSTRING_NOT_FOUND)
	{
		int pos = index;
		int line = getLineNumberAtIndex(pos, text);
		cout << "Pattern found at line: " << line << " position: " << pos << endl;
	}
}
