/*
This program creates child threads
*/

#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <pthread.h>
#include <iomanip>

using namespace  std;

int** readMatrixFromFile(std::string fileName, int &row, int &col);
int** createMatrix(const int row, const int col);
void parseRowAndColumn(ifstream &input, int &row, int &col);
void parseMatrix(ifstream &input, int** matrix, const int row, const int col);
void printMatrix(int** m, const int row, const int col);

pthread_t *tids;
//Global matrixes
int ** a;
int ** b;
//c matrix will be of dimensions m x r
int ** c;
int n, m, r;

struct rowcol
{
	int row, col;
};

//Prototype thread functions as C functions
extern "C" {
	void *threadMultiplyMatrix(void *args);
}


int main(int argc, char *argv[])
{
	int error;
	int threadIndex = 0;
	int row, col;
	//a matrix m x n
	a = readMatrixFromFile("a1.txt", row, col);
	m = row;
	n = col;
	//b matrix n x r
	b = readMatrixFromFile("b1.txt", row, col);
	r = col;
	if (n != row)
		cout << "matrices wrong dimenstions";
	//c matrix will be of dimensions m x r
	c = createMatrix(m, r);

	tids = new pthread_t[m*r];
	cout << "num of threads:" << m*r;
	printMatrix(c, m, r);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < r; j++)
		{
			rowcol *r = new rowcol;
			r->col = j;
			r->row = i;
			if (pthread_create(&tids[threadIndex], NULL, threadMultiplyMatrix, r) > 0)
			{
				cerr << "pthread_create failure" << endl;
				return 1;
			}
			threadIndex++; 
		}
	}

	/*
	Wait for the threads to terminate
	*/
	for (int i = 0; i < m*r; i++)
	{
		if (error = pthread_join(tids[i], NULL))
		{
			cout << "Failed to join thread: " << error << endl;
			return 1;
		}
	}

	cout << "Parent thread done" << endl;
	printMatrix(c, m, r);

	delete[] tids;
	return 0;
}

//Dynamically allocate matrix with row by col dimensions
//Initialize all values to 0
int** createMatrix(const int row, const int col)
{
	int **matrix;
	matrix = new int*[row];
	for (int i = 0; i < row; i++)
	{
		matrix[i] = new int[col];
		for (int j = 0; j < col; j++)
			matrix[i][j] = 0;
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
	while (input >> num)
	{
		if (col == maxCol)
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


void printMatrix(int** m, const int row, const int col)
{
	//Prints nice 2D array
	for (int i = 0; i <= row; i++)
	{
		//Print horizontal line under column numbers
		if (i == 1)
		{
			for (int k = 0; k <= col; k++)
				cout << "---";
			cout << endl;
		}

		//Print Row Numbers
		if (i == 0)
			cout << setw(2) << internal << " ";
		else
			cout << setw(2) << internal << i;
		cout << "|";

		for (int j = 1; j <= col; j++)
		{
			//Print Columns Numbers
			if (i == 0)
				cout << setw(3) << j;
			else
			{
				//Print values
				if (m[i][j] != -1)
					cout << setw(3) << m[i][j];
				else
					cout << setw(3) << ".";
			}
		}
		cout << endl;
	}
	cout << endl;
}