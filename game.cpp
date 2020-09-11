#include <bits/stdc++.h>
#include "game.h"
using namespace std;

Game::Game()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			board[i][j] = '-';
		}
	}
}

void Game::printBoard()
{
	for (int i = 0; i <= n * 6; i++)
		cout << "-";
	for (int i = 0; i < n; i++)
	{
		cout << '\n'
			 << "|";
		for (int j = 0; j < n; j++)
		{
			cout << setw(3) << board[i][j] << setw(3) << " |";
		}
	}
	cout << '\n';
	for (int i = 0; i <= n * 6; i++)
		cout << "-";
	cout << '\n';
}

bool Game::gameOver()
{
	if (checkWin(HUMAN))
		return true;
	else if (checkWin(AI))
		return true;

	bool emptySpace = false;
	/*for (int i = 0; i < n; i++)
	{	
		if (board[i][0] == '-' || board[i][1] == '-' || board[i][2] == '-' || board[i][3] == '-')
			emptySpace = true;
	}
	return !emptySpace;*/
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			if (board[i][j] == '-')
				return false;
	}
	return true;
}

bool Game::checkWin(Player player)
{
	char playerChar;
	if (player == HUMAN)
		playerChar = human;
	else
		playerChar = ai;

	for (int i = 0; i < n; i++)
	{
		// Check horizontals
		if (board[i][0] == playerChar && board[i][1] == playerChar && board[i][2] == playerChar)
			return true;

		// Check verticals
		if (board[0][i] == playerChar && board[1][i] == playerChar && board[2][i] == playerChar)
			return true;
	}

	// Check diagonals
	if (board[0][0] == playerChar && board[1][1] == playerChar && board[2][2] == playerChar)
	{
		return true;
	}
	else if (board[0][2] == playerChar && board[1][1] == playerChar && board[2][0] == playerChar)
	{
		return true;
	}

	return false;
}

bool Game::checkWin2(Player player)
{
	char playerChar;
	if (player == HUMAN)
		playerChar = human;
	else
		playerChar = ai;

	for (int i = 0; i < n; i++)
	{
		int j = 0;
		while (j < n)
		{
			if (board[i][j] == playerChar)
				j++;
			else
			{
				break;
			}
			if (j == n)
				return true;
		}
	}
	for (int i = 0; i < n; i++)
	{
		int j = 0;
		while (j < n)
		{
			if (board[j][i] == playerChar)
				j++;
			else
			{
				break;
			}
			if (j == n)
				return true;
		}
	}

	int i = 0;
	while (i < n)
	{
		if (board[i][i] == playerChar)
			i++;
		else
		{
			break;
		}
	}
	if (i == n)
		return true;

	i = 0;
	while (i < n)
	{
		if (board[i][n - 1 - i] == playerChar)
			i++;
		else
		{
			break;
		}
	}
	if (i == n)
		return true;
	return false;
}

int Game::score()
{
	if (checkWin(HUMAN))
	{
		return 10;
	}
	else if (checkWin(AI))
	{
		return -10;
	}
	return 0; // draw
}

Move Game::minimax(char AIboard[n][n])
{
	int bestMoveScore = 100; // -100 is arbitrary
	Move bestMove;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (AIboard[i][j] == '-')
			{
				AIboard[i][j] = ai;
				int tempMoveScore = maxSearch(AIboard);
				if (tempMoveScore <= bestMoveScore)
				{
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMove;
}

int Game::maxSearch(char AIboard[n][n])
{
	if (gameOver())
		return score();
	Move bestMove;

	int bestMoveScore = -1000;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (AIboard[i][j] == '-')
			{
				AIboard[i][j] = human;
				int tempMoveScore = minSearch(AIboard);
				if (tempMoveScore >= bestMoveScore)
				{
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMoveScore;
}

int Game::minSearch(char AIboard[n][n])
{
	if (gameOver())
		return score();
	Move bestMove;

	int bestMoveScore = 1000;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (AIboard[i][j] == '-')
			{
				AIboard[i][j] = ai;
				int tempMove = maxSearch(AIboard);
				if (tempMove <= bestMoveScore)
				{
					bestMoveScore = tempMove;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMoveScore;
}

void Game::getHumanMove(Player player)
{
	char playerChar;
	if (player == HUMAN)
	{
		playerChar = human;
	}
	else
	{
		playerChar = ai;
	}
again:
	int x, y = -1; // arbitrary assignment to init loop
	while (x < 0 || x > (n - 1) || y < 0 || y > (n - 1))
	{
		// Loop until a valid move is entered
		cout << "Enter your move in coordinate form, ex: (1," << n << ")." << endl;
		int a, b;
		string restofline;
		cin >> a >> b;
		x = a - 1;
		y = b - 1;
		getline(cin, restofline); // get garbage chars after move
	}
	if (board[x][y] != '-')
		goto again;
	board[x][y] = playerChar;
}

void Game::play(int turn)
{
	printBoard();
	while (!checkWin(HUMAN) && !checkWin(AI) && !gameOver())
	{
		// human move
		if (turn % 2 == 0)
		{
			getHumanMove(HUMAN);
			if (checkWin(HUMAN))
				cout << "Human Player Wins" << endl;
			turn++;
			printBoard();
		}
		else
		{
			cout << endl
				 << "Computer Player Move:" << endl;
			Move AImove = minimax(board);
			board[AImove.x][AImove.y] = ai;
			if (checkWin(AI))
				cout << "Computer Player Wins" << endl;
			turn++;
			printBoard();
		}
	}
}

void Game::play2()
{
	string name1, name2;
	cout << "ENTER THE NAME  OF FIRST PLAYER" << endl;
	cin >> name1;
	cout << endl;
	cout << "ENTER THE NAME  OF SECOND PLAYER" << endl;
	cin >> name2;
	cout << endl;
	cout << "Dear " << name1 << "   YOUR SYMBOL IS    " << human << endl;
	cout << "Dear " << name2 << "   YOUR SYMBOL IS    " << ai << endl;
	cout << "Lets begin the game press any number to start the game" << endl;
	int s;
	cin >> s;

	int turn = 0;
	printBoard();
	while (!checkWin2(HUMAN) && !checkWin2(AI) && !gameOver())
	{
		// human move
		if (turn % 2 == 0)
		{
			cout << name1 << "    its your turn  " << endl;
			getHumanMove(HUMAN);
			if (checkWin(HUMAN))
			{
				cout << name1 << "    Wins the Game" << endl;
				cout << name2 << "    Better luck next time" << endl;
			}
			turn++;
			printBoard();
		}
		else
		{
			cout << endl;
			cout << "its   " << name2 << "   Move:" << endl;
			getHumanMove(AI);
			if (checkWin(AI))
			{
				{
					cout << name2 << "    Wins the Game" << endl;
					cout << name1 << "    Better luck next time" << endl;
				}
			}

			turn++;
			printBoard();
		}
	}
}