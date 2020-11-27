#include <bits/stdc++.h>
using namespace std;

#define n 3

const char human = 'X';
const char ai = 'O';

enum Player
{
	HUMAN,
	AI
};

struct Move
{
	int x;
	int y;
};

class Game
{
	char board[n][n];

public:
	Game();

	void printBoard();
	

	bool gameOver();
	

	bool checkWin(Player player);
	

	bool checkWin2(Player player);
	

	void play(int x);
	
	void play2();

	void getHumanMove(Player player);
	

	int score();
	

	Move minimax(char AIboard[n][n]);
	

	int minSearch(char AIboard[n][n]);


	int maxSearch(char AIboard[n][n]);
	
};
