//���� 10�� ���� ���� ���� �� ���� vector�� ����.������ �� 20�� ���� ���� ����, ��ź��ġ
//�� �������� �߰��ǵ��� ����,������ ����
//space.erase(space.begin() + num);�� ���� ���� �ִ�.
//0:�����,1:�ı��Ұ��ɺ�,2:�����,3:����,4:��ź,5:�ı����ɺ�
#pragma warning(disable:4996)
#include<iostream>
#include<string>
#include<time.h>
#include<conio.h>
#include<vector>
#include<list>
using namespace std;

void Output();

const int Map_Height = 19;
const int Map_Weight = 29;

class Monster;
class Bomb;

vector<Monster>		Monster_list;
vector<Bomb>		Bomb_list;

char state[20];
char Move_Dir;

int Look_Dir;
int idx[4] = { 1,-1,0,0 };
int idy[4] = { 0,0,1,-1 };
int Map[Map_Height][Map_Weight] = { 0 };
int Monster_Size = Monster_list.size();
int Bomb_Size = Bomb_list.size();

bool End_Flag = false;

class Object
{
public:
	int Pos_x;
	int Pos_y;
};
class Monster :public Object
{
public:
	bool Alive;

	void Monster_Init(time_t t)
	{
		Monster monster;
		int rand_x = (rand() + t) % 27;
		int rand_y = (rand() + t) % 17;
		if (rand_x == 1 && rand_y == 1)return;
		if (Map[rand_y][rand_x] == 0)
		{
			Monster_Size++;
			monster.Alive = 1;
			monster.Pos_x = rand_x;
			monster.Pos_y = rand_y;
			Monster_list.push_back(monster);
			Map[rand_y][rand_x] = 3;
		}
	}
	void Monster_Attack()
	{
		for (int i = 0; i < Monster_Size; i++)
		{
			if (!Monster_list[i].Alive)continue;
			for (int j = 0; j < 4; j++)
			{
				//���Ϳ� ����ڰ� ���ڸ� -> ����
				if (Map[Monster_list[i].Pos_y + idx[j]][Monster_list[i].Pos_x + idy[j]] == 2)
				{
					Output();
					printf("Game Over!");
					system("PAUSE");
					End_Flag = true;
					return;
				}
			}
		}
	}
	void Monster_Move(time_t t)
	{
		for (int i = 0; i < Monster_Size; i++) {
			if (Map[Monster_list[i].Pos_y][Monster_list[i].Pos_x] == 0)   Monster_list[i].Alive = 0;
			int rand_x = (rand() + t);
			int rand_y = (rand() + t);
			if ((rand_x % 2 == 1) && (rand_y % 2 == 1) && (Map[Monster_list[i].Pos_y][Monster_list[i].Pos_x - 1] == 0))
			{
				Map[Monster_list[i].Pos_y][Monster_list[i].Pos_x] = 0;
				Monster_list[i].Pos_x -= 1;
			}
			else if ((rand_x % 2 == 1) && (rand_y % 2 == 0) && (Map[Monster_list[i].Pos_y - 1][Monster_list[i].Pos_x] == 0))
			{
				Map[Monster_list[i].Pos_y][Monster_list[i].Pos_x] = 0;
				Monster_list[i].Pos_y -= 1;
			}
			else if ((rand_x % 2 == 0) && (rand_y % 2 == 1) && (Map[Monster_list[i].Pos_y + 1][Monster_list[i].Pos_x] == 0))
			{
				Map[Monster_list[i].Pos_y][Monster_list[i].Pos_x] = 0;
				Monster_list[i].Pos_y += 1;
			}
			else if ((rand_x % 2 == 0) && (rand_y % 2 == 0) && (Map[Monster_list[i].Pos_y][Monster_list[i].Pos_x + 1] == 0))
			{
				Map[Monster_list[i].Pos_y][Monster_list[i].Pos_x] = 0;
				Monster_list[i].Pos_x += 1;
			}
			Map[Monster_list[i].Pos_y][Monster_list[i].Pos_x] = 3;
		}
	}
};
class Bomb :public Object
{
public:
	int Frame_Cnt;

