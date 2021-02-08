#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Consola.h"
#include "keycode.h"
#include "Util.h"
#include "Tutorial.h"
#include "music.h"

#define MAP_X1 10
#define MAP_Y1 4
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define MAP_WIDTH2 12
#define MAP_HEIGHT2 12

using namespace std;

static int point = 0;
static double Total_time = 0.0;
class map
{
public:
	static void _start_menu()
	{
		music::_music();
		int menu_key;
		int off = 1;
		clrscr();
		// 전체
		Util::fillbox(25, 5, 95, 12, WHITE);
		// p
		Util::fillbox(27, 6, 39, 9, BLACK);
		Util::fillbox(29, 7, 37, 8, WHITE);
		Util::fillbox(27, 6, 29, 11, BLACK);
		// u
		Util::fillbox(45, 6, 57, 11, BLACK);
		Util::fillbox(47, 6, 55, 10, WHITE);
		// s
		Util::fillbox(63, 6, 75, 11, BLACK);
		Util::fillbox(65, 7, 75, 8, WHITE);
		Util::fillbox(63, 9, 73, 10, WHITE);
		// h
		Util::fillbox(81, 6, 92, 11, BLACK);
		Util::fillbox(83, 6, 90, 8, WHITE);
		Util::fillbox(83, 9, 90, 11, WHITE);

		textbackground(BLACK);
		int menu_xpos = 51, menu_ypos = 21;
		Util::xyputstr(54, 21, "게임 시작");
		Util::xyputstr(54, 22, "게임 방법");
		Util::xyputstr(54, 23, "게임 종료");
		Util::filltext(menu_xpos, menu_ypos, YELLOW);
		Util::xyputstr(menu_xpos, menu_ypos, "▶");
		Util::filltext(menu_xpos, menu_ypos + 1, WHITE);
		Util::xyputstr(menu_xpos, menu_ypos + 1, "▷");
		Util::filltext(menu_xpos, menu_ypos + 2, WHITE);
		Util::xyputstr(menu_xpos, menu_ypos + 2, "▷");
		while ((menu_key = Util::getKey()) != 'q')
		{
			int menu_oldxpos = menu_xpos;
			int menu_oldypos = menu_ypos;
			switch (menu_key)
			{
			case UPKEY:
			{
				menu_ypos--;
				if (menu_oldypos != menu_ypos)
				{
					if (menu_ypos == 20)
					{
						menu_ypos = 21;
					}
					Util::filltext(menu_oldxpos, menu_oldypos, WHITE);
					Util::xyputstr(menu_oldxpos, menu_oldypos, "▷");
					Util::filltext(menu_xpos, menu_ypos, YELLOW);
					Util::xyputstr(menu_xpos, menu_ypos, "▶");
				}
				break;
			}
			case DOWNKEY:
			{
				menu_ypos++;
				if (menu_oldypos != menu_ypos)
				{
					if (menu_ypos == 24)
					{
						menu_ypos = 23;
					}
					Util::filltext(menu_oldxpos, menu_oldypos, WHITE);
					Util::xyputstr(menu_oldxpos, menu_oldypos, "▷");
					Util::filltext(menu_xpos, menu_ypos, YELLOW);
					Util::xyputstr(menu_xpos, menu_ypos, "▶");
				}
				break;
			}
			case PKEY:
			{
				if (off == 1) {
					music::_stop();
					off = 0;
					break;
				}
				else if (off == 0) {
					music::_music();
					off = 1;
					break;
				}
			}
			case SPACE:
			{
				if (menu_ypos == 21)
				{
					clrscr();
					map1();
					_start_menu();
					break;
				}
				if (menu_ypos == 22)
				{
					clrscr();
					Tutorial::tutorial();
					_start_menu();
					break;
				}
				if (menu_ypos == 23)
				{
					Util::filltext(menu_xpos, menu_ypos, WHITE);
					Util::xyputstr(menu_oldxpos, menu_oldypos, "▷");
					exit(0);
				}
			}
			}
		}
		_setcursortype(_NOCURSOR);
	}

