#include "spacePanic.h"

int printFlag;
int waitFlag;

int main(int argc, char* argv[])
{
	char space[SPACE_HEIGHT + 1][SPACE_WIDTH + 1];
	int iterations = 0;
	bool attackFinished;
	int bombsDestroyed = 0;
	int spaceShipsDestroyed = 0;
	int pointCount;
	printFlag = 1;
	waitFlag = 1;

	if (argc == 2)
	{
		if (strcmp(argv[1], "-q") == 0)
		{
			//In quiety mode don't wait or print
			printFlag = 0;
			waitFlag = 0;
		} else if (strcmp(argv[1], "-a") == 0)
		{
			//In auto mode don't wait
			waitFlag = 0;
		} else
		{
			cout << "ERROR: invalid command line argument" << endl;
			exit(1);
		}
	} else if (argc > 2)
	{
		cout << "ERROR: too many command line arguments" << endl;
		exit(1);
	}


	srand(time(0));

	Initialize(space);
	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	while (1)
	{
		if (printFlag)
		{
			system("cls"); // Clears the screen.
			PrintUpperBorder();
		}
		MoveSpaceShips(space, bombsDestroyed);
		MoveBombs(space, spaceShipsDestroyed);
		ReleaseSpaceShip(space, iterations, bombsDestroyed);
		ReleaseBombs(space, iterations, spaceShipsDestroyed);
		attackFinished = ContinueAttack(space, pointCount);
		if (printFlag)
			PrintLowerBorder();
		if (attackFinished)
		{
			break;
		}
		DetectCollisions(iterations, pointCount, space);
		Pause(argc, bombsDestroyed, spaceShipsDestroyed, iterations);
	}
	end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;

	PrintStats(bombsDestroyed, spaceShipsDestroyed);
	cout << "Total time to execute was " << elapsed_seconds.count() << "s\n";
	return 0;
}

void Initialize(char space[][SPACE_WIDTH + 1])
{
	int i;
	int j;

	for (i = 1; i <= SPACE_HEIGHT; i++)
	{
		space[i][0] = '>';
	}

	for (j = 1; j <= SPACE_WIDTH; j++)
	{
		space[0][j] = '*';
	}

	for (i = 1; i <= SPACE_HEIGHT; i++)
	{
		for (j = 1; j <= SPACE_WIDTH; j++)
		{
			space[i][j] = ' ';
		}
	}

	return;
}

void PrintUpperBorder()
{
	cout << setw(SPACE_WIDTH + 2) << setfill('-') << "-" << endl;

	return;
}

void MoveSpaceShips(char space[][SPACE_WIDTH + 1], int& bombsDestroyed)
{
	int i;
	int j;

	// Space ship has made it across.
	for (i = 1; i <= SPACE_HEIGHT; i++)
	{
		if (space[i][SPACE_WIDTH] == '>' || space[i][SPACE_WIDTH] == '#')
		{
			space[i][SPACE_WIDTH] = ' ';
		}
	}

	// Move space ship one unit right unless a bomb is approaching from above.
	for (i = 1; i <= SPACE_HEIGHT; i++)
	{
		for (j = SPACE_WIDTH - 1; j >= 1; j--)
		{
			if (space[i][j] == '>' || space[i][j] == '#')
			{
				if (space[i][j + 1] == ' ')
				{
					space[i][j + 1] = '>';
					space[i][j] = ' ';
				} else
				{
					space[i][j + 1] = '#';
					space[i][j] = ' ';
					bombsDestroyed++;
				}
			} else if (space[i][j] == '<')
			{
				space[i][j] = '>';
			}
		}
	}

	return;
}

