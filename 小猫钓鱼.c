#include <stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include <conio.h>

void hidden_cursor();
void face();
void create_fish();
void gotoxy(int x,int y);
void move_fish(int x, int y);

int isok = 0;
int Ty = 10;
int islive = 1;
int score = 0;
int Time = 60;
int isover = 0;
int goal = 100;
DWORD WINAPI thread(LPVOID lpParameter);
DWORD WINAPI timeout(LPVOID lpParameter);

HANDLE h1;
HANDLE h2;
int main()
{
	int num = 0;
	Time = 60;
	score = 0;
	isover = 0;
	TerminateThread(h1, 0);
	system("cls");
	printf("\t\t\t\t小猫钓鱼\n\n\n\n1.PLAY GAME\n2.GAME HELP\n3.QUIT GAME\n\n\n\n\n\nPlease input number(1,2,3):"); 
	scanf("%d", &num);
	if(num == 1){
		h1 = CreateThread(NULL,0,thread,NULL,0,NULL);
		h2 = CreateThread(NULL,0,timeout,NULL,0,NULL);
		system("cls");
		system("title CatFishing");
		system("mode con cols=80 lines=40");
		srand(time(NULL));
		hidden_cursor();
		face();
		create_fish();
	}else if(num == 2){
		system("cls");
		printf("按空格键发射鱼钩，在规定时间内完成得分！");
		system("pause");
		main();
	}else if(num == 3){
		exit(0);
	}else{
		system("cls");
		printf("请输入正确的选项！");
		system("pause");
		main();
	}
	main();
}
void hidden_cursor() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut,&cci);
	cci.bVisible=0;
	SetConsoleCursorInfo(hOut,&cci);
}

void face(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED); 
	printf("SCORE:\t\t\t\t\t\tTIME:\n\n\n");
	printf("\t                              M     M   \n");
	printf("\t                            /`````````\\ \n");
	printf("\t                            | &     & | \n");
	printf("\t                            \\~___O___~/ \n");
	printf("\t                     ---------(     )、 \n");
	printf("\t                      |       (_____)  \n");
	printf("\t                      |       .I. .I.~~   \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t                      |\n");
	

	
}

void create_fish(){
	int x = 70;
	while(!isover){
		move_fish(x, rand() % 15 + 15);
	}
	if(score >= goal)
	{
		printf("恭喜通关!");
		system("pause");
		return;
	}	
	printf("GAME OVER");
		system("pause");	
		return;
}
void gotoxy(int x,int y) {
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}

void move_fish(int x, int y){
	
	int i = 0;

	while(1){
		if(isover || score >= goal) return;
		isok = 1;
		gotoxy(x, y);
		printf(" ____\n");
		gotoxy(x+5, y);
		printf(" ");
		
		gotoxy(x, y+1);
		printf("/*   \\/|\n");
		gotoxy(x+8, y+1);
		printf(" ");
		
		gotoxy(x, y+2);
		printf("\\____/\\|\n");
		gotoxy(x+8, y+2);
		printf(" ");
		
		gotoxy(10, 0);
		printf("%d/%d", score, goal);
		
		gotoxy(55, 0);
		printf("%d", Time);
		
		isok = 0;

		Sleep(100);
		x--;
		if (Ty >= y && Ty <= y+2 && x <= 30 && x+8 >= 30){
			for (i = 1; i < 9; i++)
			{
				isok = 1;
				gotoxy(x+i, y);
				printf(" ");
				gotoxy(x+i, y+1);
				printf(" ");
				gotoxy(x+i, y+2);
				printf(" ");
			}
			score+=20;
			islive = 0;
			isok = 0;
			break;
		}
		if(x == 0) {
			for (i = 1; i < 9; i++)
			{
				isok = 1;
				gotoxy(x+i, y);
				printf(" ");
				gotoxy(x+i, y+1);
				printf(" ");
				gotoxy(x+i, y+2);
				printf(" ");
			}
			isok = 0;
			break;
		}
	}
}
DWORD WINAPI thread(LPVOID lpParameter) {
	
	while(1){
		if(getch() == 32)
		{
			while(Ty < 35){
				if(isover) return;
				if(isok == 0){
					if (islive == 0)
						break;
					gotoxy(30, Ty++);
					printf("|");
					Sleep(100);
				}	
			}	
			while(Ty > 10){
				if(isover) return;
				if(isok == 0){
					gotoxy(30, Ty--);
					printf(" ");
					Sleep(100);
				}
			}
		
			islive = 1;	
		}
	}
}

DWORD WINAPI timeout(LPVOID lpParameter) {
	while(--Time){
		Sleep(1000);	
	}
	if(Time == 0){
		system("cls");
		isover = 1;
	}
}
