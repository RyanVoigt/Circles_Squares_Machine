#include <cstdlib>
#include <iostream>

using namespace std;

int board[3][3] = {0,0,0,0,0,0,0,0,0};

void play_in_open(int & nextR, int & nextC)
{
	bool done = 0;
	for (int row = 0; row < 3 && !done; row++)
	{
		for (int col = 0; col < 3 && !done; col++)
		{
			if (board[row][col] == 0)
			{
				nextR = row;
				nextC = col;
				done = 1;
			}
		}
	}
//cout << "open " << done <<endl;
}

bool make_line_of_two(int & nextR, int & nextC)
{
	bool done = 0;
	int player = 0, robot = 0;
//for each row
	for (int row = 0; row < 3 && !done; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			if (board[row][col] == 1)
				player++;
			if (board[row][col] == 2)
				robot++;
		}
		if (robot == 1 && player == 0)
		{
			for (int col = 0; col < 3 && !done; col++)
			{
				if (board[row][col] == 0)
				{
					nextC = col;
					done = 1;
//cout << "mlot1" << endl;
				}
			}
			nextR = row;
		}
		robot = player = 0;
	}
//for each column
	for (int col = 0; col < 3 && !done; col++)
	{
		for (int row = 0; row < 3; row++)
		{
			if (board[row][col] == 1)
				player++;
			if (board[row][col] == 2)
				robot++;
		}
		if (robot == 1 && player == 0)
		{
			for (int row = 0; row < 3 && !done; row++)
			{
				if (board[row][col] == 0)
				{
					nextR = row;
					done = 1;
//cout << "mlot2" << endl;
				}
			}
			nextC = col;
		}
		robot = player = 0;
	}
//for diagonal 00,11,22
	for (int i = 0; i < 3 && !done; i++)
	{
		if (board[i][i] == 1)
			player++;
		if (board[i][i] == 2)
			robot++;
	}
	if (robot == 1 && player == 0)
	{
		for (int i = 0; i < 3 && !done; i++)
		{
			if (board[i][i] == 0)
			{
				nextC = nextR = i;
				done = 1;
//cout << "mlot3" << endl;
			}
		}
	}
	robot = player = 0;
//for diagonal 20,11,02
	for (int i = 0; i < 3 && !done; i++)
	{
		if (board[2-i][i] == 1)
			player++;
		if (board[2-i][i] == 2)
			robot++;
	}
	if (robot == 1 && player == 0)
	{
		for (int i = 0; i < 3 && !done; i++)
		{
			if (board[2-i][i] == 0)
			{
				nextR = 2-i;
				nextC = i;
				done = 1;
//cout << "mlot4" << endl;
			}
		}
	}
//cout << "line of 2 " <<done << endl;
	return done;
}

bool robot_intersect(int & nextR, int & nextC)
{
	//k switches the player check, if k == 1 then we find intersect for human
	bool foundIntersect = 0;
	int intersect[3][3] = {0,0,0,0,0,0,0,0,0};
	int robot = 0, player = 0;

//for each row
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			if (board[row][col] == 1)
				player++;
			if (board[row][col] == 2)
				robot++;
		}
		if (robot == 1 && player == 0)
		{
			for (int col = 0; col < 3; col++)
				intersect[row][col] += 1;
		}
		robot = player = 0;
	}
//for each column
	for (int col = 0; col < 3; col++)
	{
		for (int row = 0; row < 3; row++)
		{
			if (board[row][col] == 1)
				player++;
			if (board[row][col] == 2)
				robot++;
		}
		if (robot == 1 && player == 0)
		{
			for (int row = 0; row < 3; row++)
				intersect[row][col] += 1;
		}
		robot = player = 0;
	}
//for diagonal 00,11,22
	for (int i = 0; i < 3; i++)
	{
		if (board[i][i] == 1)
			player++;
		if (board[i][i] == 2)
			robot++;
	}
	if (robot == 1 && player == 0)
	{
		for (int i = 0; i < 3; i++)
			intersect[i][i] += 1;
	}
	robot = player = 0;
//for diagonal 20,11,02
	for (int i = 0; i < 3; i++)
	{
		if (board[2-i][i] == 1)
			player++;
		if (board[2-i][i] == 2)
			robot++;
	}
	if (robot == 1 && player == 0)
	{
		for (int i = 0; i < 3; i++)
			intersect[2-i][i] += 1;
	}
	robot = player = 0;

//set coord to play at
	int row = 0, col = 0;
	while (row < 3 && !foundIntersect)
	{
		while (col < 3 && !foundIntersect)
		{
			if (intersect[row][col] == 2)
			{
				foundIntersect = 1;
				nextR = row;
				nextC = col;
			}
			col++;
		}
		row++;
	}
//cout << "intersect " << foundIntersect << endl;
	return foundIntersect;
}

