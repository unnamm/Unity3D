#pragma warning(disable:4996)
#include "Update.h"
#include "Player.h"
#include "Singleton.h"
#include <iostream>

void Update::State()
{
	char state[20];

	printf("������ �����Ϸ��� 'Start'�� �Է� �� ���͸� ��������.\n");
	while (scanf("%s", &state))
	{
		system("cls");
		if (!strcmp(state, "Start"))
		{
			printf("Start Game!\n");
			break;
		}
		else printf("������ �����Ϸ��� 'Start'�� �Է� �� ���͸� ��������.\n");
	}
	for (int i = 0; i < Map_Height; i++)
	{
		for (int j = 0; j < Map_Width; j++)
		{
			if ((i == j) && (j == 1))							 printf("��");
			else if (Singleton::getInstance()->Map[i][j] == 1)   printf("��");
			else if (Singleton::getInstance()->Map[i][j] == 3)   printf("��");
			else if (Singleton::getInstance()->Map[i][j] == 4)   printf("��");
			else if (Singleton::getInstance()->Map[i][j] == 5)   printf("��");
			else												 printf("��");
		}
		printf("\n");
	}
}

void Update::Output()
{
	system("cls");
	//������ ī��Ʈ
	printf("Player Frame : %d\t\tPlayer Position : (%d,%d)\n", Singleton::getInstance()->player->Frame_Cnt, Singleton::getInstance()->player->Pos_y - 1, Singleton::getInstance()->player->Pos_x - 1);
	printf("Monster : %d\t\t\tBomb : %d\n", Singleton::getInstance()->Monster_Size, Singleton::getInstance()->Bomb_Size);
	//���ʹ� ������ŭ ������ ī��Ʈ
	for (int i = 0; i < Map_Height; i++)
	{
		for (int j = 0; j < Map_Width; j++)
		{
			//�ı� �Ұ����� ��
			if (Singleton::getInstance()->Map[i][j] == 1)           printf("��");
			//����� ��ġ�� ����
			else if (Singleton::getInstance()->Map[i][j] == 2)
			{
				if (Singleton::getInstance()->Look_Dir == 1)        Singleton::getInstance()->player->Frame_Cnt % 2 == 0 ? printf("��") : printf("��");
				else if (Singleton::getInstance()->Look_Dir == 2)   Singleton::getInstance()->player->Frame_Cnt % 2 == 0 ? printf("��") : printf("��");
				else if (Singleton::getInstance()->Look_Dir == 3)   Singleton::getInstance()->player->Frame_Cnt % 2 == 0 ? printf("��") : printf("��");
				else if (Singleton::getInstance()->Look_Dir == 4)   Singleton::getInstance()->player->Frame_Cnt % 2 == 0 ? printf("��") : printf("��");
			}
			else if (Singleton::getInstance()->Map[i][j] == 3)      Singleton::getInstance()->player->Frame_Cnt % 2 == 0 ? printf("��") : printf("��");
			else if (Singleton::getInstance()->Map[i][j] == 4)      Singleton::getInstance()->player->Frame_Cnt % 2 == 0 ? printf("��") : printf("��");
			else if (Singleton::getInstance()->Map[i][j] == 5)      printf("��");
			else													printf("��");
		}
		printf("\n");
	}
	printf("\n");
}

Update::Update()
{
}

Update::~Update()
{
}
