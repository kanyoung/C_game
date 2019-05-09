#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <conio.h>
#include <time.h>
#include <windows.h> 

void * print_a(void *); //线程a 绘制界面 
void * print_b(void *);//线程b 控制篮子移动 
void * print_c(void *);//线程c 控制水果下落&&相交判断 
void gameUi();//主菜单 
void beginGame();//开始游戏 
void gameover();//结束游戏 
void save();//存档 
void loading();//读档 

int loc = 20;//篮子初始位置 
char bg[15][40] = {0};//界面数组 
char basket = '_';//篮子图形 
int score = 0;//得分 
int islive = 1;//是否活着 

int main(){
    srand((unsigned)time(NULL)); 
	system("color f0");//style 
	system("mode con cols=40 lines=20");//窗口大小 
	gameUi();
    return 0;
}

void gameUi(){
	int select = 0;
	system("cls");
	printf("接水果\n\n");
	printf("1.开始游戏\n");
	printf("2.载入存档\n");
	printf("3.游戏帮助\n");
	printf("0.退出游戏\n\n\n");
	printf("please input num and press enter:");
	scanf("%d", &select);
	switch(select){
		case 1 : beginGame();
				 break;
		case 2 : loading();
				 break;
		case 3 : system("cls");
				 printf("用a d 控制盆的移动，接住水果得分，否则失败！");
				 system("pause");
				 gameUi();
				 break;					 		 				 				 
		case 5 : exit(1);
	}
}

void beginGame(){
	islive = 1;
	pthread_t t0;
    pthread_t t1;
    pthread_t t2;
    // 创建线程A B C
    if(pthread_create(&t0, NULL, print_a, NULL) == -1){
        exit(1);
    }
    if(pthread_create(&t1, NULL, print_b, NULL) == -1){
        exit(1);
    }
    if(pthread_create(&t2, NULL, print_c, NULL) == -1){
        exit(1);
    }
    // 等待线程结束
    void * result;
    if(pthread_join(t0, &result) == -1){
        exit(1);
    }
    if(pthread_join(t1, &result) == -1){
        exit(1);
    }
    if(pthread_join(t2, &result) == -1){
        exit(1);
    }
}
// 线程A 方法
void * print_a(void *a){
	system("cls");
	
	int i = 0, j = 0;
	//绘制界面 
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 40; j++)
		{
			if(i == 0 || i == 14 || j == 0 || j == 39)
			{
				bg[i][j] = '*';
			}
			else{
				bg[i][j] = ' ';
			}
			
		}
	} 
	//初始位置 
	bg[12][loc] = basket;
	//刷新界面 
	while(1){	
		if(!islive) return NULL;
		for (i = 0; i < 15; i++)
		{
			for (j = 0; j < 40; j++) 
			{
				printf("%c", bg[i][j]);			
			}
			printf("\n");
		} 
		printf("\n分数：%d", score);
		Sleep(100);
		system("cls");
	}
    return NULL;
}
// 线程B 方法
void * print_b(void *b){
	//控制篮子左右移动 
	while(1){
		if(!islive) return NULL;
		if(getch() == 'a' && loc > 1){ 
			loc-=1;
			bg[12][loc] = basket;
			bg[12][loc+1] = ' ';
		}
		if(getch() == 'd' && loc < 38){ 
			loc+=1;
			bg[12][loc] = basket;
			bg[12][loc-1] = ' ';
		}
	}	
    return NULL;
}
// 线程C 方法
void * print_c(void *c){
	int fruitlocat = 0;
	int i = 0; 
	while(1){
		if(!islive) return NULL;
		fruitlocat = rand() % 40; //水果位置随机生成
		//控制水果下落 
		for(i = 1; i < 14; i++){
			bg[i][fruitlocat] = '@';
			if(i>1)
			bg[i-1][fruitlocat] = ' ';
			Sleep(500);
			//得分判断 
			if(i == 12 && fruitlocat == loc)
			{
				bg[i][fruitlocat] = ' ';
				score+=20;
				break;
			}
			//失败判断 
			if(i == 13)
			{
				bg[i][fruitlocat] = ' ';
				islive = 0;
				gameover();
			}					
		}
	}	
    return NULL;
}
void gameover(){
	int a = 0;
	system("cls");
	printf("Game Over");
	Sleep(1500);
	system("cls");
	printf("1.重新开始\n2.回主菜单\n3.保存游戏\n4.退出游戏\n请选择：");
	scanf("%d", &a);
	switch(a){
		case 1 : 	system("cls");
					score = 0;
					beginGame();
				 	break;
		case 2 : 	system("cls");
				 	gameUi();
	 	 	 		break;
		case 3 :    system("cls");
					save();
					printf("保存成功！");
					system("pause");
					gameUi();
					break;
		case 0 :    exit(1);
	}
}

void save(){
	FILE*fp = NULL;
	char s[20] = {0};
	fp = fopen("save.txt", "w");
	sprintf(s, "%d", score);
	fprintf(fp, s);
	fclose(fp);
}

void loading(){
	FILE*fp = NULL;
	char s[20];
	fp = fopen("save.txt", "r");
	fgets(s, 20, fp);
	score = atoi(s);
	fclose(fp);
	beginGame();
}

