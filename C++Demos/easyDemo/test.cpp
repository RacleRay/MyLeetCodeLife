#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <mmsyscom.h>
#pragma comment(lib, "winmm.lib")


void setTitle();
void BGM();


int main() {
	initgraph(640, 480, SHOWCONSOLE);

	BGM();

	setbkcolor(WHITE);
	cleardevice();

	int x = 50, y = 50;
	while (1) {
		cleardevice();
		setfillcolor(BLUE);
		fillcircle(x, y, 20);

		char key = _getch();
		printf("%d, %c \n", key, key);
		switch (key) {
		case 72:
		case 'w':
		case 'W':
			y-=3;
			printf("向上");
			break;
		case 80:
		case 's':
		case 'S':
			y+= 3;
			printf("向下");
			break;
		case 75:
		case 'a':
		case 'A':
			x-= 3;
			printf("向左");
			break;
		case 77:
		case 'd':
		case 'D':
			x+= 3;
			printf("向右");
			break;
		}

		// windows库的异步键盘控制
		/*if (GetAsyncKeyState(VK_UP)) {
			...
		}*/
	}


	getchar();

	closegraph();
	getchar();
	return 0;
};


void setTitle() {
	HWND hnd = GetHWnd();
	SetWindowText(hnd, "GO");
	int isok = MessageBox(NULL, "Simple", "OH", MB_OKCANCEL);
	if (isok == IDOK) {
		printf("OK");
	}
	else if (isok==IDCANCEL) {
		printf("Canceled");
	}
}


void BGM() {
	mciSendString("open ./sound.mp3 alias Bgm", NULL, 0, NULL);
	mciSendString("play Bgm repeat", NULL, 0, NULL);

	// if ...
	//     mciSendString("close Bgm", NULL, 0, NULL);
}