//몬스터 10개 이하 랜덤 생성 및 정보 vector에 저장.깨지는 벽 20개 이하 랜덤 생성, 폭탄설치
//빈 공간에만 추가되도록 설정,변수명 정리
//space.erase(space.begin() + num);로 벡터 당길수 있다.
//0:빈공간,1:파괴불가능벽,2:사용자,3:몬스터,4:폭탄,5:파괴가능벽\
//ㅎㅇ
#pragma warning(disable:4996)
#include<iostream>
#include<string>
#include<time.h>
#include<conio.h>
#include<vector>
#include<list>
#define Map_Height 19
#define Map_Weight 29

using namespace std;

class Object
{
public:
	int Pos_x;
	int Pos_y;
};
class Player :public Object
{
public:
	int Cnt;
};
class Monster :public Object
{
public:
	bool Alive;
};
class Bomb :public Object
{
public:
	int Frame_Cnt;
};

vector<Monster>		Monster_list;
vector<Bomb>		Bomb_list;
Player				player;

char state[20];
char KeyBoard_Input;
int Look_Dir;
int idx[4] = { 1,-1,0,0 };
int idy[4] = { 0,0,1,-1 };
int Map[Map_Height][Map_Weight] = { 0 };
int Monster_Size = Monster_list.size();
int Bomb_Size = Bomb_list.size();

