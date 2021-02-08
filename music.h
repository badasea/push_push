#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

using namespace std;

class music
{
public:
	static void _music() {
		PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NOSTOP);
	}
	static void _goal() {
		PlaySound(TEXT("goal.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
	}
	static void _stage_clear() {
		PlaySound(TEXT("stage_clear.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	static void _giveup() {
		PlaySound(TEXT("game_over.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	static void _stop() {
		PlaySound(NULL, 0, 0);
	}
};
