#define _CRT_SECURE_NO_WARNINGS

#include "snake.h"


int main(void) {
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = sizeof(cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	srand(time(NULL));

	initSnake();	// 初始化蛇
	initFood();		// 初始化食物
	initWall();		// 画墙
	initUI();		// 画蛇和食物

	playGame();		// 启动游戏

	showScore();	// 打印分数

	system("pause");
	return EXIT_SUCCESS;
}


void initSnake(void) {
	snake.size = 2;

	snake.body[0].X = WIDE / 2;
	snake.body[0].Y = HIGH / 2;

	snake.body[1].X = WIDE / 2 - 1;
	snake.body[1].Y = HIGH / 2;

	return;
}


void initFood(void) {
	food.X = rand() % WIDE;
	food.Y = rand() % HIGH;
	return;
}


void initWall(void) {
	for (size_t i = 0; i <= HIGH; i++)
	{
		for (size_t j = 0; j <= WIDE; j++)
		{
			if (j == WIDE)
			{
				printf("|");
			}
			else if (i == HIGH)
			{
				printf("_");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}


void showScore(void) {
	COORD coord;
	coord.X = 0;
	coord.Y = HIGH + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	printf("  Game Over!!!\n");
	printf("  得分：%d\n\n\n", score);
}


void  initUI(void) {
	COORD coord = { 0 };

	for (size_t i = 0; i < snake.size; i++) {
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if (i == 0)
			putchar('@');
		else
			putchar('*');
	}

	coord.X = lastX;
	coord.Y = lastY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(' ');

	coord.X = food.X;
	coord.Y = food.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar('#');
}


void playGame(void) {
	char key = 'd';
	char prevKey = key;

	while (snake.body[0].X >= 0 && snake.body[0].X < WIDE
		&& snake.body[0].Y >= 0 && snake.body[0].Y < HIGH) {
		initUI();

		if (_kbhit()) { 
			key = _getch();
		}

		if ((key == 'w' && prevKey == 's') ||
			(key == 's' && prevKey == 'w') ||
			(key == 'a' && prevKey == 'd') ||
			(key == 'd' && prevKey == 'a')) {
			key = prevKey;
			prevKey = key;
		}
		else {
			prevKey = key;
		}

		switch (key) {
		case 'w': kx = 0; ky = -1; break;
		case 's': kx = 0; ky = +1; break;
		case 'd': kx = +1; ky = 0; break;
		case 'a': kx = -1; ky = 0; break;
		default:
			break;
		}

		for (size_t i = 1; i < snake.size; i++) {
			if (snake.body[0].X == snake.body[i].X
				&& snake.body[0].Y == snake.body[i].Y)
			{
				return;
			}
		}

		if (snake.body[0].X == food.X && snake.body[0].Y == food.Y) {
			initFood();
			snake.size++;
			score += 10;
			if (sleepSecond > 100) {
				sleepSecond -= 10;
			}
		}

		lastX = snake.body[snake.size - 1].X;
		lastY = snake.body[snake.size - 1].Y;

		for (size_t i = snake.size - 1; i > 0; i--)
		{
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}
		snake.body[0].X += kx;
		snake.body[0].Y += ky;

		Sleep(sleepSecond);
	}

	return;
}