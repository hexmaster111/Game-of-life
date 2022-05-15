// Game of life.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

void clear_screen(char fill = ' ') {
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}



const char* spacer = "-----------------------------------";

std::vector<std::vector<bool>> c_cell =
{
	{0,0,0,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,0,0,0},

}, c_out;


int count_friends(vector<vector<bool>> _c, int x, int y) {

	/*
	sxx
	xxx
	xxx
	*/

	int _o = 0;

	//y+0, x+1

	if (x != 0) {

		if (_c.at(y).at(x - 1)) {
			_o++;
		}
	}

	if (y != 0) {
		if (_c.at(y - 1).at(x)) {
			_o++;
		}
	}

	if (y + 1 != _c.size()) {
		if (_c.at(y + 1).at(x)) {
			_o++;
		}
	}

	if (x + 1 != _c.at(y).size()) {
		if (_c.at(y).at(x + 1)) {
			_o++;
		}
	}

	if (x != 0 and y != 0) {
		if (_c.at(y - 1).at(x - 1)) {
			_o++;
		}
	}

	if (x != 0 and y + 1 != _c.size()) {
		if (_c.at(y + 1).at(x - 1)) {
			_o++;
		}
	}

	if (x + 1 != _c.at(y).size() and y != 0) {
		if (_c.at(y - 1).at(x + 1)) {
			_o++;
		}
	}

	if (x + 1 != _c.at(y).size() and y + 1 != _c.size()) {
		if (_c.at(y + 1).at(x + 1)) {
			_o++;
		}
	}

	return _o;
}

void show_cell(vector<vector<bool>> _c)
{
	for (size_t i = 0; i < _c.size(); i++)
	{
		for (size_t m = 0; m < _c[i].size(); m++)
		{
			std::cout << _c[i][m];
		}
		std::cout << "\n";
	}
}

void game_logic() {
	// if a cell has zero alive nabors it dies
// if a cell has 1 alive nabors it dies
// if it has two they both stay alive
// if a cell has three nabors, it births

	int _around_alive = 0;


	for (size_t m = 0; m < c_cell.size() - 1; m++)
	{
		for (size_t i = 0; i < c_cell[i].size() - 1; i++)
		{
			int _around_alive = count_friends(c_cell, i, m);

			// if a cell has zero alive nabors it dies
			// if a cell has 1 alive nabors it dies
			// if it has two they both stay alive
			// if a cell has three nabors, it births

			switch (_around_alive)
			{
			case 0:
				c_out.at(m).at(i) = false;
				break;

			case 1:
				c_out[m][i] = 0;
				break;

			case 2:
				if (c_cell[m][i] == 1)
				{
					c_out[m][i] = 1;
				}
				else
				{
					c_out[m][i] = 0;
				}
				break;

			case 3:
				c_out[m][i] = 1;
				break;

			default: // This will be four or more
				c_out[m][i] = 0;
				break;
			}
			std::cout << _around_alive;
		}
		std::cout << "\n";
	}
}


int main() {
	std::cout << "Conways Game of Life\n";
	c_out.assign(c_cell.begin(), c_cell.end());
	std::cout << spacer << "\n";
	show_cell(c_cell);
	std::cout << spacer << "\n";
	game_logic();
	std::cout << spacer << "\n";
	show_cell(c_out);



	while (1) {
		clear_screen();
		game_logic();
		std::cout << spacer << "\n";
		show_cell(c_out);
		c_cell.assign(c_out.begin(), c_out.end());
		Sleep(500);
	}
	return 0;
}