#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<list>
using namespace std;
//控制台的长度比例为宽的两倍 idk

//蛇
typedef struct _SNAKE {
	int x;
	int y;
	struct _SNAKE* next;
}Snake;

void gameStart(); //游戏开始
void welcome(); //欢迎界面
void createMap(); //创建地图
void gotoxy(int x,int y); //设置光标
void InitSnake(); //初始化蛇
void moveSnake(int direction,Snake* food,bool& haveFood,bool& end); //移动蛇
void runSnake(); //控制蛇进行游戏
void eatFood(bool& haveFood,Snake* food); //随机生成食物
void gameEnd(); //游戏结束

Snake* g_phead = nullptr;

enum {up = 72,down = 80,RIGHT = 77,LEFT = 75}; //枚举方向

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
	//换页面
	system("pause"); //暂停
	system("cls"); //清屏
}

void gameStart() 
{
	system("mode con cols=100 lines=40"); //修改控制台大小
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
	COORD pos = { x,y };//坐标
	//包含winows.h，相当于返回控制台窗口ID
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //得到控制台
	
	SetConsoleCursorPosition(hOut,pos);//设置光标位置
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
		p->x = 30 + i; //横向打印初始蛇
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
				if (direction == down) break;
				direction = up;
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
				if (direction == up) break;
				direction = down;
				break;
			}
		}
		eatFood(haveFood,food);

		moveSnake(direction,food,haveFood,end);

		Sleep(100); //速度
	}
	gameEnd();
}
//增尾删头
void moveSnake(int direction,Snake* food,bool& haveFood,bool& end) {

	//找尾巴
	Snake* p = g_phead;
	while (p->next != nullptr) {
		p = p->next;
	}
	//判断是否撞墙
	if (p->x == 0 || p->x == 58 || p->y == 0 || p->y == 28) {
		end = false;
	}
	
	if (p->x == food->x && p->y == food->y) {
		//p->next = food;
		haveFood = true;
	}
	//加节点
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

	//打印新节点
	gotoxy(temp->x, temp->y);
	cout << "*";
	if (!haveFood) {
		gotoxy(g_phead->x, g_phead->y);
		cout << " ";
		//删除头
		temp = g_phead->next;
		delete g_phead;
		g_phead = temp;
	}
}
//设置一个bool值来判断当前地图是否有食物
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
	system("pause"); //暂停
	system("cls"); //清屏
	cout << "you are die!";
}