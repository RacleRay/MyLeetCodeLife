#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>


#define WIDE 60			// 宽度
#define HIGH 20			// 高度

// 一个身体的对象
struct BODY {
	int X;
	int Y;
};

// 定义蛇对象
struct SNAKE {
	struct BODY body[WIDE*HIGH];
	int size;
}snake;			// 一个蛇对象

				// 定义食物对象
struct FOOD {
	int X;
	int Y;
}food;			// 一个食物对象

int score = 0;	// 分数

int kx = 0;
int ky = 0;

int lastX = 0;
int lastY = 0;

int sleepSecond = 200;

// 声明函数
void initSnake(void);
void initFood(void);
void initUI(void);
void playGame(void);
void initWall(void);
void showScore(void);