	static void map1()
	{
		int mapData[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,0,0,0,0},
			{0,0,0,1,4,1,0,0,0,0},
			{0,0,0,1,0,1,1,1,1,0},
			{0,1,1,1,2,0,2,4,1,0},
			{0,1,4,0,2,0,1,1,1,0},
			{0,1,1,1,1,2,1,0,0,0},
			{0,0,0,0,1,4,1,0,0,0},
			{0,0,0,0,1,1,1,0,0,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int Undo[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,0,0,0,0},
			{0,0,0,1,4,1,0,0,0,0},
			{0,0,0,1,0,1,1,1,1,0},
			{0,1,1,1,2,0,2,4,1,0},
			{0,1,4,0,2,0,1,1,1,0},
			{0,1,1,1,1,2,1,0,0,0},
			{0,0,0,0,1,4,1,0,0,0},
			{0,0,0,0,1,1,1,0,0,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int key;
		int nposx;
		int nposy;
		int fposx = 5, fposy = 5;
		int posx = 5, posy = 5;
		int oldx, oldy;
		int count = 1;
		int off = 1;
		time_t start, end;
		double result;
		clrscr();
		_setcursortype(_NOCURSOR);
		textcolor(WHITE);
		Util::menubar(1);
		Util::Map(mapData);
		Util::drawCharcter(posx, posy);
		start = clock();
		Util::filltext(75, 9, YELLOW);
		Util::xyputstr(75, 9, "sec");
		while ((key = Util::getKey()) != 'q')
		{
			textcolor(RED);
			Util::xyputint(75, 7, count);
			textcolor(WHITE);
			oldx = nposx = posx;
			oldy = nposy = posy;
			switch (key)
			{
			case UPKEY:
			{
				if (posy > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposy--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case DOWNKEY:
			{
				if (posy < MAP_WIDTH - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposy++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case LEFTKEY:
			{
				if (posx > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposx--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case RIGHTKEY:
			{
				if (posx < MAP_HEIGHT - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposx++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case GKEY:
			{
				music::_giveup();
				end = clock();
				result = (double)(end - start);
				Total_time += result;
				clear(0);
				break;
			}
			case SKEY:
			{
				map2();
			}
			case RKEY:
			{
				map1();
			}
			case ZKEY:
			{
				nposx = fposx;
				nposy = fposy;
				count++;
				Util::copy(Undo, mapData);
				break;
			}
			case PKEY:
			{
				if (off == 1) {
					off = 0;
					music::_stop();
					break;
				}
				else if (off == 0) {
					off = 1;
					music::_music();
					break;
				}
			}
			}
			textcolor(WHITE);
			if (mapData[nposy][nposx] == 0)
			{
				posx = nposx;
				posy = nposy;
			}
			if (mapData[nposy][nposx] == 2)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 0;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy++;
					}

					if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy--;
					}

					if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
				}
			}
			if (oldx != posx || oldy != posy)
			{
				Util::Map(mapData);
				textcolor(YELLOW);
				Util::drawCharcter(posx, posy);
				textcolor(WHITE);
			}
			if (mapData[5][2] == 5 && mapData[2][4] == 5 && mapData[4][7] == 5 && mapData[7][5] == 5)
			{
				music::_stage_clear();
				end = clock();
				result = (double)(end - start);
				if (count <= 15) {
					point += 10;
				}
				if (count > 15) {
					point += 5;
				}
				if (result / 1000 <= 5.0) {
					point += 10;
				}
				Total_time += result;
				textcolor(YELLOW);
				count--;
				Util::xyputint(75, 7, count);
				Util::filltext(25, 20, YELLOW);
				Util::xyputstr(25, 20, "S T A G E C L E A R");
				Util::filltext(20, 22, YELLOW);
				Util::xyputstr(20, 22, "Press space key to next stage.");
				Util::filltext(70, 9, YELLOW);
				Util::xyputd(70, 9, result / 1000);
				Util::filltext(75, 9, YELLOW);
				Util::xyputstr(75, 9, "sec");
				while ((key = Util::getKey()) != 'q')
				{
					switch (key)
					{
					case SPACE:
					{
						map2();
					}
					}
				}
			}
		}
		Util::fillbox(0, 0, 100, 100, BLACK);
		textcolor(WHITE);
		clrscr();
	}
	static void map2()
	{
		int mapData[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,0,0,0,0},
			{0,1,0,0,0,1,0,0,0,0},
			{0,1,0,2,2,1,0,1,1,1},
			{0,1,0,2,0,1,0,1,4,1},
			{0,1,1,1,0,1,1,1,4,1},
			{0,0,1,1,0,0,0,0,4,1},
			{0,0,1,0,0,0,1,0,0,1},
			{0,0,1,0,0,0,1,1,1,1},
			{0,0,1,1,1,1,1,0,0,0}
		};

		int Undo[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,0,0,0,0},
			{0,1,0,0,0,1,0,0,0,0},
			{0,1,0,2,2,1,0,1,1,1},
			{0,1,0,2,0,1,0,1,4,1},
			{0,1,1,1,0,1,1,1,4,1},
			{0,0,1,1,0,0,0,0,4,1},
			{0,0,1,0,0,0,1,0,0,1},
			{0,0,1,0,0,0,1,1,1,1},
			{0,0,1,1,1,1,1,0,0,0}
		};

		int key;
		int nposx;
		int nposy;
		int fposx = 2;
		int fposy = 2;
		int posx = 2, posy = 2;
		int oldx, oldy;
		int count = 1;
		int off = 1;
		time_t start, end;
		double result;
		clrscr();
		_setcursortype(_NOCURSOR);

		Util::menubar(2);
		Util::Map(mapData);
		Util::drawCharcter(posx, posy);
		start = clock();

		while ((key = Util::getKey()) != 'q')
		{
			textcolor(RED);
			Util::xyputint(75, 7, count);
			textcolor(WHITE);
			oldx = nposx = posx;
			oldy = nposy = posy;

			switch (key)
			{
			case UPKEY:
			{
				if (posy > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposy--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case DOWNKEY:
			{
				if (posy < MAP_WIDTH - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposy++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case LEFTKEY:
			{
				if (posx > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposx--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case RIGHTKEY:
			{
				if (posx < MAP_HEIGHT - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposx++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case GKEY:
			{
				music::_giveup();
				end = clock();
				result = (double)(end - start);
				Total_time = result;
				clear(1);
				break;
			}
			case RKEY:
			{
				map2();
			}
			case AKEY:
			{
				map1();
			}
			case SKEY:
			{
				map3();
			}
			case ZKEY:
			{
				nposx = fposx;
				nposy = fposy;
				Util::copy(Undo, mapData);
				count++;
				break;
			}
			case PKEY:
			{
				if (off == 1) {
					music::_stop();
					off = 0;
					break;
				}
				else if (off == 0) {
					music::_music();
					off = 1;
					break;
				}
			}
			}
			if (mapData[nposy][nposx] == 0)
			{
				posx = nposx;
				posy = nposy;
			}
			if (mapData[nposy][nposx] == 2)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 0;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
				}
			}
			if (mapData[nposy][nposx] == 4)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
			}
			if (mapData[nposy][nposx] == 5)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy--;
					}
				}
			}
			if (oldx != posx || oldy != posy)
			{
				Util::Map(mapData);
				textcolor(YELLOW);
				Util::drawCharcter(posx, posy);
				textcolor(WHITE);
			}
			if (mapData[4][8] == 5 && mapData[5][8] == 5 && mapData[6][8] == 5)
			{
				music::_stage_clear();
				end = clock();
				result = (double)(end - start);
				if (count <= 100) {
					point += 10;
				}
				if (count > 100) {
					point += 5;
				}
				if (result / 1000 <= 18.0) {
					point += 10;
				}
				Total_time += result;
				textcolor(YELLOW);
				count--;
				Util::xyputint(75, 7, count);
				Util::filltext(25, 20, YELLOW);
				Util::xyputstr(25, 20, "S T A G E C L E A R");
				Util::filltext(20, 22, YELLOW);
				Util::xyputstr(20, 22, "Press space key to next stage.");
				Util::filltext(70, 9, YELLOW);
				Util::xyputd(70, 9, result / 1000);
				Util::filltext(75, 9, YELLOW);
				Util::xyputstr(75, 9, "sec");
				while ((key = Util::getKey()) != 'q')
				{
					switch (key)
					{
					case SPACE:
					{
						map3();
					}
					}
				}
			}
		}
		Util::fillbox(0, 0, 80, 80, BLACK);
		textcolor(WHITE);
		clrscr();
		_start_menu();
	}
	static void map3()
	{
		int mapData[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,1,1,0,0},
			{0,1,0,0,0,0,0,1,1,1},
			{1,1,2,1,1,1,0,0,0,1},
			{1,0,0,0,2,0,0,2,0,1},
			{1,0,4,4,1,0,2,0,1,1},
			{1,1,4,4,1,0,0,0,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int Undo[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,1,1,0,0},
			{0,1,0,0,0,0,0,1,1,1},
			{1,1,2,1,1,1,0,0,0,1},
			{1,0,0,0,2,0,0,2,0,1},
			{1,0,4,4,1,0,2,0,1,1},
			{1,1,4,4,1,0,0,0,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int key;
		int nposx;
		int nposy;
		int fposx = 2;
		int fposy = 5;
		int posx = 2, posy = 5;
		int oldx, oldy;
		int count = 1;
		int off = 1;
		time_t start, end;
		double result;
		clrscr();
		_setcursortype(_NOCURSOR);

		Util::menubar(3);
		Util::Map(mapData);
		Util::drawCharcter(posx, posy);
		start = clock();

		while ((key = Util::getKey()) != 'q')
		{
			textcolor(RED);
			Util::xyputint(75, 7, count);
			textcolor(WHITE);
			oldx = nposx = posx;
			oldy = nposy = posy;

			switch (key)
			{
			case UPKEY:
			{
				if (posy > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposy--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case DOWNKEY:
			{
				if (posy < MAP_WIDTH - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposy++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case LEFTKEY:
			{
				if (posx > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposx--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case RIGHTKEY:
			{
				if (posx < MAP_HEIGHT - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposx++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case GKEY:
			{
				music::_giveup();
				end = clock();
				result = (double)(end - start);
				Total_time = result;
				clear(2);
				break;
			}
			case RKEY:
			{
				map3();
			}
			case AKEY:
			{
				map2();
			}
			case SKEY:
			{
				map4();
			}
			case PKEY:
			{
				if (off == 1) {
					music::_stop();
					off = 0;
					break;
				}
				else if (off == 0) {
					music::_music();
					off = 1;
					break;
				}
			}
			case ZKEY:
			{
				nposx = fposx;
				nposy = fposy;
				count++;
				Util::copy(Undo, mapData);
				break;
			}
			}
			if (mapData[nposy][nposx] == 0)
			{
				posx = nposx;
				posy = nposy;
			}
			if (mapData[nposy][nposx] == 2)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 0;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
				}
			}
			if (mapData[nposy][nposx] == 4)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
			}
			if (mapData[nposy][nposx] == 5)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy--;
					}
				}
			}
			if (oldx != posx || oldy != posy)
			{
				Util::Map(mapData);
				textcolor(YELLOW);
				Util::drawCharcter(posx, posy);
				textcolor(WHITE);
			}
			if (mapData[6][2] == 5 && mapData[6][3] == 5 && mapData[7][2] == 5 && mapData[7][3] == 5)
			{
				music::_stage_clear();
				end = clock();
				result = (double)(end - start);
				if (count <= 130) {
					point += 10;
				}
				if (count > 130) {
					point += 5;
				}
				if (result / 1000 <= 27.0) {
					point += 10;
				}
				Total_time += result;
				textcolor(YELLOW);
				count--;
				Util::xyputint(75, 7, count);
				Util::filltext(25, 20, YELLOW);
				Util::xyputstr(25, 20, "S T A G E C L E A R");
				Util::filltext(20, 22, YELLOW);
				Util::xyputstr(20, 22, "Press space key to next stage.");
				Util::filltext(70, 9, YELLOW);
				Util::xyputd(70, 9, result / 1000);
				Util::filltext(75, 9, YELLOW);
				Util::xyputstr(75, 9, "sec");
				while ((key = Util::getKey()) != 'q')
				{
					switch (key)
					{
					case SPACE:
					{
						map4();
					}
					}
				}
			}
		}
		Util::fillbox(0, 0, 80, 80, BLACK);
		textcolor(WHITE);
		clrscr();
		_start_menu();
	}
	static void map4()
	{
		int mapData[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,0,0,0},
			{0,0,1,1,0,0,1,0,0,0},
			{0,0,1,0,2,0,1,0,0,0},
			{0,0,1,1,2,0,1,1,0,0},
			{0,0,1,1,0,2,0,1,0,0},
			{0,0,1,4,2,0,0,1,0,0},
			{0,0,1,4,4,5,4,1,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int Undo[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,0,0,0},
			{0,0,1,1,0,0,1,0,0,0},
			{0,0,1,0,2,0,1,0,0,0},
			{0,0,1,1,2,0,1,1,0,0},
			{0,0,1,1,0,2,0,1,0,0},
			{0,0,1,4,2,0,0,1,0,0},
			{0,0,1,4,4,5,4,1,0,0},
			{0,0,1,1,1,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int key;
		int nposx;
		int nposy;
		int fposx = 3;
		int fposy = 3;
		int posx = 3, posy = 3;
		int oldx, oldy;
		int count = 1;
		int off = 1;
		time_t start, end;
		double result;
		clrscr();
		_setcursortype(_NOCURSOR);

		Util::menubar(4);
		Util::Map(mapData);
		Util::drawCharcter(posx, posy);
		start = clock();
		while ((key = Util::getKey()) != 'q')
		{
			textcolor(RED);
			Util::xyputint(75, 7, count);
			textcolor(WHITE);
			oldx = nposx = posx;
			oldy = nposy = posy;

			switch (key)
			{
			case UPKEY:
			{
				if (posy > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposy--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case DOWNKEY:
			{
				if (posy < MAP_WIDTH - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposy++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case LEFTKEY:
			{
				if (posx > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposx--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case RIGHTKEY:
			{
				if (posx < MAP_HEIGHT - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposx++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case GKEY:
			{
				music::_giveup();
				end = clock();
				result = (double)(end - start);
				Total_time = result;
				clear(3);
				break;
			}
			case RKEY:
			{
				map4();
			}
			case AKEY:
			{
				map3();
			}
			case SKEY:
			{
				map5();
			}
			case PKEY:
			{
				if (off == 1) {
					music::_stop();
					off = 0;
					break;
				}
				else if (off == 0) {
					music::_music();
					off = 1;
					break;
				}
			}
			case ZKEY:
			{
				nposx = fposx;
				nposy = fposy;
				count++;
				Util::copy(Undo, mapData);
				break;
			}
			}
			if (mapData[nposy][nposx] == 0)
			{
				posx = nposx;
				posy = nposy;
			}
			if (mapData[nposy][nposx] == 2)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 0;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
				}
			}
			if (mapData[nposy][nposx] == 4)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
			}
			if (mapData[nposy][nposx] == 5)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy--;
					}
				}
			}
			if (oldx != posx || oldy != posy)
			{
				Util::Map(mapData);
				textcolor(YELLOW);
				Util::drawCharcter(posx, posy);
				textcolor(WHITE);
			}
			if (mapData[6][3] == 5 && mapData[7][3] == 5 && mapData[7][4] == 5 && mapData[7][5] == 5 && mapData[7][6] == 5)
			{
				music::_stage_clear();
				end = clock();
				result = (double)(end - start);
				if (count <= 40) {
					point += 10;
				}
				if (count > 40) {
					point += 5;
				}
				if (result / 1000 <= 10.0) {
					point += 10;
				}
				Total_time += result;
				textcolor(YELLOW);
				count--;
				Util::xyputint(75, 7, count);
				Util::filltext(25, 20, YELLOW);
				Util::xyputstr(25, 20, "S T A G E C L E A R");
				Util::filltext(20, 22, YELLOW);
				Util::xyputstr(20, 22, "Press space key to next stage.");
				Util::filltext(70, 9, YELLOW);
				Util::xyputd(70, 9, result / 1000);
				Util::filltext(75, 9, YELLOW);
				Util::xyputstr(75, 9, "sec");
				while ((key = Util::getKey()) != 'q')
				{
					switch (key)
					{
					case SPACE:
					{
						map5();
					}
					}
				}
			}
		}
		Util::fillbox(0, 0, 80, 80, BLACK);
		textcolor(WHITE);
		clrscr();
		_start_menu();
	}
	static void map5()
	{
		int mapData[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,1,1,1,0,0,0},
			{0,0,1,0,0,1,1,1,0,0},
			{0,0,1,0,2,0,0,1,0,0},
			{0,1,1,1,0,1,0,1,1,0},
			{0,1,4,1,0,1,0,0,1,0},
			{0,1,4,2,0,0,1,0,1,0},
			{0,1,4,0,0,0,2,0,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int Undo[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,1,1,1,0,0,0},
			{0,0,1,0,0,1,1,1,0,0},
			{0,0,1,0,2,0,0,1,0,0},
			{0,1,1,1,0,1,0,1,1,0},
			{0,1,4,1,0,1,0,0,1,0},
			{0,1,4,2,0,0,1,0,1,0},
			{0,1,4,0,0,0,2,0,1,0},
			{0,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int key;
		int nposx;
		int nposy;
		int fposx = 3;
		int fposy = 2;
		int posx = 3, posy = 2;
		int oldx, oldy;
		int count = 1;
		int off = 1;
		time_t start, end;
		double result;
		clrscr();
		_setcursortype(_NOCURSOR);

		Util::menubar(5);
		Util::Map(mapData);
		Util::drawCharcter(posx, posy);
		start = clock();

		while ((key = Util::getKey()) != 'q')
		{
			textcolor(RED);
			Util::xyputint(75, 7, count);
			textcolor(WHITE);
			oldx = nposx = posx;
			oldy = nposy = posy;

			switch (key)
			{
			case UPKEY:
			{
				if (posy > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposy--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case DOWNKEY:
			{
				if (posy < MAP_WIDTH - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposy++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case LEFTKEY:
			{
				if (posx > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposx--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case RIGHTKEY:
			{
				if (posx < MAP_HEIGHT - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposx++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case GKEY:
			{
				music::_giveup();
				end = clock();
				result = (double)(end - start);
				Total_time = result;
				clear(4);
				break;
			}
			case RKEY:
			{
				map5();
			}
			case AKEY:
			{
				map4();
			}
			case SKEY:
			{
				map6();
			}
			case PKEY:
			{
				if (off == 1) {
					music::_stop();
					off = 0;
					break;
				}
				else if (off == 0) {
					music::_music();
					off = 1;
					break;
				}
			}
			case ZKEY:
			{
				nposx = fposx;
				nposy = fposy;
				count++;
				Util::copy(Undo, mapData);
				break;
			}
			}
			if (mapData[nposy][nposx] == 0)
			{
				posx = nposx;
				posy = nposy;
			}
			if (mapData[nposy][nposx] == 2)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 0;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
				}
			}
			if (mapData[nposy][nposx] == 4)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
			}
			if (mapData[nposy][nposx] == 5)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy--;
					}
				}
			}
			if (oldx != posx || oldy != posy)
			{
				Util::Map(mapData);
				textcolor(YELLOW);
				Util::drawCharcter(posx, posy);
				textcolor(WHITE);
			}
			if (mapData[5][2] == 5 && mapData[6][2] == 5 && mapData[7][2] == 5)
			{
				music::_stage_clear();
				end = clock();
				result = (double)(end - start);
				if (count <= 55) {
					point += 10;
				}
				if (count > 55) {
					point += 5;
				}
				if (result / 1000 <= 12.0) {
					point += 10;
				}
				Total_time += result;
				textcolor(YELLOW);
				count--;
				Util::xyputint(75, 7, count);
				Util::filltext(25, 20, YELLOW);
				Util::xyputstr(25, 20, "S T A G E C L E A R");
				Util::filltext(20, 22, YELLOW);
				Util::xyputstr(20, 22, "Press space key to next stage.");
				Util::filltext(70, 9, YELLOW);
				Util::xyputd(70, 9, result / 1000);
				Util::filltext(75, 9, YELLOW);
				Util::xyputstr(75, 9, "sec");
				while ((key = Util::getKey()) != 'q')
				{
					switch (key)
					{
					case SPACE:
					{
						map6();
					}
					}
				}
			}
		}
		Util::fillbox(0, 0, 80, 80, BLACK);
		textcolor(WHITE);
		clrscr();
		_start_menu();
	}
	static void map6()
	{
		int mapData[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,1,1},
			{0,0,1,1,0,0,1,0,0,1},
			{0,0,1,0,0,0,1,0,0,1},
			{0,0,1,2,0,2,0,2,0,1},
			{0,0,1,0,2,1,1,0,0,1},
			{1,1,1,0,2,0,1,0,1,1},
			{1,4,4,4,4,4,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int Undo[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,1,1},
			{0,0,1,1,0,0,1,0,0,1},
			{0,0,1,0,0,0,1,0,0,1},
			{0,0,1,2,0,2,0,2,0,1},
			{0,0,1,0,2,1,1,0,0,1},
			{1,1,1,0,2,0,1,0,1,1},
			{1,4,4,4,4,4,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int key;
		int nposx;
		int nposy;
		int fposx = 8;
		int fposy = 2;
		int posx = 8, posy = 2;
		int oldx, oldy;
		int count = 1;
		int off = 1;
		time_t start, end;
		double result;
		clrscr();
		_setcursortype(_NOCURSOR);

		Util::menubar(6);
		Util::Map(mapData);
		Util::drawCharcter(posx, posy);
		start = clock();

		while ((key = Util::getKey()) != 'q')
		{
			textcolor(RED);
			Util::xyputint(75, 7, count);
			textcolor(WHITE);
			oldx = nposx = posx;
			oldy = nposy = posy;

			switch (key)
			{
			case UPKEY:
			{
				if (posy > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposy--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case DOWNKEY:
			{
				if (posy < MAP_WIDTH - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposy++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case LEFTKEY:
			{
				if (posx > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposx--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case RIGHTKEY:
			{
				if (posx < MAP_HEIGHT - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposx++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case GKEY:
			{
				music::_giveup();
				end = clock();
				result = (double)(end - start);
				Total_time = result;
				clear(5);
				break;
			}
			case RKEY:
			{
				map6();
			}
			case AKEY:
			{
				map5();
			}
			case SKEY:
			{
				map7();
			}
			case ZKEY:
			{
				nposx = fposx;
				nposy = fposy;
				count++;
				Util::copy(Undo, mapData);
				break;
			}
			case PKEY:
			{
				if (off == 1) {
					music::_stop();
					off = 0;
					break;
				}
				else if (off == 0) {
					music::_music();
					off = 1;
					break;
				}
			}
			}
			if (mapData[nposy][nposx] == 0)
			{
				posx = nposx;
				posy = nposy;
			}
			if (mapData[nposy][nposx] == 2)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 0;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
				}
			}
			if (mapData[nposy][nposx] == 4)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
			}
			if (mapData[nposy][nposx] == 5)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy--;
					}
				}
			}
			if (oldx != posx || oldy != posy)
			{
				Util::Map(mapData);
				textcolor(YELLOW);
				Util::drawCharcter(posx, posy);
				textcolor(WHITE);
			}
			if (mapData[7][1] == 5 && mapData[7][2] == 5 && mapData[7][3] == 5 && mapData[7][4] == 5 && mapData[7][5] == 5)
			{
				music::_stage_clear();
				end = clock();
				result = (double)(end - start);
				if (count <= 130) {
					point += 10;
				}
				if (count > 130) {
					point += 5;
				}
				if (result / 1000 <= 30.0) {
					point += 10;
				}
				Total_time += result;
				textcolor(YELLOW);
				count--;
				Util::xyputint(75, 7, count);
				Util::filltext(25, 20, YELLOW);
				Util::xyputstr(25, 20, "S T A G E C L E A R");
				Util::filltext(20, 22, YELLOW);
				Util::xyputstr(20, 22, "Press space key to next stage.");
				Util::filltext(70, 9, YELLOW);
				Util::xyputd(70, 9, result / 1000);
				Util::filltext(75, 9, YELLOW);
				Util::xyputstr(75, 9, "sec");
				while ((key = Util::getKey()) != 'q')
				{
					switch (key)
					{
					case SPACE:
					{
						map7();
					}
					}
				}
			}
		}
		Util::fillbox(0, 0, 80, 80, BLACK);
		textcolor(WHITE);
		clrscr();
		_start_menu();
	}
	static void map7()
	{
		int mapData[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,1,0},
			{0,1,1,1,0,0,0,0,1,0},
			{1,1,4,0,2,1,1,0,1,1},
			{1,4,4,2,0,2,0,0,0,1},
			{1,4,4,0,2,0,2,0,1,1},
			{1,1,1,1,1,1,0,0,1,0},
			{0,0,0,0,0,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int Undo[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,1,0},
			{0,1,1,1,0,0,0,0,1,0},
			{1,1,4,0,2,1,1,0,1,1},
			{1,4,4,2,0,2,0,0,0,1},
			{1,4,4,0,2,0,2,0,1,1},
			{1,1,1,1,1,1,0,0,1,0},
			{0,0,0,0,0,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int key;
		int nposx;
		int nposy;
		int fposx = 8;
		int fposy = 5;
		int posx = 8, posy = 5;
		int oldx, oldy;
		int count = 1;
		int off = 1;
		time_t start, end;
		double result;
		clrscr();
		_setcursortype(_NOCURSOR);

		Util::menubar(7);
		Util::Map(mapData);
		Util::drawCharcter(posx, posy);
		start = clock();

		while ((key = Util::getKey()) != 'q')
		{
			textcolor(RED);
			Util::xyputint(75, 7, count);
			textcolor(WHITE);
			oldx = nposx = posx;
			oldy = nposy = posy;

			switch (key)
			{
			case UPKEY:
			{
				if (posy > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposy--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case DOWNKEY:
			{
				if (posy < MAP_WIDTH - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposy++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case LEFTKEY:
			{
				if (posx > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposx--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case RIGHTKEY:
			{
				if (posx < MAP_HEIGHT - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposx++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case GKEY:
			{
				music::_giveup();
				end = clock();
				result = (double)(end - start);
				Total_time = result;
				clear(6);
				break;
			}
			case RKEY:
			{
				map7();
			}
			case AKEY:
			{
				map6();
			}
			case SKEY:
			{
				map8();
			}
			case ZKEY:
			{
				nposx = fposx;
				nposy = fposy;
				count++;
				Util::copy(Undo, mapData);
				break;
			}
			case PKEY:
			{
				if (off == 1) {
					music::_stop();
					off = 0;
					break;
				}
				else if (off == 0) {
					music::_music();
					off = 1;
					break;
				}
			}
			}
			if (mapData[nposy][nposx] == 0)
			{
				posx = nposx;
				posy = nposy;
			}
			if (mapData[nposy][nposx] == 2)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 0;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
				}
			}
			if (mapData[nposy][nposx] == 4)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
			}
			if (mapData[nposy][nposx] == 5)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy--;
					}
				}
			}
			if (oldx != posx || oldy != posy)
			{
				Util::Map(mapData);
				textcolor(YELLOW);
				Util::drawCharcter(posx, posy);
				textcolor(WHITE);
			}
			if (mapData[4][2] == 5 && mapData[5][2] == 5 && mapData[5][1] == 5 && mapData[6][2] == 5 && mapData[6][1] == 5)
			{
				music::_stage_clear();
				end = clock();
				result = (double)(end - start);
				if (count <= 55) {
					point += 10;
				}
				if (count > 55) {
					point += 5;
				}
				if (result / 1000 <= 18.0) {
					point += 10;
				}
				Total_time += result;
				textcolor(YELLOW);
				count--;
				Util::xyputint(75, 7, count);
				Util::filltext(25, 20, YELLOW);
				Util::xyputstr(25, 20, "S T A G E C L E A R");
				Util::filltext(20, 22, YELLOW);
				Util::xyputstr(20, 22, "Press space key to next stage.");
				Util::filltext(70, 9, YELLOW);
				Util::xyputd(70, 9, result / 1000);
				Util::filltext(75, 9, YELLOW);
				Util::xyputstr(75, 9, "sec");
				while ((key = Util::getKey()) != 'q')
				{
					switch (key)
					{
					case SPACE:
					{
						map8();
					}
					}
				}
			}
		}
		Util::fillbox(0, 0, 80, 80, BLACK);
		textcolor(WHITE);
		clrscr();
		_start_menu();
	}
	static void map8()
	{
		int mapData[][12] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,1,1,1,1,0,0},
			{0,1,0,0,1,1,0,0,0,1,0,0},
			{0,1,0,0,0,2,0,0,0,1,0,0},
			{0,1,2,0,1,1,1,0,2,1,0,0},
			{0,1,0,1,4,4,4,1,0,1,0,0},
			{1,1,0,1,4,4,4,1,0,1,1,0},
			{1,0,2,0,0,2,0,0,2,0,1,0},
			{1,0,0,0,0,0,1,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0}
		};

		int Undo[][12] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0,0,0},
			{0,1,1,1,1,1,1,1,1,1,0,0},
			{0,1,0,0,1,1,0,0,0,1,0,0},
			{0,1,0,0,0,2,0,0,0,1,0,0},
			{0,1,2,0,1,1,1,0,2,1,0,0},
			{0,1,0,1,4,4,4,1,0,1,0,0},
			{1,1,0,1,4,4,4,1,0,1,1,0},
			{1,0,2,0,0,2,0,0,2,0,1,0},
			{1,0,0,0,0,0,1,0,0,0,1,0},
			{1,1,1,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0}
		};

		int key;
		int nposx;
		int nposy;
		int fposx = 8;
		int fposy = 8;
		int posx = 8, posy = 8;
		int oldx, oldy;
		int count = 1;
		int off = 1;
		time_t start, end;
		double result;
		clrscr();
		_setcursortype(_NOCURSOR);

		Util::menubar(8);
		Util::Map2(mapData);
		Util::drawCharcter(posx, posy);
		start = clock();

		while ((key = Util::getKey()) != 'q')
		{
			textcolor(RED);
			Util::xyputint(75, 7, count);
			textcolor(WHITE);
			oldx = nposx = posx;
			oldy = nposy = posy;

			switch (key)
			{
			case UPKEY:
			{
				if (posy > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposy--;
					count++;
					Util::copy2(mapData, Undo);
					break;
				}
			}
			case DOWNKEY:
			{
				if (posy < MAP_WIDTH2 - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposy++;
					count++;
					Util::copy2(mapData, Undo);
					break;
				}
			}
			case LEFTKEY:
			{
				if (posx > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposx--;
					count++;
					Util::copy2(mapData, Undo);
					break;
				}
			}
			case RIGHTKEY:
			{
				if (posx < MAP_HEIGHT2 - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposx++;
					count++;
					Util::copy2(mapData, Undo);
					break;
				}
			}
			case GKEY:
			{
				music::_giveup();
				end = clock();
				result = (double)(end - start);
				Total_time = result;
				clear(7);
				break;
			}
			case RKEY:
			{
				map8();
			}
			case AKEY:
			{
				map7();
			}
			case SKEY:
			{
				map9();
			}
			case ZKEY:
			{
				nposx = fposx;
				nposy = fposy;
				count++;
				Util::copy2(Undo, mapData);
				break;
			}
			case PKEY:
			{
				if (off == 1) {
					music::_stop();
					off = 0;
					break;
				}
				else if (off == 0) {
					music::_music();
					off = 1;
					break;
				}
			}
			}
			if (mapData[nposy][nposx] == 0)
			{
				posx = nposx;
				posy = nposy;
			}
			if (mapData[nposy][nposx] == 2)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 0;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
				}
			}
			if (mapData[nposy][nposx] == 4)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
			}
			if (mapData[nposy][nposx] == 5)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy--;
					}
				}
			}
			if (oldx != posx || oldy != posy)
			{
				Util::Map2(mapData);
				textcolor(YELLOW);
				Util::drawCharcter(posx, posy);
				textcolor(WHITE);
			}
			if (mapData[5][4] == 5 && mapData[5][5] == 5 && mapData[5][6] == 5 &&
				mapData[6][4] == 5 && mapData[6][5] == 5 && mapData[6][6] == 5)
			{
				music::_stage_clear();
				end = clock();
				result = (double)(end - start);
				if (count <= 220) {
					point += 10;
				}
				if (count > 220) {
					point += 5;
				}
				if (result / 1000 <= 45.0) {
					point += 10;
				}
				Total_time += result;
				textcolor(YELLOW);
				count--;
				Util::xyputint(75, 7, count);
				Util::filltext(25, 20, YELLOW);
				Util::xyputstr(25, 20, "S T A G E C L E A R");
				Util::filltext(20, 22, YELLOW);
				Util::xyputstr(20, 22, "Press space key to next stage.");
				Util::filltext(70, 9, YELLOW);
				Util::xyputd(70, 9, result / 1000);
				Util::filltext(75, 9, YELLOW);
				Util::xyputstr(75, 9, "sec");
				while ((key = Util::getKey()) != 'q')
				{
					switch (key)
					{
					case SPACE:
					{
						map9();
					}
					}
				}
			}
		}
		Util::fillbox(0, 0, 80, 80, BLACK);
		textcolor(WHITE);
		clrscr();
		_start_menu();
	}
	static void map9()
	{
		int mapData[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,1,0},
			{0,0,0,1,0,0,0,0,1,0},
			{0,1,1,1,2,2,2,0,1,0},
			{0,1,0,0,2,4,4,0,1,0},
			{0,1,0,2,4,4,4,1,1,0},
			{0,1,1,1,1,0,0,1,0,0},
			{0,0,0,0,1,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int Undo[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,1,0},
			{0,0,0,1,0,0,0,0,1,0},
			{0,1,1,1,2,2,2,0,1,0},
			{0,1,0,0,2,4,4,0,1,0},
			{0,1,0,2,4,4,4,1,1,0},
			{0,1,1,1,1,0,0,1,0,0},
			{0,0,0,0,1,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int key;
		int nposx;
		int nposy;
		int fposx = 2;
		int fposy = 5;
		int posx = 2, posy = 5;
		int oldx, oldy;
		int count = 1;
		int off = 1;
		time_t start, end;
		double result;
		clrscr();
		_setcursortype(_NOCURSOR);

		Util::menubar(9);
		Util::Map(mapData);
		Util::drawCharcter(posx, posy);
		start = clock();

		while ((key = Util::getKey()) != 'q')
		{
			textcolor(RED);
			Util::xyputint(75, 7, count);
			textcolor(WHITE);
			oldx = nposx = posx;
			oldy = nposy = posy;

			switch (key)
			{
			case UPKEY:
			{
				if (posy > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposy--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case DOWNKEY:
			{
				if (posy < MAP_WIDTH - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposy++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case LEFTKEY:
			{
				if (posx > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposx--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case RIGHTKEY:
			{
				if (posx < MAP_HEIGHT - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposx++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case GKEY:
			{
				music::_giveup();
				end = clock();
				result = (double)(end - start);
				Total_time = result;
				clear(8);
				break;
			}
			case RKEY:
			{
				map9();
			}
			case AKEY:
			{
				map8();
			}
			case SKEY:
			{
				map10();
			}
			case ZKEY:
			{
				nposx = fposx;
				nposy = fposy;
				count++;
				Util::copy(Undo, mapData);
				break;
			}
			case PKEY:
			{
				if (off == 1) {
					music::_stop();
					off = 0;
					break;
				}
				else if (off == 0) {
					music::_music();
					off = 1;
					break;
				}
			}
			}
			if (mapData[nposy][nposx] == 0)
			{
				posx = nposx;
				posy = nposy;
			}
			if (mapData[nposy][nposx] == 2)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 0;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
				}
			}
			if (mapData[nposy][nposx] == 4)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
			}
			if (mapData[nposy][nposx] == 5)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy--;
					}
				}
			}
			if (oldx != posx || oldy != posy)
			{
				Util::Map(mapData);
				textcolor(YELLOW);
				Util::drawCharcter(posx, posy);
				textcolor(WHITE);
			}
			if (mapData[5][5] == 5 && mapData[5][6] == 5 && mapData[6][4] == 5 &&
				mapData[6][5] == 5 && mapData[6][6] == 5)
			{
				music::_stage_clear();
				end = clock();
				result = (double)(end - start);
				if (count <= 40) {
					point += 10;
				}
				if (count > 40) {
					point += 5;
				}
				if (result / 1000 <= 10.0) {
					point += 10;
				}
				Total_time += result;
				textcolor(YELLOW);
				count--;
				Util::xyputint(75, 7, count);
				Util::filltext(25, 20, YELLOW);
				Util::xyputstr(25, 20, "S T A G E C L E A R");
				Util::filltext(20, 22, YELLOW);
				Util::xyputstr(20, 22, "Press space key to next stage.");
				Util::filltext(70, 9, YELLOW);
				Util::xyputd(70, 9, result / 1000);
				Util::filltext(75, 9, YELLOW);
				Util::xyputstr(75, 9, "sec");
				while ((key = Util::getKey()) != 'q')
				{
					switch (key)
					{
					case SPACE:
					{
						map10();
					}
					}
				}
			}
		}
		Util::fillbox(0, 0, 80, 80, BLACK);
		textcolor(WHITE);
		clrscr();
		_start_menu();
	}
	static void map10()
	{
		int mapData[][13] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,1,1,0,0,1,1,1,1,1},
			{0,1,1,0,0,1,0,0,1,0,0,0,1},
			{0,1,0,2,0,1,1,1,1,2,0,0,1},
			{0,1,0,0,2,4,4,4,4,0,2,0,1},
			{0,1,1,0,0,0,0,1,0,0,0,1,1},
			{0,0,1,1,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0}
		};

		int Undo[][13] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,1,1,0,0,1,1,1,1,1},
			{0,1,1,0,0,1,0,0,1,0,0,0,1},
			{0,1,0,2,0,1,1,1,1,2,0,0,1},
			{0,1,0,0,2,4,4,4,4,0,2,0,1},
			{0,1,1,0,0,0,0,1,0,0,0,1,1},
			{0,0,1,1,1,1,1,1,1,1,1,1,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0}
		};

		int key;
		int nposx;
		int nposy;
		int fposx = 9;
		int fposy = 8;
		int posx = 9, posy = 8;
		int oldx, oldy;
		int count = 1;
		int off = 1;
		time_t start, end;
		double result;
		clrscr();
		_setcursortype(_NOCURSOR);

		Util::menubar(10);
		Util::Map3(mapData);
		Util::drawCharcter(posx, posy);
		start = clock();

		while ((key = Util::getKey()) != 'q')
		{
			textcolor(RED);
			Util::xyputint(75, 7, count);
			textcolor(WHITE);
			oldx = nposx = posx;
			oldy = nposy = posy;

			switch (key)
			{
			case UPKEY:
			{
				if (posy > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposy--;
					count++;
					Util::copy3(mapData, Undo);
					break;
				}
			}
			case DOWNKEY:
			{
				if (posy < 13 - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposy++;
					count++;
					Util::copy3(mapData, Undo);
					break;
				}
			}
			case LEFTKEY:
			{
				if (posx > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposx--;
					count++;
					Util::copy3(mapData, Undo);
					break;
				}
			}
			case RIGHTKEY:
			{
				if (posx < 13 - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposx++;
					count++;
					Util::copy3(mapData, Undo);
					break;
				}
			}
			case GKEY:
			{
				music::_giveup();
				end = clock();
				result = (double)(end - start);
				Total_time = result;
				clear(9);
				break;
			}
			case RKEY:
			{
				map10();
			}
			case AKEY:
			{
				map9();
			}
			case SKEY:
			{
				map11();
			}
			case ZKEY:
			{
				nposx = fposx;
				nposy = fposy;
				count++;
				Util::copy3(Undo, mapData);
				break;
			}
			case PKEY:
			{
				if (off == 1) {
					music::_stop();
					off = 0;
					break;
				}
				else if (off == 0) {
					music::_music();
					off = 1;
					break;
				}
			}
			}
			if (mapData[nposy][nposx] == 0)
			{
				posx = nposx;
				posy = nposy;
			}
			if (mapData[nposy][nposx] == 2)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 0;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
				}
			}
			if (mapData[nposy][nposx] == 4)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
			}
			if (mapData[nposy][nposx] == 5)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy--;
					}
				}
			}
			if (oldx != posx || oldy != posy)
			{
				Util::Map3(mapData);
				textcolor(YELLOW);
				Util::drawCharcter(posx, posy);
				textcolor(WHITE);
			}
			if (mapData[7][7] == 5 && mapData[7][6] == 5 && mapData[7][5] == 5 && mapData[7][8] == 5)
			{
				music::_stage_clear();
				end = clock();
				result = (double)(end - start);
				if (count <= 65) {
					point += 10;
				}
				if (count > 65) {
					point += 5;
				}
				if (result / 1000 <= 15.0) {
					point += 10;
				}
				Total_time += result;
				textcolor(YELLOW);
				count--;
				Util::xyputint(75, 7, count);
				Util::filltext(25, 20, YELLOW);
				Util::xyputstr(25, 20, "S T A G E C L E A R");
				Util::filltext(20, 22, YELLOW);
				Util::xyputstr(20, 22, "Press space key to next stage.");
				Util::filltext(70, 9, YELLOW);
				Util::xyputd(70, 9, result / 1000);
				Util::filltext(75, 9, YELLOW);
				Util::xyputstr(75, 9, "sec");
				while ((key = Util::getKey()) != 'q')
				{
					switch (key)
					{
					case SPACE:
					{
						map11();
					}
					}
				}
			}
		}
		Util::fillbox(0, 0, 80, 80, BLACK);
		textcolor(WHITE);
		clrscr();
		_start_menu();
	}
	static void map11()
	{
		int mapData[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,0,0},
			{0,1,1,1,0,0,0,1,0,0},
			{0,1,0,0,2,4,0,1,1,0},
			{0,1,0,0,4,2,4,0,1,0},
			{0,1,1,1,0,5,2,0,1,0},
			{0,0,0,1,0,0,0,1,1,0},
			{0,0,0,1,1,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int Undo[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,1,1,1,1,1,0,0},
			{0,1,1,1,0,0,0,1,0,0},
			{0,1,0,0,2,4,0,1,1,0},
			{0,1,0,0,4,2,4,0,1,0},
			{0,1,1,1,0,5,2,0,1,0},
			{0,0,0,1,0,0,0,1,1,0},
			{0,0,0,1,1,1,1,1,0,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int key;
		int nposx;
		int nposy;
		int fposx = 6;
		int fposy = 3;
		int posx = 6, posy = 3;
		int oldx, oldy;
		int count = 1;
		int off = 1;
		time_t start, end;
		double result;
		clrscr();
		_setcursortype(_NOCURSOR);

		Util::menubar(11);
		Util::Map(mapData);
		Util::drawCharcter(posx, posy);
		start = clock();

		while ((key = Util::getKey()) != 'q')
		{
			textcolor(RED);
			Util::xyputint(75, 7, count);
			textcolor(WHITE);
			oldx = nposx = posx;
			oldy = nposy = posy;

			switch (key)
			{
			case UPKEY:
			{
				if (posy > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposy--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case DOWNKEY:
			{
				if (posy < MAP_WIDTH - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposy++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case LEFTKEY:
			{
				if (posx > 0)
				{
					fposx = nposx;
					fposy = nposy;
					nposx--;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case RIGHTKEY:
			{
				if (posx < MAP_HEIGHT - 1)
				{
					fposx = nposx;
					fposy = nposy;
					nposx++;
					count++;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case GKEY:
			{
				music::_giveup();
				end = clock();
				result = (double)(end - start);
				Total_time = result;
				clear(10);
				break;
			}
			case RKEY:
			{
				map11();
			}
			case AKEY:
			{
				map10();
			}
			case ZKEY:
			{
				nposx = fposx;
				nposy = fposy;
				count++;
				Util::copy(Undo, mapData);
				break;
			}
			case PKEY:
			{
				if (off == 1) {
					music::_stop();
					off = 0;
					break;
				}
				else if (off == 0) {
					music::_music();
					off = 1;
					break;
				}
			}
			}
			if (mapData[nposy][nposx] == 0)
			{
				posx = nposx;
				posy = nposy;
			}
			if (mapData[nposy][nposx] == 2)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 0;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						mapData[posy][posx] = 2;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						mapData[posy][posx] = 2;
						posy--;
					}
				}
			}
			if (mapData[nposy][nposx] == 4)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
			}
			if (mapData[nposy][nposx] == 5)
			{
				posx = nposx;
				posy = nposy;
				mapData[nposy][nposx] = 4;
				if (oldx > posx) {
					if (mapData[nposy][nposx - 1] == 0)
					{
						mapData[posy][posx - 1] = 2;
					}
					else if (mapData[nposy][nposx - 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx++;
					}
					else if (mapData[nposy][nposx - 1] == 4)
					{
						music::_goal();
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx++;
					}
				}
				if (oldx < posx) {
					if (mapData[nposy][nposx + 1] == 0)
					{
						mapData[posy][posx + 1] = 2;
					}
					else if (mapData[nposy][nposx + 1] == 1)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 2)
					{
						mapData[posy][posx] = 5;
						posx--;
					}
					else if (mapData[nposy][nposx + 1] == 4)
					{
						music::_goal();
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posx--;
					}
				}
				if (oldy > posy) {
					if (mapData[nposy - 1][nposx] == 0)
					{
						mapData[posy - 1][posx] = 2;
					}
					else if (mapData[nposy - 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy++;
					}
					else if (mapData[nposy - 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy++;
					}
				}
				if (oldy < posy) {
					if (mapData[nposy + 1][nposx] == 0)
					{
						mapData[posy + 1][posx] = 2;
					}
					else if (mapData[nposy + 1][nposx] == 1)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 2)
					{
						mapData[posy][posx] = 5;
						posy--;
					}
					else if (mapData[nposy + 1][nposx] == 4)
					{
						music::_goal();
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
						music::_goal();
						mapData[posy][posx] = 5;
						posy--;
					}
				}
			}
			if (oldx != posx || oldy != posy)
			{
				Util::Map(mapData);
				textcolor(YELLOW);
				Util::drawCharcter(posx, posy);
				textcolor(WHITE);
			}
			if (mapData[6][5] == 5 && mapData[5][4] == 5 && mapData[4][5] == 5 && mapData[5][6] == 5)
			{
				music::_stage_clear();
				end = clock();
				result = (double)(end - start);
				if (count <= 50) {
					point += 10;
				}
				if (count > 50) {
					point += 5;
				}
				if (result / 1000 <= 15.0) {
					point += 10;
				}
				Total_time += result;
				textcolor(YELLOW);
				count--;
				Util::xyputint(75, 7, count);
				Util::filltext(25, 20, YELLOW);
				Util::xyputstr(25, 20, "S T A G E C L E A R");
				Util::filltext(20, 22, YELLOW);
				Util::xyputstr(20, 22, "Press space key to next stage.");
				Util::filltext(70, 9, YELLOW);
				Util::xyputd(70, 9, result / 1000);
				Util::filltext(75, 9, YELLOW);
				Util::xyputstr(75, 9, "sec");
				while ((key = Util::getKey()) != 'q')
				{
					switch (key)
					{
					case SPACE:
					{
						clear(11);
					}
					}
				}
			}
		}
		Util::fillbox(0, 0, 80, 80, BLACK);
		textcolor(WHITE);
		clrscr();
		_start_menu();
	}
	static void clear(int stage)
	{
		clrscr();
		_setcursortype(_NOCURSOR);
		textcolor(WHITE);
		Util::fillbox(0, 0, 80, 80, BLACK);
		textcolor(WHITE);
		clrscr();
		textcolor(YELLOW);
		Util::xyputstr(35, 3, "┌──────────────────────────────────────────────┐");
		Util::xyputstr(35, 4, "│                                              │");
		Util::xyputstr(35, 5, "│ Total Clear Stage               / 11         │");
		Util::filltext(65, 5, GREEN);
		Util::xyputint(65, 5, stage);
		Util::filltext(66, 6, YELLOW);
		Util::xyputstr(35, 6, "│                                              │");
		Util::xyputstr(35, 7, "│                                              │");
		Util::xyputstr(35, 8, "│                                              │");
		Util::xyputstr(35, 9, "│ Acquisition Score               / 220   point│");
		Util::filltext(65, 9, GREEN);
		Util::xyputint(65, 9, point);
		Util::filltext(70, 9, YELLOW);
		Util::xyputstr(35, 10, "│                                              │");
		Util::xyputstr(35, 11, "│                                              │");
		Util::xyputstr(35, 12, "│                                              │");
		Util::xyputstr(35, 13, "│  Play Time                             sec   │");
		Util::filltext(69, 13, GREEN);
		Util::xyputint(69, 13, Total_time / 1000);
		Util::filltext(75, 13, YELLOW);
		Util::xyputstr(35, 14, "│                                              │");
		Util::xyputstr(35, 15, "└──────────────────────────────────────────────┘");

		Util::filltext(37, 21, YELLOW);
		Util::xyputstr(37, 21, "Congratulations, you have cleared all stages.");
		Util::filltext(44, 23, YELLOW);
		Util::xyputstr(44, 23, "Press space key return to menu.");
		int key;
		while ((key = Util::getKey()) != 'q')
		{
			switch (key)
			{
			case SPACE:
			{
				textcolor(WHITE);
				_start_menu();
			}
			}
		}
	}
};
