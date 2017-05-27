#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "title.h"
#include "graphics.h"
#include <iomanip>
using namespace std;
int Speed_snake = 60;										//̰���߳������е��ٶȣ���ʼֵΪ60��

void InitGraph()											//��ͼ��ģʽ
{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"");
	cleardevice();
}

void CloseGraph()											//�ر�ͼ��ģʽ
{
	cleardevice();
	closegraph();
}

int GetDirections(int NoSnake)								//��ⷽ���� �ټ�������Ҫ�����λ
{
	switch(NoSnake)
	{
		case 0:
		{
			if(GetKeyState(VK_UP)<0) 
				return 1;									//1�����ϼ� 
			else if(GetKeyState(VK_DOWN)<0) 
				return 2;									//2�����¼�
			else if(GetKeyState(VK_LEFT)<0) 
				return 3;									//3�������
			else if(GetKeyState(VK_RIGHT)<0)
				return 4;									//4�����Ҽ�
			else
				return 0; 
		}
		break;
		case 1:
		{
			if(GetKeyState(87)<0) 
				return 1;									//w�����ϼ� 
			else if(GetKeyState(83)<0) 
				return 2;									//s�����¼�
			else if(GetKeyState(65)<0) 
				return 3;									//a�������
			else if(GetKeyState(68)<0)
				return 4;									//d�����Ҽ�
			else
				return 0; 
		}
		break;
		default:break;
	}
}

int Death(int x[Number_Snake],int y[Number_Snake])										//�ж����Ƿ����������ڻ��������壩�ĺ���
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

bool Choose_open()											//�ж�����y��n�ĺ�����Ϊ�жϿ�ʼ�������á�
{
	while(1)
	{
		if((GetKeyState(68)<0)&&(GetKeyState(VK_RIGHT)<0))			//ͬʱ������ʼ��ͬʱ������ر�
			return ture;
		else if((GetKeyState(65)<0)&&(GetKeyState(VK_LEFT)<0))
			return false;
	}
}

bool Game()
{
	int key[Number_Snake]=0;
	
	Direction Snake_of_direction[Number_Snake];				//���������з���ķ������
	for(i=0;i<Number_Snake;i++)
	{
		Snake_of_direction[i]=righ;
	}
	
	Node random_node;										//������ɵ�ʳ���
	Node new_node,old_node;									//�滻��
	bool temp1=true;
	bool temp2=false;
	int randx,randy;
	
	for(i=0;i<Number_Snake;i++)								//�״δ�������
	{
		snake[i].Create(i);
	}
	
	while(1)
	{
		if(temp1==true)
		{
			srand(time(NULL));
			do												//����ѭ������ʳ��㣬Ҫ��Ϸ����������������ϣ���
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
			setfillstyle(SOLID_FILL,BLUE);					//ʳ������ɫɫ����
			bar(random_node.x+1,random_node.y+1,random_node.x+Point_width-1,random_node.y+Point_height-1);
			temp1=false;
		}
		
		for(i=0;i<Number_Snake;i++)
		{
			key[i]=GetDirections(i);
		}
		
		for(i=0;i<Number_Snake;i++)							//�ж����н�����Ŀ�����
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
			switch(Snake_of_direction[i])							//�����ϻ�õ��ߵ��н����򣬵�����ͷ������һ����
			{
			case (Direction)up: heady[i]=heady[i]-Point_height;break;
			case (Direction)down: heady[i]=heady[i]+Point_height;break;
			case (Direction)lef: headx[i]=headx[i]-Point_width;break;
			case (Direction)righ: headx[i]=headx[i]+Point_width;break;
			}
		}
		
		if(Death(headx,heady)!=0)								//ͷ���ƶ�֮���ж����Ƿ�����
			return Choose_again();							//������������GAME OVER��ѡ�񻷽�
		else
		{
			if(headx==random_node.x&&heady==random_node.y)	//�ж��Ƿ�Ե�ʳ����жϣ��£�ͷ���Ƿ���ʳ���ϣ����ǣ�������ͷ�ϵ�һ�ڡ�
			{
				snake.Grow(random_node);
				setfillstyle(SOLID_FILL,GREEN);
				bar(random_node.x+1,random_node.y+1,random_node.x-1+Point_width,random_node.y-1+Point_height);
				temp1=true;
			}
			else											//�����ǣ���ͷ�ƶ�һ����β�ƶ�һ������������ɾ�ڡ�
			{
				new_node.x=headx;new_node.y=heady;new_node.next=NULL;
				snake.Grow(new_node);
				old_node=snake.Anti_grow();
				setfillstyle(SOLID_FILL,GREEN);
				bar(new_node.x+1,new_node.y+1,new_node.x-1+Point_width,new_node.y-1+Point_height);
				setfillstyle(SOLID_FILL,BLACK);
				bar(old_node.x+1,old_node.y+1,old_node.x-1+Point_width,old_node.y-1+Point_height);
			}
			wall.build_Wall();								//�ٴι���Χǽ����֤Χǽԭ״���������־��״��
		}
		Sleep(Speed_snake);									//���ƴ˶�ѭ���������ٶȡ�
	}
}

int main()
{
	Open_title();
	if(!Choose_open())										//����ѡ�񿪹�
		return 0;
	else
	{
		do
		{
			system("cls");									//����ǰ����
			InitGraph();
			wall.build_Wall();								//�����״ν���Χǽ
		}
		while(Game());
		CloseGraph();
		return 0;
	}
}