#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "title.h"
#include "graphics.h"
#include <iomanip>
using namespace std;
int Speed_snake = 60;										//贪吃蛇程序运行的速度，初始值为60。

void InitGraph()											//打开图形模式
{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"");
	cleardevice();
}

void CloseGraph()											//关闭图形模式
{
	cleardevice();
	closegraph();
}

int GetDirections(int NoSnake)								//检测方向函数 再加蛇则需要分配键位
{
	switch(NoSnake)
	{
		case 0:
		{
			if(GetKeyState(VK_UP)<0) 
				return 1;									//1代表上键 
			else if(GetKeyState(VK_DOWN)<0) 
				return 2;									//2代表下键
			else if(GetKeyState(VK_LEFT)<0) 
				return 3;									//3代表左键
			else if(GetKeyState(VK_RIGHT)<0)
				return 4;									//4代表右键
			else
				return 0; 
		}
		break;
		case 1:
		{
			if(GetKeyState(87)<0) 
				return 1;									//w代表上键 
			else if(GetKeyState(83)<0) 
				return 2;									//s代表下键
			else if(GetKeyState(65)<0) 
				return 3;									//a代表左键
			else if(GetKeyState(68)<0)
				return 4;									//d代表右键
			else
				return 0; 
		}
		break;
		default:break;
	}
}

int Death(int x[Number_Snake],int y[Number_Snake])										//判断蛇是否死亡（碰壁或者碰身体）的函数
{
	
	int i=0;
	if(x<wall.Left_bond||x>=wall.Right_bond||y<wall.Up_bond||y>=wall.Down_bond)
		return true;
	else 
	{
		for(m=0;m<Number_Snake;m++)
		{
			Node* part=snake[m].head->next;
			for(i=snake[m].length-1;i>3;i-=1,part=part->next)
			{
				if((x==part->x)&&(y==part->y)) return true;
			}
		}
		return false;
	}
}

bool Choose_open()											//判断输入y与n的函数，为判断开始函数所用。
{
	while(1)
	{
		if((GetKeyState(68)<0)&&(GetKeyState(VK_RIGHT)<0))			//同时按右则开始，同时按左则关闭
			return ture;
		else if((GetKeyState(65)<0)&&(GetKeyState(VK_LEFT)<0))
			return false;
	}
}

bool Game()
{
	int key[Number_Snake]=0;
	
	Direction Snake_of_direction[Number_Snake];				//保存蛇运行方向的方向变量
	for(i=0;i<Number_Snake;i++)
	{
		Snake_of_direction[i]=righ;
	}
	
	Node random_node;										//随机生成的食物点
	Node new_node,old_node;									//替换点
	bool temp1=true;
	bool temp2=false;
	int randx,randy;
	
	for(i=0;i<Number_Snake;i++)								//首次创建蛇体
	{
		snake[i].Create(i);
	}
	
	while(1)
	{
		if(temp1==true)
		{
			srand(time(NULL));
			do												//以下循环产生食物点，要求合法（不生成于蛇身上）。
			{
				temp2=false;
				randx=wall.Left_bond+rand()%Column_of_Wall*Point_width;	
				randy=wall.Up_bond+rand()%Row_of_Wall*Point_height;
				for(int m=0;m<Number_Snake;m++)
					for(Node* p=snake[m].head;p!=NULL;p=p->next)
						if(randx==p->x&&randy==p->y)
						{temp2=true;break;}
			}
			while(temp2==true);
			random_node.x=randx;
			random_node.y=randy;
			random_node.next=NULL;
			setfillstyle(SOLID_FILL,BLUE);					//食物用蓝色色块标出
			bar(random_node.x+1,random_node.y+1,random_node.x+Point_width-1,random_node.y+Point_height-1);
			temp1=false;
		}
		
		for(i=0;i<Number_Snake;i++)
		{
			key[i]=GetDirections(i);
		}
		
		for(i=0;i<Number_Snake;i++)							//判断蛇行进方向的可行性
		{
			if(key[i]!=0)											
			{
				switch(key[i])
				{
				case 1: if(Snake_of_direction[i]!=(Direction)down)
							Snake_of_direction[i]=(Direction)up;
					break;
				case 2: if(Snake_of_direction[i]!=(Direction)up)
							Snake_of_direction[i]=(Direction)down;
					break;
				case 3: if(Snake_of_direction[i]!=(Direction)righ)
							Snake_of_direction[i]=(Direction)lef;
					break;
				case 4: if(Snake_of_direction[i]!=(Direction)lef)
							Snake_of_direction[i]=(Direction)righ;
					break;
				default:break;
				}
			}
		}
		
		
		int headx[Number_Snake], heady[Number_Snake];
		for(i=0;i<Number_Snake;i++)
		{
			headx[i]=snake[i].tail->x;
			heady[i]=snake[i].tail->y;
			switch(Snake_of_direction[i])							//由以上获得的蛇的行进方向，导出蛇头部的下一坐标
			{
			case (Direction)up: heady[i]=heady[i]-Point_height;break;
			case (Direction)down: heady[i]=heady[i]+Point_height;break;
			case (Direction)lef: headx[i]=headx[i]-Point_width;break;
			case (Direction)righ: headx[i]=headx[i]+Point_width;break;
			}
		}
		
		if(Death(headx,heady)!=0)								//头部移动之后，判断蛇是否死亡
			return Choose_again();							//若死亡，进入GAME OVER再选择环节
		else
		{
			if(headx==random_node.x&&heady==random_node.y)	//判断是否吃掉食物，即判断（新）头部是否在食物上，若是，则增加头上的一节。
			{
				snake.Grow(random_node);
				setfillstyle(SOLID_FILL,GREEN);
				bar(random_node.x+1,random_node.y+1,random_node.x-1+Point_width,random_node.y-1+Point_height);
				temp1=true;
			}
			else											//若不是，则头移动一步，尾移动一步，即生长后删节。
			{
				new_node.x=headx;new_node.y=heady;new_node.next=NULL;
				snake.Grow(new_node);
				old_node=snake.Anti_grow();
				setfillstyle(SOLID_FILL,GREEN);
				bar(new_node.x+1,new_node.y+1,new_node.x-1+Point_width,new_node.y-1+Point_height);
				setfillstyle(SOLID_FILL,BLACK);
				bar(old_node.x+1,old_node.y+1,old_node.x-1+Point_width,old_node.y-1+Point_height);
			}
			wall.build_Wall();								//再次构建围墙，保证围墙原状，否则会出现锯齿状。
		}
		Sleep(Speed_snake);									//控制此段循环的运行速度。
	}
}

int main()
{
	Open_title();
	if(!Choose_open())										//开局选择开关
		return 0;
	else
	{
		do
		{
			system("cls");									//运行前清屏
			InitGraph();
			wall.build_Wall();								//开局首次建立围墙
		}
		while(Game());
		CloseGraph();
		return 0;
	}
}