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

//检测方向函数 再加蛇则需要分配键位
int GetDirections(int NoSnake)
{
	if(NoSnake==0)
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
	if(NoSnake==1)
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
	else
		return 0;
}

//此处需要根据Number_Snake特殊优化
int fla[Number_Snake]={0};

//判断蛇是否死亡（碰壁或者碰身体）的函数
int Death(int x[Number_Snake], int y[Number_Snake], int fla[Number_Snake])
{
	int sum=0;
	int lastfla[Number_Snake];
	for(int m=0;m<Number_Snake;m++)
	{
		lastfla[m]=fla[m];
	}
	
	//判定新移动到的点是否重合
	for(int m=0;m<Number_Snake;m++)
	{
		if(m==Number_Snake) break;
		for(int n=m+1;n<Number_Snake;n++)
		{
			if((x[m]==x[n])&&(y[m]==y[n]))
			{
				fla[m]=1;
				fla[n]=1;
			}
		}
	}
	
	for(int m=0;m<Number_Snake;m++)
	{
		if(fla[m]==0) sum=sum+1;
	}
	
	//判定新移动到的点是否和自己和其他蛇身重合
	if(sum!=0)
	{
		for(int m=0;m<Number_Snake;m++)
		{
			if(fla[m]==1) continue;
			if(x[m]<wall.Left_bond||x[m]>=wall.Right_bond||y[m]<wall.Up_bond||y[m]>=wall.Down_bond)
				fla[m]=1;
			else
			{
				Node* part=snake[m].head->next;
				for(int i=snake[m].length-1;i>3;i-=1,part=part->next)
				{
					if((x[m]==part->x)&&(y[m]==part->y)) fla[m]=1;
				}
				if(fla[m]==0)
				{
					for(int n=0;n<Number_Snake;n++)
					{
						if((n==m)||(fla[n]==1)) continue;
						else
						{
							Node* part=snake[n].head->next;
							for(int i=snake[n].length-1;i>0;i-=1,part=part->next)
							{
								if((x[m]==part->x)&&(y[m]==part->y)) fla[m]=1;
							}
						}
					}
				}
			}
		}
	}
	
	sum=0;
	for(int m=0;m<Number_Snake;m++)
	{
		if(fla[m]==0) sum=sum+1;
	}
	
	//对比上次的fla与本次的fla，抹除本回合死亡的蛇
	for(int m=0;m<Number_Snake;m++)
	{
		if(sum==0) break;
		if((lastfla[m]==0)&&(fla[m]==1))
		{
			Node* part=snake[m].head;
			for(int i=snake[m].length;i>0;i-=1,part=part->next)
			{
				setfillstyle(SOLID_FILL,BLACK);
				bar(part->x+1,part->y+1,part->x-1+Point_width,part->y-1+Point_height);
			}
		}
	}
	
	return sum;
}

//增加蛇数目需要增加if语句条件
//判断输入y与n的函数，为判断开始函数所用。
bool Choose_open()
{
	while(1)
	{
		if((GetKeyState(68)<0)&&(GetKeyState(VK_RIGHT)<0))			//同时按右则开始，同时按左则关闭
			return true;
		else if((GetKeyState(65)<0)&&(GetKeyState(VK_LEFT)<0))
			return false;
	}
}

//GAME OVER后再选择函数，使用Choose_open()。
bool Choose_again()
{
	CloseGraph();
	system("CLS");
	Over_title();
	return Choose_open();
}