void Map_Init()
{
	for (int i = 0; i < Map_Height; i++)
	{
		for (int j = 0; j < Map_Weight; j++)
		{
			//맨 윗줄, 맨 아랫줄의 경우 1
			if (i == 0 || i == Map_Height - 1)
			{
				Map[i][j] = 1;
			}
			//맨 왼쪽, 맨 오른쪽의 경우 1
			else if (j == 0 || j == Map_Weight - 1)
			{
				Map[i][j] = 1;
			}
			//나머지 경우
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
	printf("게임을 시작하려면 'Start'를 입력 후 엔터를 누르세요.\n");
	while (scanf("%s", &state))
	{
		system("cls");
		printf("게임을 시작하려면 'Start'를 입력 후 엔터를 누르세요.\n");
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
			if ((i == j) && (j == 1))  printf("▽");
			else if (Map[i][j] == 1)   printf("■");
			else if (Map[i][j] == 3)   printf("○");
			else if (Map[i][j] == 4)   printf("◇");
			else if (Map[i][j] == 5)   printf("□");
			else                  printf("　");
		}
		printf("\n");
	}
}
void Output()
{
	system("cls");
	//프레임 카운트
	printf("player.Cnt : %d\n", player.Cnt);
	printf("Player Position : (%d,%d)\n", player.Pos_y - 1, player.Pos_x - 1);
	//몬스터는 갯수만큼 프레임 카운트
	for (int i = 0; i < Map_Height; i++)
	{
		for (int j = 0; j < Map_Weight; j++)
		{
			//파괴 불가능한 벽
			if (Map[i][j] == 1)           printf("■");
			//사용자 위치를 찍음
			else if (Map[i][j] == 2)
			{
				if (Look_Dir == 1)        player.Cnt % 2 == 0 ? printf("△") : printf("▲");
				else if (Look_Dir == 2)   player.Cnt % 2 == 0 ? printf("◁") : printf("◀");
				else if (Look_Dir == 3)   player.Cnt % 2 == 0 ? printf("▽") : printf("▼");
				else if (Look_Dir == 4)   player.Cnt % 2 == 0 ? printf("▷") : printf("▶");
			}
			else if (Map[i][j] == 3)      player.Cnt % 2 == 0 ? printf("○") : printf("●");
			else if (Map[i][j] == 4)      player.Cnt % 2 == 0 ? printf("◇") : printf("◆");
			else if (Map[i][j] == 5)      printf("□");
			else						  printf("　");
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
	for (int i = 0; i < 10; i++)	Monster_Init(t);
	Breakable_Wall_Init(t);
	State();

	while (KeyBoard_Input = _getch())
	{
		player.Cnt++;
		//20초마다 몬스터 추가
		if (player.Cnt % 20 == 0)	Monster_Init(t);
#pragma region 사용자 입력
		if ((KeyBoard_Input == 'W') || (KeyBoard_Input == 'w'))
		{
			if (Look_Dir == 1 && Map[player.Pos_y - 2][player.Pos_x - 1] == 0)
			{
				Map[player.Pos_y - 1][player.Pos_x - 1] = 0;
				player.Pos_y--;
			}
			else Look_Dir = 1;
		}
		else if ((KeyBoard_Input == 'A') || (KeyBoard_Input == 'a'))
		{
			if (Look_Dir == 2 && Map[player.Pos_y - 1][player.Pos_x - 2] == 0)
			{
				Map[player.Pos_y - 1][player.Pos_x - 1] = 0;
				player.Pos_x--;
			}
			else Look_Dir = 2;
		}
		else if ((KeyBoard_Input == 'S') || (KeyBoard_Input == 's'))
		{
			if (Look_Dir == 3 && Map[player.Pos_y][player.Pos_x - 1] == 0)
			{
				Map[player.Pos_y - 1][player.Pos_x - 1] = 0;
				player.Pos_y++;
			}
			else Look_Dir = 3;
		}
		else if ((KeyBoard_Input == 'D') || (KeyBoard_Input == 'd'))
		{
			if (Look_Dir == 4 && Map[player.Pos_y - 1][player.Pos_x] == 0)
			{
				Map[player.Pos_y - 1][player.Pos_x - 1] = 0;
				player.Pos_x++;
			}
			else Look_Dir = 4;
		}
		else if (KeyBoard_Input == '1')
		{
			Bomb bomb;
			bomb.Frame_Cnt = -1;
			//바라보는 방향의 정보
			if (Look_Dir == 1 && Map[player.Pos_y - 2][player.Pos_x - 1] == 0)
				Map[player.Pos_y - 2][player.Pos_x - 1] = 4, bomb.Frame_Cnt = 0, bomb.Pos_x = player.Pos_x - 1, bomb.Pos_y = player.Pos_y - 2;
			else if (Look_Dir == 2 && Map[player.Pos_y - 1][player.Pos_x - 2] == 0)
				Map[player.Pos_y - 1][player.Pos_x - 2] = 4, bomb.Frame_Cnt = 0, bomb.Pos_x = player.Pos_x - 2, bomb.Pos_y = player.Pos_y - 1;
			else if (Look_Dir == 3 && Map[player.Pos_y][player.Pos_x - 1] == 0)
				Map[player.Pos_y][player.Pos_x - 1] = 4, bomb.Frame_Cnt = 0, bomb.Pos_x = player.Pos_x - 1, bomb.Pos_y = player.Pos_y;
			else if (Look_Dir == 4 && Map[player.Pos_y - 1][player.Pos_x] == 0)
				Map[player.Pos_y - 1][player.Pos_x] = 4, bomb.Frame_Cnt = 0, bomb.Pos_x = player.Pos_x, bomb.Pos_y = player.Pos_y - 1;
			//바라보는 방향에 폭탄이 없으면 설치
			if (bomb.Frame_Cnt != -1)
			{
				Bomb_Size++;
				Bomb_list.push_back(bomb);
			}
		}
		//프레임만 증가
		else if (KeyBoard_Input == '2');
		else printf("잘못된 키 입력입니다.");

		//사용자 위치 초기화
		Map[player.Pos_y - 1][player.Pos_x - 1] = 2;
#pragma endregion
#pragma region 몬스터
		for (int i = 0; i < Monster_Size; i++)
		{
			if (!Monster_list[i].Alive)continue;
			for (int j = 0; j < 4; j++)
			{
				//몬스터와 사용자가 옆자리 -> 종료
				if (Map[Monster_list[i].Pos_y + idx[j]][Monster_list[i].Pos_x + idy[j]] == 2)
				{
					Output();
					printf("Game Over!");
					system("PAUSE");
					return 0;
				}
			}
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
#pragma endregion
#pragma region 폭탄
		for (int i = 0; i < Bomb_Size; i++)
		{
			if (Bomb_list[i].Frame_Cnt == -1)      continue;
			Bomb_list[i].Frame_Cnt++;
			//폭탄 터지면 Bomb_list[i].Frame_Cnt = -1로 초기화.
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
						return 0;
					}
					if (Map[new_y][new_x] == 3 || Map[new_y][new_x] == 5)	Map[new_y][new_x] = 0;
				}
				Map[Bomb_list[i].Pos_y][Bomb_list[i].Pos_x] = 0;
			}
		}
#pragma endregion
		Output();
	}
	return 0;
}