void MoveBombs(char space[][SPACE_WIDTH + 1], int& spaceShipsDestroyed)
{
	int i;
	int j;

	// Bomb has hit the planet.
	for (j = 1; j <= SPACE_WIDTH; j++)
	{
		if (space[SPACE_HEIGHT][j] == '*' || space[SPACE_HEIGHT][j] == '%')
		{
			space[SPACE_HEIGHT][j] = ' ';
		}
	}

	// Move bomb one unit down.
	for (i = SPACE_HEIGHT - 1; i >= 1; i--)
	{
		for (j = 1; j <= SPACE_WIDTH; j++)
		{
			if (space[i][j] == '*' || space[i][j] == '%')
			{
				if (space[i + 1][j] == ' ')
				{
					space[i + 1][j] = '*';
					space[i][j] = ' ';
				} else
				{
					space[i + 1][j] = '%';
					space[i][j] = ' ';
					spaceShipsDestroyed++;
				}
			}
		}
	}

	return;
}

void ReleaseSpaceShip(char space[][SPACE_WIDTH + 1], int iterations, int& bombsDestroyed)
{
	int i;

	if (iterations > 40)
	{
		i = 1 + rand() % SPACE_HEIGHT;
		if (space[i][1] == '*')
		{
			bombsDestroyed++;
		}
		space[i][1] = space[i][0];
		space[i][0] = ' ';
	}

	return;
}

void ReleaseBombs(char space[][SPACE_WIDTH + 1], int iterations, int& spaceShipsDestroyed)
{
	int i;
	int j;
	int k;

	if (iterations > 0)
	{
		k = 1 + rand() % MAX_BOMBS_PER_DROP;
		for (i = 1; i <= k; i++)
		{
			j = 1 + rand() % SPACE_WIDTH;
			if (space[1][j] == '>')
			{
				spaceShipsDestroyed++;
			}
			space[1][j] = space[0][j];
		}
	}

	return;
}

bool ContinueAttack(char space[][SPACE_WIDTH + 1], int& pointCount)
{
	int i;
	int j;
	bool attackFinished = true;

	// Attack continues as long as space ships still exist.
	for (i = 1; i <= SPACE_HEIGHT; i++)
	{
		if (space[i][0] == '>')
		{
			attackFinished = false;
			break;
		}
	}

	pointCount = 0;
	for (i = 1; i <= SPACE_HEIGHT; i++)
	{
		if (printFlag)
			cout << "|";
		for (j = 1; j <= SPACE_WIDTH; j++)
		{
			if (space[i][j] == '>' || space[i][j] == '#' || space[i][j] == '%')
			{
				attackFinished = false;
			}
			if (space[i][j] == '>' || space[i][j] == '#' ||
				space[i][j] == '*' || space[i][j] == '%')
			{
				pointCount++;
			}
			if (printFlag)
				cout << space[i][j];
		}
		if (printFlag)
			cout << "|" << endl;
	}

	return (attackFinished);
}

void PrintLowerBorder()
{
	cout << setw(SPACE_WIDTH + 2) << setfill('-') << "-" << endl;

	return;
}

void DetectCollisions(int iterations, int pointCount, char space[][SPACE_WIDTH + 1])
{
	int i;
	Point* pX;
	ClosePair* clP;
	int closePairs;

	if (iterations > 0 && pointCount > 0)
	{
		//
		// Your code here.
		//
	}

	return;
}

void Pause(int argc, int bombsDestroyed, int spaceShipsDestroyed, int& iterations)
{
	char next;

	if(printFlag)
	{
		cout << "bombsDestroyed = " << bombsDestroyed << endl;
		cout << "spaceShipsDestroyed = " << spaceShipsDestroyed << endl;
	}


	// If not on auto, print stats and stop.
	if (waitFlag)
	{
		cin.get(next);

	}
	// Otherwise, pause briefly
	else if(printFlag)
	{
		this_thread::sleep_for(chrono::microseconds(SLEEP_DELAY));
	}
	iterations++;

	return;
}

void PrintStats(int bombsDestroyed, int spaceShipsDestroyed)
{

	if (bombsDestroyed > 0)
	{
		cout << "bombsDestroyed = " << bombsDestroyed << endl;
	}

	if (spaceShipsDestroyed > 0)
	{
		cout << "spaceShipsDestroyed = " << spaceShipsDestroyed << endl;
	}

	cout << "survivors = " << SPACE_HEIGHT - spaceShipsDestroyed << endl;

	return;
}

