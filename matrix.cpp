/*
This program creates child threads
*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <iomanip>

using namespace  std;

int** readMatrixFromFile(std::string fileName, int &row, int &col);
int** createMatrix(const int row, const int col);
void parseRowAndColumn(ifstream &input, int &row, int &col);
void parseMatrix(ifstream &input, int** matrix, const int row, const int col);
void printMatrix(int** m, const int row, const int col);
int multiplyMatrixFiles(std::string file1, std::string file2);
int evidence(std::string file1, std::string file2);

pthread_t *tids;
//Cout output lock
pthread_mutex_t output_lock;

//Global matrixes
int ** a;
int ** b;
//c matrix will be of dimensions m x r
int ** c;
int n, m, r;

struct RowCol
{
	int row, col;
};

//Prototype thread functions as C functions
extern "C" {
	void *threadMultiplyMatrix(void *args);
	void *verboseThreadMultiplyMatrix(void *args);
}


int main(int argc, char *argv[])
{

	if (evidence("a1.txt", "b1.txt") > 0)
		return -1;
	if (multiplyMatrixFiles("a2.txt", "b2.txt") > 0)
		return -1;
	if (multiplyMatrixFiles("a3.txt", "b3.txt") > 0)
		return -1;

	return 0;
}

int multiplyMatrixFiles(std::string file1, std::string file2)
{
	int threadIndex = 0;
	int row, col;
	//a matrix m x n
	a = readMatrixFromFile(file1, row, col);
	m = row;
	n = col;
	//b matrix n x r
	b = readMatrixFromFile(file2, row, col);
	r = col;
	if (n != row)
		cout << "matrices wrong dimenstions";
	//c matrix will be of dimensions m x r
	c = createMatrix(m, r);

	tids = new pthread_t[m*r];
	cout << "num of threads:" << m*r << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < r; j++)
		{
			RowCol *rc = new RowCol;
			rc->col = j;
			rc->row = i;
			if (pthread_create(&tids[threadIndex], NULL, threadMultiplyMatrix, rc) > 0)
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
		if (pthread_join(tids[i], NULL) > 0)
		{
			cerr << "pthread_join failure" << endl;
			return 1;
		}
	}

	cout << "Parent thread done" << endl;
	cout << "Matrix C" << endl;
	printMatrix(c, m, r);

	delete[] tids;
	return 0;
}

int evidence(std::string file1, std::string file2)
{
	int threadIndex = 0;
	int row, col;
	//a matrix m x n
	a = readMatrixFromFile(file1, row, col);
	cout << "Matrix " << file1 << endl;
	printMatrix(a, row, col);
	m = row;
	n = col;
	//b matrix n x r
	b = readMatrixFromFile(file2, row, col);
	cout << "Matrix " << file2 << endl;
	printMatrix(b, row, col);
	r = col;
	if (n != row)
		cout << "matrices wrong dimenstions";
	//c matrix will be of dimensions m x r
	c = createMatrix(m, r);
	cout << "Matrix C" << endl;
	printMatrix(c, m, r);

	tids = new pthread_t[m*r];
	cout << "num of threads:" << m*r << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < r; j++)
		{
			RowCol *rc = new RowCol;
			rc->col = j;
			rc->row = i;
			if (pthread_create(&tids[threadIndex], NULL, verboseThreadMultiplyMatrix, rc) > 0)
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
		if (pthread_join(tids[i], NULL) > 0)
		{
			cerr << "pthread_join failure" << endl;
			return 1;
		}
	}

	cout << "Parent thread done" << endl;
	cout << "Matrix C" << endl;
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
	const int WIDTH_PER_COLUMN = 6;
	for (int i = -1; i < row; i++)
	{
		//Print horizontal line under column numbers
		if (i == 0)
		{
			for (int k = 0; k <= col; k++)
				cout << setfill('-') << setw(WIDTH_PER_COLUMN) << "-";
			cout << setfill(' ');
			cout << endl;
		}

		//Print Row Numbers
		if (i == -1)
			cout << setw(2) << internal << " ";
		else
			cout << setw(2) << internal << i + 1;
		cout << "|";

		for (int j = 0; j < col; j++)
		{
			//Print Columns Numbers
			if (i == -1)
				cout << setw(WIDTH_PER_COLUMN) << j + 1;
			else
			{
				//Print values
				cout << setw(WIDTH_PER_COLUMN) << m[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}