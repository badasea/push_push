#pragma once
#include <iostream>
#include <conio.h>
#include "Consola.h"
#include "keycode.h"
#include "Util.h"

class Tutorial
{
public:
	static void tutorial()
	{
		int mapData[][10] = {	// y,x 반대로 생각하자
			{1,1,1,1,1,1,1,1,1,1},
			{1,1,4,1,1,0,1,4,1,1},
			{1,0,0,0,1,0,0,0,0,1},
			{1,0,2,0,0,0,0,2,0,1},
			{1,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,0,0,0,0,0,1},
			{1,1,0,0,0,0,0,0,0,1},
			{1,4,0,0,0,0,0,2,0,1},
			{1,1,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1}
		};

		int Undo[][10] = {	// y,x 반대로 생각하자
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0}
		};

		int key;
		int nposx;
		int nposy;
		int posx = 5, posy = 5;
		int oldx, oldy;
		int fposx = 5, fposy = 5;
		clrscr();
		_setcursortype(_NOCURSOR);

		Util::filltext(3, 3, WHITE);
		Util::xyputstr(7, 3, "본 화면은 튜토리얼입니다. 방향키 → ← ↑ ↓눌러 이동해보세요.");
		Util::filltext(40, 20, WHITE);
		Util::xyputstr(40, 20, "다시 메인화면으로 돌아가려면 'q'키를 눌러주세요.");
		Util::filltext(40, 22, GREEN);
		Util::xyputstr(40, 22, "'P'키를 눌러 배경 음악을 ON OFF 할 수 있어요.");
		Util::filltext(68, 14, WHITE);
		Util::xyputstr(68, 14, "▦ 는 벽입니다. 플레이어는 이곳을 통과할수 없어요.");
		Util::filltext(68, 16, WHITE);
		Util::xyputstr(68, 16, "'Z' 키는 이전 스텝으로 돌아가는 키입니다.");
		Util::filltext(68, 8, BLUE);
		Util::xyputstr(68, 8, "●");
		Util::filltext(69, 8, WHITE);
		Util::xyputstr(69, 8, "을   속에 넣어 주세요.");
		Util::filltext(72, 8, YELLOW);
		Util::xyputstr(72, 8, "※");
		Util::filltext(68, 10, BLUE);
		Util::xyputstr(68, 10, "●");
		Util::filltext(69, 10, WHITE);
		Util::xyputstr(69, 10, "을   속에 들어가면    로 변해요.");
		Util::filltext(88, 10, RED);
		Util::xyputstr(88, 10, "◎");
		Util::filltext(72, 10, YELLOW);
		Util::xyputstr(72, 10, "※");
		Util::filltext(68, 12, WHITE);
		Util::xyputstr(68, 12, "모든    을    로 만들어주세요.");
		Util::filltext(73, 12, BLUE);
		Util::xyputstr(73, 12, "●");
		Util::filltext(79, 12, RED);
		Util::xyputstr(79, 12, "◎");
		Util::filltext(68, 6, GREEN);
		Util::xyputstr(68, 6, "■");
		Util::filltext(69, 6, WHITE);
		Util::xyputstr(69, 6, " 는 당신의 캐릭터입니다.");
		Util::Map(mapData);
		Util::drawCharcter(posx, posy);

		while ((key = Util::getKey()) != 'q')
		{
			oldx = nposx = posx;
			oldy = nposy = posy;
			switch (key)
			{
			case UPKEY:
			{
				if (posy > 0)
				{
					fposy = nposy;
					fposx = nposx;
					nposy--;
					Util::copy(mapData, Undo);
					break;
				}
			}
			case DOWNKEY:
			{
				if (posy < MAP_WIDTH - 1)
				{
					fposy = nposy;
					fposx = nposx;
					nposy++;
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
					Util::copy(mapData, Undo);
					break;
				}
			}
			case ZKEY:
			{
				nposx = fposx;
				nposy = fposy;
				Util::copy(Undo, mapData);
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
						mapData[posy][posx - 1] = 5;
					}
					else if (mapData[nposy][nposx - 1] == 5)
					{
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
						mapData[posy][posx + 1] = 5;
					}
					else if (mapData[nposy][nposx + 1] == 5)
					{
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
						mapData[posy - 1][posx] = 5;
					}
					else if (mapData[nposy - 1][nposx] == 5)
					{
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
						mapData[posy + 1][posx] = 5;
					}
					else if (mapData[nposy + 1][nposx] == 5)
					{
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
		}
		Util::fillbox(0, 0, 100, 100, BLACK);
		textcolor(WHITE);
		clrscr();
	}
};