	void Bomb_Cnt()
	{
		for (int i = 0; i < Bomb_Size; i++)
		{
			if (Bomb_list[i].Frame_Cnt == -1)      continue;
			Bomb_list[i].Frame_Cnt++;
			//��ź ������ Bomb_list[i].Frame_Cnt = -1�� �ʱ�ȭ.
			if (Bomb_list[i].Frame_Cnt == 5)
			{
				Bomb_list[i].Frame_Cnt = -1;

				for (int j = 0; j < 4; j++)
				{
					int new_y = Bomb_list[i].Pos_y + idx[j];
					int new_x = Bomb_list[i].Pos_x + idy[j];
					if (Map[new_y][new_x] == 2)
					{
						Output();
						printf("Game Over!");
						system("PAUSE");
						End_Flag = true;
						return;
					}
					if (Map[new_y][new_x] == 3 || Map[new_y][new_x] == 5)	Map[new_y][new_x] = 0;
				}
				Map[Bomb_list[i].Pos_y][Bomb_list[i].Pos_x] = 0;
			}
		}
	}
};
class Player :public Object
{
public:
	int Cnt;

	Player Player_Move(Player player, char move_dir)
	{
		if ((Move_Dir == 'W') || (Move_Dir == 'w'))
		{
			if (Look_Dir == 1 && Map[player.Pos_y - 2][player.Pos_x - 1] == 0)
			{
				Map[player.Pos_y - 1][player.Pos_x - 1] = 0;
				player.Pos_y--;
			}
			else Look_Dir = 1;
		}
		else if ((Move_Dir == 'A') || (Move_Dir == 'a'))
		{
			if (Look_Dir == 2 && Map[player.Pos_y - 1][player.Pos_x - 2] == 0)
			{
				Map[player.Pos_y - 1][player.Pos_x - 1] = 0;
				player.Pos_x--;
			}
			else Look_Dir = 2;
		}
		else if ((Move_Dir == 'S') || (Move_Dir == 's'))
		{
			if (Look_Dir == 3 && Map[player.Pos_y][player.Pos_x - 1] == 0)
			{
				Map[player.Pos_y - 1][player.Pos_x - 1] = 0;
				player.Pos_y++;
			}
			else Look_Dir = 3;
		}
		else if ((Move_Dir == 'D') || (Move_Dir == 'd'))
		{
			if (Look_Dir == 4 && Map[player.Pos_y - 1][player.Pos_x] == 0)
			{
				Map[player.Pos_y - 1][player.Pos_x - 1] = 0;
				player.Pos_x++;
			}
			else Look_Dir = 4;
		}
		else if (Move_Dir == '1')
		{
			Bomb bomb;
			bomb.Frame_Cnt = -1;
			//�ٶ󺸴� ������ ����
			if (Look_Dir == 1 && Map[player.Pos_y - 2][player.Pos_x - 1] == 0)
				Map[player.Pos_y - 2][player.Pos_x - 1] = 4, bomb.Frame_Cnt = 0, bomb.Pos_x = player.Pos_x - 1, bomb.Pos_y = player.Pos_y - 2;
			else if (Look_Dir == 2 && Map[player.Pos_y - 1][player.Pos_x - 2] == 0)
				Map[player.Pos_y - 1][player.Pos_x - 2] = 4, bomb.Frame_Cnt = 0, bomb.Pos_x = player.Pos_x - 2, bomb.Pos_y = player.Pos_y - 1;
			else if (Look_Dir == 3 && Map[player.Pos_y][player.Pos_x - 1] == 0)
				Map[player.Pos_y][player.Pos_x - 1] = 4, bomb.Frame_Cnt = 0, bomb.Pos_x = player.Pos_x - 1, bomb.Pos_y = player.Pos_y;
			else if (Look_Dir == 4 && Map[player.Pos_y - 1][player.Pos_x] == 0)
				Map[player.Pos_y - 1][player.Pos_x] = 4, bomb.Frame_Cnt = 0, bomb.Pos_x = player.Pos_x, bomb.Pos_y = player.Pos_y - 1;
			//�ٶ󺸴� ���⿡ ��ź�� ������ ��ġ
			if (bomb.Frame_Cnt != -1)
			{
				Bomb_Size++;
				Bomb_list.push_back(bomb);
			}
		}
		//�����Ӹ� ����
		else if (Move_Dir == '2');
		else printf("�߸��� Ű �Է��Դϴ�.");
		//����� ��ġ �ʱ�ȭ
		Map[player.Pos_y - 1][player.Pos_x - 1] = 2;
		return player;
	}
};

