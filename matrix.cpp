/*
This program creates child threads
*/

#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>

using namespace  std;

int** readMatrixFromFile(std::string fileName, int &row, int &col);
void parseRowAndColumn(ifstream &input, int &row, int &col);
void parseMatrix(ifstream &input, int** matrix, const int row, const int col);
int ** createMatrix(const int row, const int col);

int ** a;
int ** b;
int ** c;
//c matrix will be of dimensions m x r
int m,r;

//Prototype thread functions as C functions
extern "C" {
	void *threadout(void *args);
}


int main(int argc, char *argv[])
{
	int row, col;
	//a matrix m x n
	a = readMatrixFromFile("a1.txt", row ,col);
	m = row;
	//b matrix n x r
	b = readMatrixFromFile("a2.txt", row, col);
	r = col;
	//c matrix will be of dimensions m x r
	c = createMatrix(m, r);

	return 0;
}

//Dynamically allocate matrix with row by col dimensions
//Initialize all values to 0
int** createMatrix(const int row, const int col)
{
	int **matrix;
	matrix = new int*[row];
	for(int i = 0; i < row; i++)
	{
		matrix[i] = new int[col];
		for(int j = 0;j < col; j++)
		{
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

int** readMatrixFromFile(string fileName, int &row, int &col)
{
	ifstream input(fileName.c_str());
	string s;
	int ** matrix;
	//get row and column from file
	parseRowAndColumn(input, row, col);
	matrix = createMatrix(row, col);
	//Fill matrix with values in file
	parseMatrix(input, matrix, row, col);
	return matrix;
}

void parseMatrix(ifstream &input, int** matrix, const int maxRow, const int maxCol)
{
	int num;
	int row = 0;
	int col = 0;
	//Read in values in row order
	while(input >> num)
	{
		if(col == maxCol)
		{
			row++;
			col = 0;
		}
		matrix[row][col] = num;
		col++;
	}
}


void parseRowAndColumn(ifstream &input, int &row, int &col)
{
	//string to hold row and col with extra junk
	string srow, scol;
	//junk the first line
	getline(input, srow);
	getline(input, srow);
	getline(input, scol);
	//get the numbers at the beginning of the string
	std::istringstream iss(srow);
	iss >> row;
	iss.str(scol);
	iss >> col;
}