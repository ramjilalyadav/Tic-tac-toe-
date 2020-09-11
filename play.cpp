#include <bits/stdc++.h>
#include "game.h"
using namespace std;

int main()
{
	cout << "ENTER YOUR NAME" << endl;
	string name;
	cin >> name;
	cout << " Welcome " << name << endl;

	cout << "THERE IS  2 TYPE OF GAME " << endl
		 << endl;
	cout << "IF YOU WANT TO PLAY WITH FRIENDS THEN PRESS  1 OR PRESS 2 FOR PLAY WITH COMPUTER" << endl;
	int mood;
	cin >> mood;
	Game tictactoe;
	if (mood == 1)
	{
		tictactoe.play2();
	}
	else
	{
		cout << "IF you want first then enter 0 else enter 1" << endl;
		int choice;
		cin >> choice;
		tictactoe.play(choice);
	}

	return 0;
}