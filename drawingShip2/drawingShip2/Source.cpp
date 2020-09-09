#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>	
char ch = '.';
int x = 38, y = 20,Direction=0,bulletInMag=5;
int tempx, tempy=-1;
bool bulletOperate = false;
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void fire(int temp, int x, int y);
void draw_ship(int t,int x, int y)
{
	if (t > 0&&t<80)
	{
		setcolor(3, 0);
		gotoxy(t - 1, y); printf("         ");

		setcolor(2, 4);
		gotoxy(x, y); printf(" <-0-> ");
		Sleep(100);
	}
}
void draw_ship_with_fire(int t,int x, int y)
{
	
	if (t > 0&&t<80)
	{
		setcolor(3, 0);
		gotoxy(t-1 , y); printf("         ");
		setcolor(2, 4);
		gotoxy(x, y); printf(" <-0-> ");
		Sleep(100);
		if (tempy >= 0&&bulletInMag>=0)
		{
			setcolor(6, 0);
			gotoxy(tempx + 2, tempy + 1); printf("   ");
			gotoxy(tempx + 2, tempy); printf(" ' ");
			tempy--;
		}
		if (tempy == -1)
		{
			gotoxy(tempx + 2, 0); printf("   ");
			bulletOperate = false;
		
		}
	}
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
int main()
{

	
	setcursor(0);
	draw_ship(x,x, y);
	gotoxy(38, 22);
	/*setcolor(6, 0);
	printf("Bullet left = %d",bulletInMag);*/
	do {
		
		if (_kbhit()) {
			
			ch = _getch();
			switch (ch)
			{
			case 'a': Direction = -1; break;
			case 's': Direction = 0; break;
			case 'd': Direction = 1; break;
			case ' ': bulletOperate = true;
			}
			while (1)
			{
				if(x+Direction<0|| x + Direction>80)
				{
					if (x + Direction < 0 ) x  = 1;
					else x = 79;
				}
				
				if (bulletOperate == true && bulletInMag >= 0)
				{
					if(tempy<0) tempy = y-2,tempx=x, bulletInMag--;
					draw_ship_with_fire(x, x += Direction, y);
					setcolor(6, 0);
					gotoxy(38, 22);
					/*if(bulletInMag>=0)
					printf("Bullet left = %d", bulletInMag);
					else 
					printf("Bullet left = 0 Leaw ai wen ying tam here a rai");*/
				}
				else draw_ship(x, x += Direction, y);
			
				Sleep(100);
				if (_kbhit()) break;
			}
					
			fflush(stdin);
		}
		
	} while (ch != 'x');
	return 0;
}