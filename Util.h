#pragma once
#include <iostream> 
#include <Windows.h>
#include <time.h>
#include "Consola.h"
#include <conio.h>
#define MAP_X1 11
#define MAP_Y1 5
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define MAP_WIDTH2 12
#define MAP_HEIGHT2 12
#define MAP_WIDTH3 13
#define MAP_HEIGHT3 13

using namespace std;

class Util {
public:
	static void xyputint(int x, int y, const int ch) {
		gotoxy(x, y);
		cout << ch;
	}
	static void xyputd(int x, int y, const double ch) {
		gotoxy(x, y);
		cout << ch;
	}
	static void xyputc(int x, int y, const char ch) {
		gotoxy(x, y);
		cout << ch;
	}
	static void xyputstr(int x, int y, const char str[]) {
		gotoxy(x, y);
		cout << str;
	}
	static void fillbox(int x1, int y1, int x2, int y2, const char color) {
		textbackground(color);
		for (int y = y1; y < y2; y++) {
			for (int x = x1; x < x2; x++) {
				xyputc(x, y, ' ');
			}
		}
	}
	static void filltext(int x, int y, const char color) {
		textcolor(color);
		xyputc(x, y, ' ');
	}
	static int getKey()
	{
		int key = _getch();
		return ((key == 0xe0) ? (0xe000 | _getch()) : key);
	}
	static void drawCharcter(int x, int y)
	{
		textcolor(GREEN);
		xyputstr((MAP_X1 + x + 1) * 2, MAP_Y1 + 1 + y, "■");
		textcolor(WHITE);
	}
	static void drawCell(int col, int row, int mapData[][10])
	{
		const char* cellSymbol[] = { "  ", "▦", "●",NULL,"※","◎" };
		int cell = mapData[row][col];
		if (cell == 2) {
			textcolor(BLUE);
		}
		if (cell == 4) {
			textcolor(YELLOW);
		}
		if (cell == 5) {
			textcolor(RED);
		}
		if (cell == 1) {
			textcolor(WHITE);
		}
		gotoxy((MAP_X1 + col + 1) * 2, MAP_Y1 + row + 1);
		puts(cellSymbol[cell]);
	}

	static void Map(int mapData[][10])
	{
		for (int row = 0; row < MAP_HEIGHT; ++row)
		{
			for (int col = 0; col < MAP_WIDTH; ++col)
			{
				drawCell(col, row, mapData); // col, row를 변경시키는 걸로 소스 코드 다시 짜기
			}
		}
	}
	static void drawCell2(int col, int row, int mapData[][12])
	{
		const char* cellSymbol[] = { "  ", "▦", "●",NULL,"※","◎" };
		int cell = mapData[row][col];
		if (cell == 2) {
			textcolor(BLUE);
		}
		if (cell == 4) {
			textcolor(YELLOW);
		}
		if (cell == 5) {
			textcolor(RED);
		}
		if (cell == 1) {
			textcolor(WHITE);
		}
		gotoxy((MAP_X1 + col + 1) * 2, MAP_Y1 + row + 1);
		puts(cellSymbol[cell]);
	}

	static void Map2(int mapData[][12])
	{
		for (int row = 0; row < MAP_HEIGHT2; ++row)
		{
			for (int col = 0; col < MAP_WIDTH2; ++col)
			{
				drawCell2(col, row, mapData); // col, row를 변경시키는 걸로 소스 코드 다시 짜기
			}
		}
	}
	static void drawCell3(int col, int row, int mapData[][13])
	{
		const char* cellSymbol[] = { "  ", "▦", "●",NULL,"※","◎" };
		int cell = mapData[row][col];
		if (cell == 2) {
			textcolor(BLUE);
		}
		if (cell == 4) {
			textcolor(YELLOW);
		}
		if (cell == 5) {
			textcolor(RED);
		}
		if (cell == 1) {
			textcolor(WHITE);
		}
		gotoxy((MAP_X1 + col + 1) * 2, MAP_Y1 + row + 1);
		puts(cellSymbol[cell]);
	}

	static void Map3(int mapData[][13])
	{
		for (int row = 0; row < MAP_HEIGHT3; ++row)
		{
			for (int col = 0; col < MAP_WIDTH3; ++col)
			{
				drawCell3(col, row, mapData); // col, row를 변경시키는 걸로 소스 코드 다시 짜기
			}
		}
	}
	static void menubar(int stage)
	{
		//┌┐└┘│──
		filltext(55, 4, WHITE);
		xyputstr(55, 4, "┌───────────────────────────┐");
		filltext(55, 5, WHITE);
		xyputstr(55, 5, "│    Stage           /  11  │");
		textcolor(GREEN);
		xyputint(72, 5, stage);
		filltext(55, 6, WHITE);
		xyputstr(55, 6, "│                           │");
		filltext(55, 7, WHITE);
		xyputstr(55, 7, "│    Step                   │");
		filltext(55, 8, WHITE);
		xyputstr(55, 8, "│                           │");
		filltext(55, 9, WHITE);
		xyputstr(55, 9, "│    Time                   │");
		filltext(55, 10, WHITE);
		xyputstr(55, 10, "│───────────────────────────│");
		filltext(55, 11, WHITE);
		xyputstr(55, 11, "│          HELP KEY         │");
		filltext(55, 12, WHITE);
		xyputstr(55, 12, "│  → ← ↑ ↓ : MOVE       │");
		filltext(55, 13, WHITE);
		xyputstr(55, 13, "│  A : Previous Stage       │");
		filltext(55, 14, WHITE);
		xyputstr(55, 14, "│  S : Next Stage           │");
		filltext(55, 15, WHITE);
		xyputstr(55, 15, "│  Z : Previous Step        │");
		filltext(55, 16, WHITE);
		xyputstr(55, 16, "│  Q : Return Menu          │");
		filltext(55, 17, WHITE);
		xyputstr(55, 17, "│  R : Reset                │");
		filltext(55, 18, WHITE);
		xyputstr(55, 18, "│  P : Music ON / OFF       │");
		filltext(55, 19, WHITE);
		xyputstr(55, 19, "│  G : Give up              │");
		filltext(55, 20, WHITE);
		xyputstr(55, 20, "└───────────────────────────┘");
	}
	static void copy(int array1[][10], int array2[][10])
	{
		int* p1, * endp1;
		int* p2;
		p1 = &array1[0][0];
		p2 = &array2[0][0];
		endp1 = &array1[10 - 1][10 - 1];
		while (p1 <= endp1)
		{
			*p2 = *p1;
			p1++; p2++;
		}
	}
	static void copy2(int array1[][12], int array2[][12])
	{
		int* p1, * endp1;
		int* p2;
		p1 = &array1[0][0];
		p2 = &array2[0][0];
		endp1 = &array1[12 - 1][12 - 1];
		while (p1 <= endp1)
		{
			*p2 = *p1;
			p1++; p2++;
		}
	}
	static void copy3(int array1[][13], int array2[][13])
	{
		int* p1, * endp1;
		int* p2;
		p1 = &array1[0][0];
		p2 = &array2[0][0];
		endp1 = &array1[13 - 1][13 - 1];
		while (p1 <= endp1)
		{
			*p2 = *p1;
			p1++; p2++;
		}
	}
};
