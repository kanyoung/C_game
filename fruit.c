#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <conio.h>
#include <time.h>
#include <windows.h> 

void * print_a(void *); //�߳�a ���ƽ��� 
void * print_b(void *);//�߳�b ���������ƶ� 
void * print_c(void *);//�߳�c ����ˮ������&&�ཻ�ж� 
void gameUi();//���˵� 
void beginGame();//��ʼ��Ϸ 
void gameover();//������Ϸ 
void save();//�浵 
void loading();//���� 

int loc = 20;//���ӳ�ʼλ�� 
char bg[15][40] = {0};//�������� 
char basket = '_';//����ͼ�� 
int score = 0;//�÷� 
int islive = 1;//�Ƿ���� 

int main(){
    srand((unsigned)time(NULL)); 
	system("color f0");//style 
	system("mode con cols=40 lines=20");//���ڴ�С 
	gameUi();
    return 0;
}

void gameUi(){
	int select = 0;
	system("cls");
	printf("��ˮ��\n\n");
	printf("1.��ʼ��Ϸ\n");
	printf("2.����浵\n");
	printf("3.��Ϸ����\n");
	printf("0.�˳���Ϸ\n\n\n");
	printf("please input num and press enter:");
	scanf("%d", &select);
	switch(select){
		case 1 : beginGame();
				 break;
		case 2 : loading();
				 break;
		case 3 : system("cls");
				 printf("��a d ��������ƶ�����סˮ���÷֣�����ʧ�ܣ�");
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
    // �����߳�A B C
    if(pthread_create(&t0, NULL, print_a, NULL) == -1){
        exit(1);
    }
    if(pthread_create(&t1, NULL, print_b, NULL) == -1){
        exit(1);
    }
    if(pthread_create(&t2, NULL, print_c, NULL) == -1){
        exit(1);
    }
    // �ȴ��߳̽���
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
// �߳�A ����
void * print_a(void *a){
	system("cls");
	
	int i = 0, j = 0;
	//���ƽ��� 
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
	//��ʼλ�� 
	bg[12][loc] = basket;
	//ˢ�½��� 
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
		printf("\n������%d", score);
		Sleep(100);
		system("cls");
	}
    return NULL;
}
// �߳�B ����
void * print_b(void *b){
	//�������������ƶ� 
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
// �߳�C ����
void * print_c(void *c){
	int fruitlocat = 0;
	int i = 0; 
	while(1){
		if(!islive) return NULL;
		fruitlocat = rand() % 40; //ˮ��λ���������
		//����ˮ������ 
		for(i = 1; i < 14; i++){
			bg[i][fruitlocat] = '@';
			if(i>1)
			bg[i-1][fruitlocat] = ' ';
			Sleep(500);
			//�÷��ж� 
			if(i == 12 && fruitlocat == loc)
			{
				bg[i][fruitlocat] = ' ';
				score+=20;
				break;
			}
			//ʧ���ж� 
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
	printf("1.���¿�ʼ\n2.�����˵�\n3.������Ϸ\n4.�˳���Ϸ\n��ѡ��");
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
					printf("����ɹ���");
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

