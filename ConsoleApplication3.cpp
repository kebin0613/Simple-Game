// ConsoleApplication3.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define MAP_WIDTH 70
#define MAP_HEIGHT 28

#define FOOD 3
#define CHARACTOR 2
#define WALL 1
#define NONE 0

int map[MAP_HEIGHT][MAP_WIDTH];
int state = 0; //Game State

int charactorX, charactorY;

void RenderMap(); // Map rendering
void InitializeMapAndCharactor(); // Initialize map And charactor
void GameLoop(); // Game loop
void FoodRandomDrop(); // Food random drop
void MoveCharactor(int kbcode); // Charactor key code check and move
void RemoveConsoleCursor(); // Remove console cursor
int FoodCheckAndHandle(); // Food check and handling

int main()
{
	RemoveConsoleCursor();
	InitializeMapAndCharactor();

	GameLoop();

	system("pause");

	return 0;
}

void RemoveConsoleCursor() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void RenderMap() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			switch (map[i][j])
			{
			case NONE:
				printf(" ");
				break;
			case WALL:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("#");
				break;
			case FOOD:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("$");
				break;
			default:
				break;
			}

			if (i == charactorY && j == charactorX) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("@");
			}
		}

		printf("\n");
	}
}

int FoodCheckAndHandle() {
	int check = map[charactorY][charactorX] == FOOD ? 1 : 0;

	if (check) {
		map[charactorY][charactorX] = NONE;
		FoodRandomDrop();
	}

	return check;
}

void InitializeMapAndCharactor() {
	state = !state;
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (i != 0 && j != 0 && j != MAP_WIDTH - 1 && i != MAP_HEIGHT - 1)
				map[i][j] = NONE;
			else
				map[i][j] = WALL;
		}
	}

	charactorY = MAP_HEIGHT / 2;
	charactorX = MAP_WIDTH / 2;

	FoodRandomDrop();
}

void FoodRandomDrop() {
	int randY;
	int randX;
	
	do {
		randY = rand() % MAP_HEIGHT - 1;
		randX = rand() % MAP_WIDTH + 1;
	} while (map[randY][randX] != NONE);

	map[randY][randX] = FOOD;
}

void MoveCharactor(int kbcode) {
	printf("%d", kbcode);
	int tmpX = charactorX;
	int tmpY = charactorY;
	map[tmpY][tmpX] = NONE;

	switch (kbcode)
	{
	case 72:
		--charactorY;
		break;
	case 80:
		++charactorY;
		break;
	case 75:
		--charactorX;
		break;
	case 77:
		++charactorX;
		break;

	default:
		break;
	}

	if (map[charactorY][charactorX] == WALL) {
		charactorX = tmpX;
		charactorY = tmpY;
	}
}

void GameLoop() {
	while (state) {
		system("cls");
		RenderMap();
		MoveCharactor(_getch());

		int check = FoodCheckAndHandle();
		if (check) {
			system("cls");
			RenderMap();
		}
	}
}

