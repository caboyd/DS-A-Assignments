#pragma once
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <cfloat>
#include <chrono>
#include <thread>
#include <string>

using namespace std;

const int SPACE_WIDTH = 100;
const int SPACE_HEIGHT = 40;
const int MAX_BOMBS_PER_DROP = 10;
const int SLEEP_DELAY = 75000;

struct Point
{
	int x;
	int y;
};

struct ClosePair
{
	Point p1;
	Point p2;
};

void Initialize(char space[][SPACE_WIDTH + 1]);
void PrintUpperBorder();
void MoveSpaceShips(char space[][SPACE_WIDTH + 1], int& bombsDestroyed);
void MoveBombs(char space[][SPACE_WIDTH + 1], int& spaceShipsDestroyed);
void ReleaseSpaceShip(char space[][SPACE_WIDTH + 1], int iterations, int& bombsDestroyed);
void ReleaseBombs(char space[][SPACE_WIDTH + 1], int iterations, int& spaceShipsDestroyed);
bool ContinueAttack(char space[][SPACE_WIDTH + 1], int& pointCoint);
void PrintLowerBorder();
void DetectCollisions(int iterations, int pointCount, char space[][SPACE_WIDTH + 1]);
void Pause(int argc, int bombsDestroyed, int spaceShipsDestroyed, int& iterations);
void PrintStats(int bombsDestroyed, int spaceShipsDestroyed);
