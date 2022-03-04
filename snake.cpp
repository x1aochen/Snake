#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<list>
using namespace std;
//����̨�ĳ��ȱ���Ϊ������� idk

//��
typedef struct _SNAKE {
	int x;
	int y;
	struct _SNAKE* next;
}Snake;

void gameStart(); //��Ϸ��ʼ
void welcome(); //��ӭ����
void createMap(); //������ͼ
void gotoxy(int x,int y); //���ù��
void InitSnake(); //��ʼ����
void moveSnake(int direction,Snake* food,bool& haveFood,bool& end); //�ƶ���
void runSnake(); //�����߽�����Ϸ
void eatFood(bool& haveFood,Snake* food); //�������ʳ��
void gameEnd(); //��Ϸ����

Snake* g_phead = nullptr;

enum {up = 72,down = 80,RIGHT = 77,LEFT = 75}; //ö�ٷ���

int main()
{
	gameStart(); 
	welcome();
	createMap();
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
	system("mode con cols=100 lines=40"); //�޸Ŀ���̨��С
}

void createMap() 
{
	for (int i = 0; i < 60; i += 2) {

		gotoxy(i, 0);
		cout << "*";
		gotoxy(i, 29);
		cout << "*";
	}
	for (int i = 0; i < 30; i++) {
		gotoxy(0, i);
		cout << "*";
		gotoxy(58, i);
		cout << "*";
	}	
}

void gotoxy(int x, int y) 
{
	COORD pos = { x,y };//����
	//����winows.h���൱�ڷ��ؿ���̨����ID
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //�õ�����̨
	
	SetConsoleCursorPosition(hOut,pos);//���ù��λ��
}

void InitSnake() 
{
	Snake* temp = new Snake();
	temp->x = 30;
	temp->y = 10;
	temp->next = nullptr;
	g_phead = temp;

	for (int i = 0; i < 4; i++) {
		Snake* p = new Snake();
		p->x = 30 + i; //�����ӡ��ʼ��
		p->y = 10;
		p->next = nullptr;
		temp->next = p;
		temp = p;
	}
		
	temp = g_phead;
	while (temp != nullptr) {
		gotoxy(temp->x, temp->y);
		cout << "*";
		temp = temp->next;
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
				if (direction == down) break;
				direction = up;
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
				if (direction == up) break;
				direction = down;
				break;
			}
		}
		eatFood(haveFood,food);

		moveSnake(direction,food,haveFood,end);

		Sleep(100); //�ٶ�
	}
	gameEnd();
}
//��βɾͷ
void moveSnake(int direction,Snake* food,bool& haveFood,bool& end) {

	//��β��
	Snake* p = g_phead;
	while (p->next != nullptr) {
		p = p->next;
	}
	//�ж��Ƿ�ײǽ
	if (p->x == 0 || p->x == 58 || p->y == 0 || p->y == 28) {
		end = false;
	}
	
	if (p->x == food->x && p->y == food->y) {
		//p->next = food;
		haveFood = true;
	}
	//�ӽڵ�
	Snake* temp = new Snake();
	temp->next = nullptr;
	temp->x = 0;
	temp->y = 0;
	p->next = temp;
	if (direction == RIGHT) {
		temp->x = p->x + 2;
		temp->y = p->y;
	}
	else if (direction == LEFT){
		temp->x = p->x - 2;
		temp->y = p->y;
	}
	else if (direction == up) {
		temp->x = p->x;
		temp->y = p->y -1;
	}
	else if (direction == down) {
		temp->x = p->x;
		temp->y = p->y + 1;
	}

	//��ӡ�½ڵ�
	gotoxy(temp->x, temp->y);
	cout << "*";
	if (!haveFood) {
		gotoxy(g_phead->x, g_phead->y);
		cout << " ";
		//ɾ��ͷ
		temp = g_phead->next;
		delete g_phead;
		g_phead = temp;
	}
}
//����һ��boolֵ���жϵ�ǰ��ͼ�Ƿ���ʳ��
void eatFood(bool& haveFood,Snake* food) {
	if (haveFood) {
		unsigned seed;
		seed = time(0);
		srand(seed);

		int foodx = rand() % 58 + 2;
		int foody = rand() % 28 + 2;

		food->x = foodx;
		food->y = foody;
		food->next = nullptr;

		gotoxy(food->x, food->y);
		cout << "*";
		haveFood = false;
	}
}	

void gameEnd() {
	system("pause"); //��ͣ
	system("cls"); //����
	cout << "you are die!";
}