bool two_in_line(int & nextR, int & nextC)
{
	int robot = 0, player = 0;
	bool rWin = 0, pWin;

//for each row
	for (int row = 0; row < 3; row++)
	{
		if (!rWin)
		{
			for (int col = 0; col < 3; col++)
			{
					if (board[row][col] == 1)
						player++;
					if (board[row][col] == 2)
						robot++;
			}

			if (robot == 2 && player == 0)
			{
				rWin = 1;
				nextR = row;
//cout << "ri1r" << endl;
				for (int col = 0; col < 3; col++)
					if (board[row][col] == 0)
						nextC = col;
			}
			else if (player == 2 && robot == 0)
			{
				pWin = 1;
				nextR = row;
//cout << "ri1p" << endl;
				for (int col = 0; col < 3; col++)
					if (board[row][col] == 0)
						nextC = col;
			}

			robot = player = 0;
		}
	}
//for each column
	for (int col = 0; col < 3; col++)
	{
		if (!rWin)
		{
			for (int row = 0; row < 3; row++)
			{
				if (board[row][col] == 1)
					player++;
				if (board[row][col] == 2)
					robot++;
			}
			if (robot == 2 && player == 0)
			{
				rWin = 1;
				nextC = col;
//cout << "ri2r" << endl;
				for (int row = 0; row < 3; row++)
					if (board[row][col] == 0)
						nextR = row;
			}
			else if (player == 2 && robot == 0)
			{
				pWin = 1;
				nextC = col;
//cout << "ri2p" << endl;
				for (int row = 0; row < 3; row++)
					if (board[row][col] == 0)
						nextR = row;
			}
			robot = player = 0;
		}
	}
//diagonal across 00,11,22
	if (!rWin)
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[i][i] == 1)
				player++;
			if (board[i][i] == 2)
				robot++;
		}
		if (robot == 2 && player == 0)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[j][j] == 0)
					nextR = nextC = j;
			}
			rWin = 1;
//cout << "ri3r" << endl;
		}
		else if (player == 2 && robot == 0)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[j][j] == 0)
					nextR = nextC = j;
			}
			pWin = 1;
//cout << "ri3p" << endl;
		}
		robot = player = 0;
	}
//diagonal across 20,11,02
	if (!rWin)
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[2-i][i] == 1)
				player++;
			if (board[2-i][i] == 2)
				robot++;
		}
		if (robot == 2 && player == 0)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[2-j][j] == 0)
				{
					nextR = 2-j;
					nextC = j;
				}
			}
			rWin = 1;
//cout << "ri4r" << endl;
		}
		else if (player == 2 && robot == 0)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[2-j][j] == 0)
				{
					nextR = 2-j;
					nextC = j;
				}
			}
			pWin = 1;
//cout << "ri4p" << endl;
		}
	}
//cout << "two in line " << rWin << pWin << endl;
	if (!rWin)
		return pWin;
	else
		return rWin;
}

void rotate_CW(int amount)
{
	int rotB[3][3];

	for (int i = 0; i < amount; i++)
	{
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				rotB[row][col] = board[2-col][row];
			}
		}

		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				board[row][col] = rotB[row][col];
			}
		}
	}
}

void rotate_CoCW(int amount)
{
	int rotB[3][3];

	for (int i = 0; i < amount; i++)
	{
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				rotB[row][col] = board[col][2-row];
			}
		}

		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				board[row][col] = rotB[row][col];
			}
		}
	}
}

void rotate_XY_ccw(int & x, int & y, int amount)
{
	int hx = x, hy = y;
	for (int i = 0; i < amount; i++)
	{
		if (x == 0)
		{
			if (y == 0)
			{
				hx = 2; hy = 0;
			}
			else if (y == 1)
			{
				hx = 1; hy = 0;
			}
			else if (y == 2)
			{
				hx = 0; hy = 0;
			}
		}
		else if (x == 1)
		{
			if (y == 0)
			{
				hx = 2; hy = 1;
			}
			else if (y == 2)
			{
				hx = 0; hy = 1;
			}
		}
		else if (x == 2)
		{
			if (y == 0)
			{
				hx = 2; hy = 2;
			}
			else if (y == 1)
			{
				hx = 1; hy = 2;
			}
			else if (y == 2)
			{
				hx = 0; hy = 2;
			}
		}
		x = hx; y = hy;
	}
}

void win_action(int k)
{
	if (k == 1)
		cout << "robot has won" << endl;
	else if (k == 2)
		cout << "player has won" << endl;
	else
		cout << "game is a tie" << endl;
}