Player				player;
Monster				monster;
Bomb				bomb;

void Map_Init()
{
	for (int i = 0; i < Map_Height; i++)
	{
		for (int j = 0; j < Map_Weight; j++)
		{
			//�� ����, �� �Ʒ����� ��� 1
			if (i == 0 || i == Map_Height - 1)
			{
				Map[i][j] = 1;
			}
			//�� ����, �� �������� ��� 1
			else if (j == 0 || j == Map_Weight - 1)
			{
				Map[i][j] = 1;
			}
			//������ ���
			else
			{
				if (i % 2 == 0 && j % 2 == 0)
				{
					Map[i][j] = 1;
				}
			}
		}
	}
}
void Breakable_Wall_Init(time_t t)
{
	for (int i = 0; i < 20; i++)
	{
		int rand_x = (rand() + t) % 27;
		int rand_y = (rand() + t) % 17;
		if (rand_x == 1 && rand_y == 1)continue;
		if (Map[rand_y][rand_x] == 0)
		{
			Map[rand_y][rand_x] = 5;
		}
	}
}
void State()
{
	printf("������ �����Ϸ��� 'Start'�� �Է� �� ���͸� ��������.\n");
	while (scanf("%s", &state))
	{
		system("cls");
		printf("������ �����Ϸ��� 'Start'�� �Է� �� ���͸� ��������.\n");
		if (!strcmp(state, "Start"))
		{
			printf("Start Game!\n");
			break;
		}
	}
	for (int i = 0; i < Map_Height; i++)
	{
		for (int j = 0; j < Map_Weight; j++)
		{
			if ((i == j) && (j == 1))  printf("��");
			else if (Map[i][j] == 1)   printf("��");
			else if (Map[i][j] == 3)   printf("��");
			else if (Map[i][j] == 4)   printf("��");
			else if (Map[i][j] == 5)   printf("��");
			else                  printf("��");
		}
		printf("\n");
	}
}
void Output()
{
	system("cls");
	//������ ī��Ʈ
	printf("player.Cnt : %d\n", player.Cnt);
	printf("Player Position : (%d,%d)\n", player.Pos_y - 1, player.Pos_x - 1);
	//���ʹ� ������ŭ ������ ī��Ʈ
	for (int i = 0; i < Map_Height; i++)
	{
		for (int j = 0; j < Map_Weight; j++)
		{
			//�ı� �Ұ����� ��
			if (Map[i][j] == 1)           printf("��");
			//����� ��ġ�� ����
			else if (Map[i][j] == 2)
			{
				if (Look_Dir == 1)        player.Cnt % 2 == 0 ? printf("��") : printf("��");
				else if (Look_Dir == 2)   player.Cnt % 2 == 0 ? printf("��") : printf("��");
				else if (Look_Dir == 3)   player.Cnt % 2 == 0 ? printf("��") : printf("��");
				else if (Look_Dir == 4)   player.Cnt % 2 == 0 ? printf("��") : printf("��");
			}
			else if (Map[i][j] == 3)      player.Cnt % 2 == 0 ? printf("��") : printf("��");
			else if (Map[i][j] == 4)      player.Cnt % 2 == 0 ? printf("��") : printf("��");
			else if (Map[i][j] == 5)      printf("��");
			else						  printf("��");
		}
		printf("\n");
	}
	printf("\n");
}

int main()
{
	time_t t;
	time(&t);

	player.Pos_x = 2;		player.Pos_y = 2;		player.Cnt = 0;
	
	Map_Init();
	for(int i = 0 ; i < 10;i++)	monster.Monster_Init(t);
	Breakable_Wall_Init(t);
	State();

	while (Move_Dir = _getch())
	{
		player.Cnt++;
		//20�ʸ��� ���� �߰�
		if (player.Cnt % 20 == 0)	monster.Monster_Init(t);
		//�����
		player = player.Player_Move(player, Move_Dir);
		//����
		monster.Monster_Move(t);
		monster.Monster_Attack();
		//��ź
		bomb.Bomb_Cnt();
		//���� Ȯ��
		if (End_Flag)return 0;
		//���
		Output();
	}
	return 0;
}