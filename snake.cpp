#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<list>
#include<graphics.h>
using namespace std;

//蛇
typedef struct _SNAKE {
	int x;
	int y;
	_SNAKE* next;
	_SNAKE* prev;
}Snake;

void gameStart(); //游戏开始
void welcome(); //欢迎界面
//void createMap(); //创建地图
//void gotoxy(int x,int y); //设置光标
void InitSnake(); //初始化蛇
void moveSnake(int direction,Snake* food,bool& haveFood,bool& end); //移动蛇
void runSnake(); //控制蛇进行游戏
void eatFood(bool& haveFood,Snake* food); //随机生成食物
void gameEnd(); //游戏结束

Snake* g_phead = nullptr;
Snake* g_ptail = nullptr;

enum {UP = 72,DOWN = 80,RIGHT = 77,LEFT = 75}; //枚举方向


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
	//换页面
	system("pause"); //暂停
	system("cls"); //清屏
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
		p->next = temp; //绑定前后节点
		temp->prev = p;
		p = temp;
		solidcircle(temp->x, temp->y, 10);
		g_ptail = temp;
	}
}
//必须是死循环，不然程序会终止
void runSnake() {
	int direction = RIGHT;
	bool haveFood = true;
	Snake* food = new Snake();
	bool end = true;
	while (end) {
		//判断是否输入
		int ch = 77;
		
		if (_kbhit()) {
			ch = _getch();
			switch (ch) {
			case 72: //上
				if (direction == DOWN) break;
				direction = UP;
				break;
			case 75: //左
				if (direction == RIGHT) break;
				direction = LEFT;
				break;
			case 77: //右
				if (direction == LEFT) break;
				direction = RIGHT;
				break;
			case 80: //下
				if (direction == UP) break;
				direction = DOWN;
				break;
			}
		}

		if (haveFood)
		eatFood(haveFood,food);

		moveSnake(direction,food,haveFood,end);

		Sleep(200); //速度
	}
	gameEnd();
}

void moveSnake(int direction, Snake* food, bool& haveFood, bool& end)
{
	//判断是否撞墙
	if (g_phead->x == 0 || g_phead->x == 480 ||
		g_phead->y == 0 || g_phead->y == 480) {
		end = false;
	}
	//判断是否吃到食物
	if (g_phead->x == food->x && g_phead->y == food->y) {
		//p->next = food;
		haveFood = true;
	}
	//增头删尾
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
	 //打印新节点
	solidcircle(temp->x, temp->y, 10);
	g_phead = temp;

	if (!haveFood) { //如果没吃到到食物，删除尾部节点
	clearcircle(g_ptail->x, g_ptail->y, 10);
	g_ptail = g_ptail->prev;
	}
}
//设置一个bool值来判断当前地图是否有食物
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
	system("pause"); //暂停
	system("cls"); //清屏
	cout << "you are die!";
}