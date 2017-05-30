#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "graphics.h"
#include <iomanip>

#define Row_of_Wall		20
#define Column_of_Wall	20
#define Point_width     20
#define Point_height	20
#define Number_Snake	2		//�ߵ�����
#define Interval_Snake  10*Point_height		//����֮�����10�����᷽��
using namespace std;

class Point
{
public:
	int x;
	int y;
};

class Node: virtual public Point
{
public:
	Node* next;
};

class Wall
{
public:
	int Up_bond;
	int Right_bond;
	int Down_bond;
	int Left_bond;
	void build_Wall();
};

void Wall::build_Wall()
{
	int i=0;
	setbkcolor(LIGHTGREEN);
	//ȷ�����߽�
	Left_bond=(getmaxx()+1-Point_width*Row_of_Wall)/2;
	Up_bond=(getmaxy()+1-Point_height*Column_of_Wall)/2;
	Right_bond=Left_bond+Point_width*Column_of_Wall;
	Down_bond=Up_bond+Point_height*Row_of_Wall;

	//�����´������
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	rectangle(Left_bond,Up_bond,Right_bond,Down_bond);
	
	//�����´��뻭���߿���
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	i=Left_bond;
	for(;;i+=1)
	{
		rectangle(i,Up_bond,i+1,Up_bond+1);
		rectangle(i,Down_bond-1,i+1,Down_bond);
		if(i>=Right_bond) break;
	}
	i=Up_bond;
	for(;;i+=1)
	{
		rectangle(Left_bond,i,Left_bond+1,i+1);
		rectangle(Right_bond-1,i,Right_bond,i+1);
		if(i>=Down_bond) break;
	}
}
Wall wall;

class Snake
{
public:
	Node* head;
	Node* tail;
	int length;
	void Create(int);
	void Grow(Node);
	Node Anti_grow();
};

void Snake::Create(int NoSnake)
{
	Node* part1=new Node;								//ע�⣺ʵ���������ڿ��ơ�β����ǰ������
	Node* part2=new Node;
	part1->x=wall.Left_bond+Point_width;
	part1->y=wall.Up_bond+NoSnake*Interval_Snake;		//����֮�����2�����᷽��
	part1->next=NULL;
	tail=part1;
	part2->x=wall.Left_bond;
	part2->y=wall.Up_bond+NoSnake*Interval_Snake;
	part2->next=tail;
	head=part2;
	length=2;
	
	switch(NoSnake)										//������������Ҫ������ɫ����
	{
		case 0:setfillstyle(SOLID_FILL,GREEN);break;
		case 1:setfillstyle(SOLID_FILL,CYAN);break;
	}
	
	bar(head->x+1,head->y+1,head->x+Point_width-1,head->y+Point_width-1);
	bar(tail->x+1,tail->y+1,tail->x+Point_width-1,tail->y+Point_width-1);
}

void Snake::Grow (Node part_next)
{
	Node* part=new Node;
	part->x=part_next.x;
	part->y=part_next.y;
	part->next=part_next.next;
	tail->next=part;
	tail=part;
	length+=1;
}

Node Snake::Anti_grow()
{
	Node* part=head;
	Node Anti_part= *part;
	head=part->next;
	length-=1;
	delete part;
	return Anti_part;
}

Snake snake[Number_Snake];		//������

enum Direction					//����ö�ٱ���
{up,down,lef,righ};