#include <iostream>
#include <windows.h>
#include <iomanip>
#include "class.h"
using namespace std;
void Open_title()
{
	cout<<endl<<endl<<endl<<endl<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);	//调整输出字符颜色
	cout<<"         　　　　　　　吃蛇吃　　　　　　　　　　　　　　一蛇　　　　　　　　　蛇一　　　　　一吃　　　　　"<<endl;
	cout<<"         　　　　　一蛇吃　吃蛇一　　　　　　　　　　　　蛇一　　　　　　　　　蛇一　　　　　　蛇一　　　　"<<endl;
	cout<<"         　　一蛇蛇一　蛇　　　吃蛇一　　一蛇蛇蛇蛇一　一蛇一　　　　　　　　　蛇一　　一蛇蛇蛇蛇蛇蛇蛇吃　"<<endl;
	cout<<"         一蛇蛇　　　　一蛇　　　　一蛇吃一蛇　　吃一　蛇蛇蛇蛇蛇蛇蛇蛇一一蛇蛇蛇蛇蛇一一一　　　　　一吃　"<<endl;
	cout<<"         　　　吃蛇蛇蛇蛇蛇蛇蛇蛇一　　　一蛇　　吃一吃蛇　　　　　　　　一蛇　蛇一一一一一　　　　　一吃　"<<endl;
	cout<<"         　　　　　　　　　　蛇一　　　　一蛇　　吃蛇蛇　　　　　　　　　一蛇　蛇一一一　　　　　　　　　　"<<endl;
	cout<<"         　　一蛇蛇蛇蛇蛇蛇蛇蛇蛇蛇吃　　一蛇　　吃一　吃蛇蛇蛇蛇蛇蛇　　一蛇　蛇一一一　吃一　　　一吃　　"<<endl;
	cout<<"         　　一吃　　　　　　　　一吃　　一蛇　　吃一　　　　　一蛇　　　一蛇　蛇一一一　吃一　　一蛇一　　"<<endl;
	cout<<"         　　一吃　　　一吃　　　一吃　　一蛇　　吃一　　　　吃蛇　　　　一蛇蛇蛇蛇蛇一　吃一一蛇吃　　　　"<<endl;
	cout<<"         　　一吃　　　一吃　　　一吃　　一蛇　　吃一　　　蛇吃　　　一吃一蛇　蛇一　　　吃蛇蛇　　　一吃　"<<endl;
	cout<<"         　　一吃　　　一蛇　　　一吃　　一蛇蛇蛇蛇一　　蛇一　　　　一吃　　　蛇一吃一　吃一　　　　一一　"<<endl;
	cout<<"         　　　　　　一蛇蛇蛇蛇一　　　　一蛇　　吃一　吃一　　　　　一一　　　蛇一一吃　吃一　　　　吃一　"<<endl;
	cout<<"　         　　　吃蛇蛇一　　一蛇蛇蛇　　　　　　　　一蛇　　　　　　蛇一　　一蛇蛇蛇蛇　吃一　　　一蛇一　"<<endl;
	cout<<"         一蛇蛇蛇一　　　　　　　　一蛇　　　　　　　　蛇蛇蛇蛇蛇蛇蛇吃　一蛇蛇　　　蛇一一蛇蛇蛇蛇蛇一　　"<<endl;
	cout<<endl<<endl<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout<<setw(68)<<"键盘方向键与WASD键控制方向"<<endl<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	cout<<setw(63)<<"Designed by Jack"<<endl<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout<<setw(80)<<"同时按住右方向键进行游戏，同时按住左方向键退出游戏"<<endl<<endl;
}
void Over_title()
{
	cout<<endl<<endl<<endl<<endl<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout<<"          　　　　　　　吃蛇吃　　　　　　　　　　　　　　一蛇　　　　　　　　　蛇一　　　　　一吃　　　　　"<<endl;
	cout<<"          　　　　　一蛇吃　吃蛇一　　　　　　　　　　　　蛇一　　　　　　　　　蛇一　　　　　　蛇一　　　　"<<endl;
	cout<<"　          　一蛇蛇一　蛇　　　吃蛇一　　一蛇蛇蛇蛇一　一蛇一　　　　　　　　　蛇一　　一蛇蛇蛇蛇蛇蛇蛇吃　"<<endl;
	cout<<"          一蛇蛇　　　　一蛇　　　　一蛇吃一蛇　　吃一　蛇蛇蛇蛇蛇蛇蛇蛇一一蛇蛇蛇蛇蛇一一一　　　　　一吃　"<<endl;
	cout<<"　　          　吃蛇蛇蛇蛇蛇蛇蛇蛇一　　　一蛇　　吃一吃蛇　　　　　　　　一蛇　蛇一一一一一　　　　　一吃　"<<endl;
	cout<<"　　　　  　        　　　　　蛇一　　　　一蛇　　吃蛇蛇　　　　　　　　　一蛇　蛇一一一　　　　　　　　　　"<<endl;
	cout<<"          　　一蛇蛇蛇蛇蛇蛇蛇蛇蛇蛇吃　　一蛇　　吃一　吃蛇蛇蛇蛇蛇蛇　　一蛇　蛇一一一　吃一　　　一吃　　"<<endl;
	cout<<"　　          一吃　　　　　　　　一吃　　一蛇　　吃一　　　　　一蛇　　　一蛇　蛇一一一　吃一　　一蛇一　　"<<endl;
	cout<<"　　          一吃　　　一吃　　　一吃　　一蛇　　吃一　　　　吃蛇　　　　一蛇蛇蛇蛇蛇一　吃一一蛇吃　　　　"<<endl;
	cout<<"　　          一吃　　　一吃　　　一吃　　一蛇　　吃一　　　蛇吃　　　一吃一蛇　蛇一　　　吃蛇蛇　　　一吃　"<<endl;
	cout<<"　　          一吃　　　一蛇　　　一吃　　一蛇蛇蛇蛇一　　蛇一　　　　一吃　　　蛇一吃一　吃一　　　　一一　"<<endl;
	cout<<"　　　　　          　一蛇蛇蛇蛇一　　　　一蛇　　吃一　吃一　　　　　一一　　　蛇一一吃　吃一　　　　吃一　"<<endl;
	cout<<"　　　　          吃蛇蛇一　　一蛇蛇蛇　　　　　　　　一蛇　　　　　　蛇一　　一蛇蛇蛇蛇　吃一　　　一蛇一　"<<endl;
	cout<<"          一蛇蛇蛇一　　　　　　　　一蛇　　　　　　　　蛇蛇蛇蛇蛇蛇蛇吃　一蛇蛇　　　蛇一一蛇蛇蛇蛇蛇一　　"<<endl;
	cout<<endl<<endl<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout<<setw(60)<<"GAME OVER"<<endl<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout<<setw(80)<<"同时按住右方向键进行游戏，同时按住左方向键退出游戏"<<endl<<endl;
}