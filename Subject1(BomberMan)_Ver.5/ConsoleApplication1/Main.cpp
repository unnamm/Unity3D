#pragma warning(disable:4996)
#include <iostream>
#include <time.h>
#include <conio.h>
#include <vector>
#include <list>
#include "Bomb.h"
#include "UnBreakable_Wall.h"
#include "Breakable_Wall.h"
#include "Monster.h"
#include "Update.h"
#include "Player.h"
#include "Singleton.h"
using namespace std;

int main()
{
	Monster *monster					= new Monster();
	Bomb *bomb							= new Bomb();
	UnBreakable_Wall *unbreakable_wall	= new UnBreakable_Wall();
	Breakable_Wall *breakable_wall		= new Breakable_Wall();
	Update *update						= new Update();
	
	Singleton::getInstance()->player->Pos_x = 2;			Singleton::getInstance()->player->Pos_y = 2;			Singleton::getInstance()->player->Frame_Cnt = 0;

	unbreakable_wall->UnBreakable_Wall_Init();

	for (int i = 0; i < 10; i++)
	{
		monster->Monster_Init();
	}

	breakable_wall->Breakable_Wall_Init();
	update->State();

	while (Singleton::getInstance()->Move_Dir = _getch())
	{
		Singleton::getInstance()->player->Frame_Cnt++;
		//20�ʸ��� ���� �߰�
		if (Singleton::getInstance()->player->Frame_Cnt % 20 == 0)	monster->Monster_Init();
		//�����
		Singleton::getInstance()->player->Player_Move(Singleton::getInstance()->player);
		//����
		monster->Monster_Move(&Singleton::getInstance()->Monster_list);
		monster->Monster_Attack(&Singleton::getInstance()->Monster_list);
		//��ź
		bomb->Bomb_Cnt();
		//���� Ȯ��
		if (Singleton::getInstance()->End_Flag)return 0;
		//���
		update->Output();
	}
	return 0;
}