bool game_win()
{
	bool win = 0;
	int robot = 0, player = 0;
	int row = 0, col = 0;

	//for each row
	while (row < 3 && !win)
	{
		while (col < 3)
		{
			if (board[row][col] == 1)
				player++;
			if (board[row][col] == 2)
				robot++;
			col++;
		}

		if (robot == 3)
		{
			win_action(1);
			win = 1;
		}
		else if (player == 3)
		{
			win_action(2);
			win = 1;
		}
		robot = player = col = 0;
		row++;
	}
	row = 0;

//for each column
	while (col < 3 && !win)
	{
		while (row < 3)
		{
			if (board[row][col] == 1)
				player++;
			if (board[row][col] == 2)
				robot++;
			row++;
		}

		if (robot == 3)
		{
			win_action(1);
			win = 1;
		}
		else if (player == 3)
		{
			win_action(2);
			win = 1;
		}
		robot = player = row = 0;
		col++;
	}
	col = 0;

//for diagonal 00,11,22
	if (!win)
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[i][i] == 1)
				player++;
			if (board[i][i] == 2)
				robot++;
		}
		if (robot == 3)
		{
			win_action(1);
			win = 1;
		}
		else if (player == 3)
		{
			win_action(2);
			win = 1;
		}
		robot = player = 0;
	}

	//for diagonal 20,11,02
	if (!win)
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[2-i][i] == 1)
				player++;
			if (board[2-i][i] == 2)
				robot++;
		}
		if (robot == 3)
		{
			win_action(1);
			win = 1;
		}
		else if (robot == 3)
		{
			win_action(2);
			win = 1;
		}
		robot = player = 0;
	}

	if (!win &&
		board[0][0] != 0 && board[0][1] != 0 && board[0][2] != 0 &&
		board[1][0] != 0 && board[1][1] != 0 && board[1][2] != 0 &&
		board[2][0] != 0 && board[2][1] != 0 && board[2][2] != 0)
	{
		win_action(0);
		win = 1;
	}
	return win;
}

void clear_board()
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			board[row][col] = 0;
		}
	}
}

bool game_logic(int & nextR, int & nextC, int turn, int & rotateAmount)
{
	// if (game_win())
		// return 1;

	if (turn == 1)
	{
		if (board[1][0] == 1 || board[2][0] == 1)
			rotateAmount = 1;

		else if (board[2][1] == 1 || board[2][2] == 1)
			rotateAmount = 2;

		else if (board[0][2] == 1 || board[1][2] == 1)
			rotateAmount = 3;

		rotate_CW(rotateAmount);

		if (board[0][0] == 1)
		{
			board[1][1] == 2;
			nextR = nextC = 1;
		}
		else if (board[0][1] == 1)
		{
			board[0][0] == 2;
			nextR = nextC = 0;
		}
		else if (board[1][1] == 1)
		{
			board[2][0] == 2;
			nextR = 2;
			nextC = 0;
		}

		rotate_XY_ccw(nextR, nextC, rotateAmount);
		rotate_CoCW(rotateAmount);
	}

	else if (turn == 2)
	{
		if (!two_in_line(nextR, nextC))
		{
			rotate_CW(rotateAmount);
			if (board[0][0] == 1)
			{
				if (board[1][2] == 1)
				{
					board[2][1] = 2;
					nextR = 2;
					nextC = 1;
				}
				else if (board[2][1] == 1)
				{
					board[1][2] = 2;
					nextR = 1;
					nextC = 2;
				}
				else if (board[2][2])
				{
					board[1][0] = 2;
					nextR = 1;
					nextC = 0;
				}
			}
			else if (board[0][1] == 1)
			{
				if (board[1][0] == 1)
				{
					board[1][1] = 2;
					nextR = nextC = 1;
				}
				else if (board[0][2] == 1 || board[1][2] == 1 || board[2][2] == 1)
				{
					board[2][0] = 2;
					nextR = 2;
					nextC = 0;
				}
				else if (board[2][0] == 1)
				{
					board[1][1] = 2;
					nextR = nextC = 0;
				}
			}
			else if (board[1][1] == 1)
			{
				if (board[0][2] == 1)
				{
					board[0][0] = 2;
					nextR = nextC = 0;
				}
			}
			rotate_CoCW(rotateAmount);
			rotate_XY_ccw(nextR, nextC, rotateAmount);
		}
	}
	else if (turn > 2)
	{
		if (!two_in_line(nextR, nextC))
		{
			if(!robot_intersect(nextR, nextC))
			{
				if (!make_line_of_two(nextR, nextC))
					play_in_open(nextR, nextC);
			}
		}
	}

	// if (game_win())
		// return 1;
	// else
		return 0;
}

int print(int k)
{
	cout << k << endl;
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			cout << board[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	int nextR = 0, nextC = 0, rotateAmount = 0, turn = 0;
	int pick = 0;

	while (!game_win())
	{
		cout << ">";
		cin >> pick;
		if (pick == 7)
			board[0][0] = 1;
		else if (pick == 8)
			board[0][1] = 1;
		else if (pick == 9)
			board[0][2] = 1;
		else if (pick == 4)
			board[1][0] = 1;
		else if (pick == 5)
			board[1][1] = 1;
		else if (pick == 6)
			board[1][2] = 1;
		else if (pick == 1)
			board[2][0] = 1;
		else if (pick == 2)
			board[2][1] = 1;
		else if (pick == 3)
			board[2][2] = 1;
		else
			return 0;

		print(rotateAmount);

		turn++;
		if(!game_win())
		{
			game_logic(nextR, nextC, turn, rotateAmount);
			board[nextR][nextC] = 2;
		}

		print(rotateAmount);
	}
}
