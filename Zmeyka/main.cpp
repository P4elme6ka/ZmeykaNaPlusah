#include "TXLib.h"
#include <time.h>
#include <iostream>
#include "blend2d/blend2d/src/blend2d.h"

int main() {
	int snake_len = 1;
	int** pole;
	int dir = 0; // 0 - UP; 1 - RIGHT; 2 - DOWN; 3 - LEFT


	pole = new int*[101];
	for (int i = 0; i < 101; i++) {
		pole[i] = new int[101];
	}


	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++) {
			pole[i][j] = -1;
		}

	int x_p = random(100);
	int y_p = random(100);

	pole[x_p][y_p] = -2;

	txCreateWindow(1000, 1000);

	int x = 50;
	int y = 50;
	pole[x][y] = 1;

	while (true) {
		txBegin();
		txSetFillColor(TX_BLACK);
		txClear();
		txSetFillColor(TX_WHITE);

		if (GetAsyncKeyState(VK_SPACE)) {
			snake_len++;
		}

		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}

		if (GetAsyncKeyState(VK_UP) && dir != 2) {
			dir = 0;
		}
		if (GetAsyncKeyState(VK_DOWN) && dir != 0) {
			dir = 2;
		}
		if (GetAsyncKeyState(VK_RIGHT) && dir != 3) {
			dir = 1;
		}
		if (GetAsyncKeyState(VK_LEFT) && dir != 1) {
			dir = 3;
		}

		switch (dir)
		{
		case 0:
			y--;
			break;
		case 1:
			x++;
			break;
		case 2:
			y++;
			break;
		case 3:
			x--;
			break;
		}

		if (y > 100) {
			y = 0;
		}
		else if (y < 0) {
			y = 100;
		}

		if (x < 0) {
			x = 100;
		} 
		else if (x > 100) {
			x = 0;
		}

		if (pole[x][y] > 0) {
			break;
		}

		pole[x][y] = 1;

		if (x == x_p && y == y_p) {
			snake_len++;
			while (pole[x_p][y_p] != -1) {
				x_p = random(100);
				y_p = random(100);
			}
			pole[x_p][y_p] = -2;
		}

		txSetColor(TX_RED);
		for (int i = 0; i < 100; i++) {
			txLine(i * 10, 0, i * 10, 1000);
			txLine(0, i * 10, 1000, i * 10);
		}

		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++) {
				if (pole[i][j] > 0) {
					pole[i][j] += 1;
					txSetFillColor(TX_WHITE);
					txRectangle(i * 10, j * 10, i * 10 + 10, j * 10 + 10);
				}
				if (pole[i][j] > snake_len) {
					pole[i][j] = -1;
				}
			}
		
		
		txSetFillColor(TX_BLUE);
		txRectangle(x_p * 10, y_p * 10, x_p * 10 + 10, y_p * 10 + 10);


		txSetFillColor(TX_WHITE);
		txRectangle(x * 10, y * 10, x * 10 + 11, y * 10 + 11);

		txSleep(100);
	}
	cout << "Game over" << '\n' << "Press any key to exit" << '\n';
    return 0;
}
