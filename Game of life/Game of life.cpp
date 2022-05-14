// Game of life.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

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

int cell[8][8] = {
	0,0,0,0,0,0,0,0,
	0,0,0,1,0,0,0,0,
	0,0,0,1,0,0,0,0,
	0,0,0,1,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,
	0,0,0,0,0,0,0,1,
	0,0,0,0,0,0,0,1 };

int out[8][8] = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0 };

int count_friends(int _c[8][8], int x, int y) {

	/*
	sxx
	xxx
	xxx
	*/

	int _o = 0;

	if (_c[y][x + 1] == 1) {
		_o++;
	}
	if (_c[y + 1][x] == 1) {
		_o++;
	}
	if (_c[y - 1][x] == 1) {
		_o++;
	}
	if (_c[y][x - 1] == 1) {
		_o++;
	}
	if (_c[y + 1][x + 1] == 1) {
		_o++;
	}
	if (_c[y + 1][x - 1] == 1) {
		_o++;
	}
	if (_c[y - 1][x + 1] == 1) {
		_o++;
	}
	if (_c[y - 1][x - 1] == 1) {
		_o++;
	}


	return _o;
}

void show_cell(int _c[8][8])
{
	for (size_t i = 0; i < sizeof(_c[0]) / sizeof(_c[0][0]); i++)
	{
		for (size_t m = 0; m < 8; m++)
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

	for (size_t m = 0; m < 8; m++)
	{
		for (size_t i = 0; i < 8; i++)
		{
			int _around_alive = count_friends(cell, i, m);

			// if a cell has zero alive nabors it dies
			// if a cell has 1 alive nabors it dies
			// if it has two they both stay alive
			// if a cell has three nabors, it births

			switch (_around_alive)
			{
			case 0:
				out[m][i] = 0;
				break;

			case 1:
				out[m][i] = 0;
				break;

			case 2:
				if (cell[m][i] == 1)
				{
					out[m][i] = 1;
				}
				else
				{
					out[m][i] = 0;
				}
				break;

			case 3:
				out[m][i] = 1;
				break;

			default: // This will be four or more
				out[m][i] = 0;
				break;
			}
			std::cout << _around_alive;
		}
		std::cout << "\n";
	}
}


int main() {
	std::cout << "Conways Game of Life\n";
	std::cout << spacer << "\n";
	show_cell(cell);
	std::cout << spacer << "\n";
	game_logic();
	std::cout << spacer << "\n";
	show_cell(out);

	memcpy(cell, out, sizeof(cell));

	while (1) {
		clear_screen();
		game_logic();
		std::cout << spacer << "\n";
		show_cell(out);
		memcpy(cell, out, sizeof(cell));
		Sleep(500);
	}
	return 0;
}