#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<list>
#include<graphics.h>
using namespace std;

//��
typedef struct _SNAKE {
	int x;
	int y;
	_SNAKE* next;
	_SNAKE* prev;
}Snake;

void gameStart(); //��Ϸ��ʼ
void welcome(); //��ӭ����
//void createMap(); //������ͼ
//void gotoxy(int x,int y); //���ù��
void InitSnake(); //��ʼ����
void moveSnake(int direction,Snake* food,bool& haveFood,bool& end); //�ƶ���
void runSnake(); //�����߽�����Ϸ
void eatFood(bool& haveFood,Snake* food); //�������ʳ��
void gameEnd(); //��Ϸ����

Snake* g_phead = nullptr;
Snake* g_ptail = nullptr;

enum {UP = 72,DOWN = 80,RIGHT = 77,LEFT = 75}; //ö�ٷ���


int main()
{

	gameStart(); 
	//welcome();
	//createMap();
	InitSnake();
	runSnake();
	return 0;
}

void welcome()
{
	cout << "welcome the snake" << endl;
	//��ҳ��
	system("pause"); //��ͣ
	system("cls"); //����
}

void gameStart() 
{

	initgraph(480,480);
	setbkcolor(CYAN);
	cleardevice();
}

void InitSnake() 
{
	Snake* p = new Snake();
	p->x = 100;
	p->y = 20;
	p->next = nullptr;
	g_phead = p;
	solidcircle(p->x, p->y, 10);

	for (int i = 0; i <= 60; i = i + 20) {
		Snake* temp = new Snake();
		temp->x = 80 - i; 
		temp->y = 20;
		temp->next = nullptr;
		p->next = temp; //��ǰ��ڵ�
		temp->prev = p;
		p = temp;
		solidcircle(temp->x, temp->y, 10);
		g_ptail = temp;
	}
}
//��������ѭ������Ȼ�������ֹ
void runSnake() {
	int direction = RIGHT;
	bool haveFood = true;
	Snake* food = new Snake();
	bool end = true;
	while (end) {
		//�ж��Ƿ�����
		int ch = 77;
		
		if (_kbhit()) {
			ch = _getch();
			switch (ch) {
			case 72: //��
				if (direction == DOWN) break;
				direction = UP;
				break;
			case 75: //��
				if (direction == RIGHT) break;
				direction = LEFT;
				break;
			case 77: //��
				if (direction == LEFT) break;
				direction = RIGHT;
				break;
			case 80: //��
				if (direction == UP) break;
				direction = DOWN;
				break;
			}
		}

		if (haveFood)
		eatFood(haveFood,food);

		moveSnake(direction,food,haveFood,end);

		Sleep(200); //�ٶ�
	}
	gameEnd();
}

void moveSnake(int direction, Snake* food, bool& haveFood, bool& end)
{
	//�ж��Ƿ�ײǽ
	if (g_phead->x == 0 || g_phead->x == 480 ||
		g_phead->y == 0 || g_phead->y == 480) {
		end = false;
	}
	//�ж��Ƿ�Ե�ʳ��
	if (g_phead->x == food->x && g_phead->y == food->y) {
		//p->next = food;
		haveFood = true;
	}
	//��ͷɾβ
	Snake* temp = new Snake();
	g_phead->prev = temp;
	temp->next = g_phead;
	temp->prev = nullptr;

	switch (direction) {
	case (RIGHT): {
		temp->x = g_phead->x + 20;
		temp->y = g_phead->y;
		break;
	}
	case (LEFT): {
		temp->x = g_phead->x - 20;
		temp->y = g_phead->y;
		break;
	}
	case (UP): {
		temp->x = g_phead->x;
		temp->y = g_phead->y - 20;
		break;
	}
	case (DOWN): {
		temp->x = g_phead->x;
		temp->y = g_phead->y + 20;
		break;
	}
	}
	 //��ӡ�½ڵ�
	solidcircle(temp->x, temp->y, 10);
	g_phead = temp;

	if (!haveFood) { //���û�Ե���ʳ�ɾ��β���ڵ�
	clearcircle(g_ptail->x, g_ptail->y, 10);
	g_ptail = g_ptail->prev;
	}
}
//����һ��boolֵ���жϵ�ǰ��ͼ�Ƿ���ʳ��
void eatFood(bool& haveFood,Snake* food)
{
		unsigned seed;
		seed = time(0);
		srand(seed);

		int foodx = rand() % 20;
		int foody = rand() % 20;

		food->x = foodx * 20;
		food->y = foody * 20;

		solidcircle(food->x, food->y, 10);
		haveFood = false;
}

void gameEnd() {
	system("pause"); //��ͣ
	system("cls"); //����
	cout << "you are die!";
}