bool Game()
{
	int key[Number_Snake]={0};
	
	Direction Snake_of_direction[Number_Snake];				//保存蛇运行方向的方向变量
	for(int i=0;i<Number_Snake;i++)
	{
		Snake_of_direction[i]=righ;
	}
	
	Node random_node;										//随机生成的食物点
	Node new_node,old_node;									//替换点
	bool temp1=true;
	bool temp2=false;
	int randx,randy;
	
	//首次创建蛇体
	for(int i=0;i<Number_Snake;i++)
	{
		snake[i].Create(i);
		fla[i]=0;
	}
	
	while(1)
	{
		for(int i=0;i<Number_Snake;i++)
		{
			key[i]=GetDirections(i);
		}
		
		//判断蛇行进方向的可行性
		for(int i=0;i<Number_Snake;i++)
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
		
		//死亡后再按右方向键则复活
		for(int m=0;m<Number_Snake;m++)
		{
			if((key[m]==4)&&(fla[m]==1))
			{
				int relivefla=0;
				for(int n=0;n<Number_Snake;n++)
				{
					if((n==m)||(fla[n]==1)) continue;
					else
					{
						Node* part=snake[n].head;
						for(int i=snake[n].length;i>0;i-=1,part=part->next)
						{
							if((wall.Left_bond==part->x)&&(wall.Up_bond+m*Interval_Snake==part->y)) relivefla=relivefla+1;
							if(((wall.Left_bond+Point_width)==part->x)&&(wall.Up_bond+m*Interval_Snake==part->y)) relivefla=relivefla+1;
						}
					}
				}
				if(relivefla==0)
				{
					snake[m].Create(m);
					fla[m]=0;
				}
			}
		}
		
		if(temp1==true)
		{
			srand(time(NULL));
			
			//以下循环产生食物点，要求合法（不生成于蛇身上）
			do
			{
				temp2=false;
				randx=wall.Left_bond+rand()%Column_of_Wall*Point_width;	
				randy=wall.Up_bond+rand()%Row_of_Wall*Point_height;
				//randy=40;
				for(int m=0;m<Number_Snake;m++)
					for(Node* p=snake[m].head;p!=NULL;p=p->next)
						if((randx==p->x)&&(randy==p->y))
						{temp2=true;break;}
			}
			while(temp2==true);
			random_node.x=randx;
			random_node.y=randy;
			random_node.next=NULL;
			
			//食物用蓝色色块标出
			setfillstyle(SOLID_FILL,BLUE);
			bar(random_node.x+1,random_node.y+1,random_node.x+Point_width-1,random_node.y+Point_height-1);
			temp1=false;
		}
		
		int headx[Number_Snake], heady[Number_Snake];
		for(int i=0;i<Number_Snake;i++)
		{
			headx[i]=snake[i].tail->x;
			heady[i]=snake[i].tail->y;
			
			//由以上获得的蛇的行进方向，导出蛇头部的下一坐标
			switch(Snake_of_direction[i])
			{
			case (Direction)up: heady[i]=heady[i]-Point_height;break;
			case (Direction)down: heady[i]=heady[i]+Point_height;break;
			case (Direction)lef: headx[i]=headx[i]-Point_width;break;
			case (Direction)righ: headx[i]=headx[i]+Point_width;break;
			}
		}
		
		int sum=0;
		sum=Death(headx,heady,fla);
		
		if(sum!=0)
		{
			for(int m=0;m<Number_Snake;m++)
			{
				if(fla[m]==1) continue;
				
				//判断是否吃掉食物，即判断（新）头部是否在食物上，若是，则增加头上的一节。
				if(headx[m]==random_node.x&&heady[m]==random_node.y)
				{
					snake[m].Grow(random_node);
					
					//增添蛇体则需要增设颜色区别
					switch(m)
					{
						case 0:setfillstyle(SOLID_FILL,GREEN);break;
						case 1:setfillstyle(SOLID_FILL,CYAN);break;
					}
					
					bar(random_node.x+1,random_node.y+1,random_node.x-1+Point_width,random_node.y-1+Point_height);
					temp1=true;
				}
				
				//若不是，则头移动一步，尾移动一步，即生长后删节。
				else
				{
					new_node.x=headx[m];new_node.y=heady[m];new_node.next=NULL;
					snake[m].Grow(new_node);
					old_node=snake[m].Anti_grow();
					
					//增添蛇体则需要增设颜色区别
					switch(m)
					{
						case 0:setfillstyle(SOLID_FILL,GREEN);break;
						case 1:setfillstyle(SOLID_FILL,CYAN);break;
					}
					
					bar(new_node.x+1,new_node.y+1,new_node.x-1+Point_width,new_node.y-1+Point_height);
					setfillstyle(SOLID_FILL,BLACK);
					bar(old_node.x+1,old_node.y+1,old_node.x-1+Point_width,old_node.y-1+Point_height);
				}
			}
			
			//再次构建围墙，保证围墙原状，否则会出现锯齿状。
			wall.build_Wall();
		}
		else
			return Choose_again();
		
		//控制此段循环的运行速度。
		Sleep(Speed_snake);	
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