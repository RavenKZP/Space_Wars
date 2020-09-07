#include <stdio.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <queue>
#include <unistd.h>

#include "Algorithms.h"

std::ofstream ANTS_LOG;
std::ofstream BEES_LOG;
std::ofstream REPLAYER_LOG;
std::ifstream REPLAY_FILE;

int first_open_ants = 0;
int first_open_rep = 0;
int first_open_bees = 0;

void Ants_Algorithm (Input_type Input, Output_type &Output)
{
	time_t start_time = clock();
	if (first_open_ants == 0)
	{
		ANTS_LOG.open("logs/ANTS_LOG.log");
		first_open_ants = 1;
	}
	srand(time(NULL));

	Output_type Output_local;
	int Player = Input.PLAYER_IN;
	std::vector<std::vector<char> > MAP = Input.MAP_IN;
	std::string OUT;
	int My_Ships = Input.No_Ships_IN;

	char Enemy_1;
	char Enemy_2;
	char Enemy_3;
	char Enemy_4;
	char MyShip_1;
	char MyShip_2;
	char MyShip_3;
	char MyShip_4;
	
	if (Player == 1)
	{
		Enemy_1 =	'h';
		Enemy_2 =	'f';
		Enemy_3 =	't';
		Enemy_4 = 'w';
		MyShip_1 = 'H';
		MyShip_2 = 'F';
		MyShip_3 = 'T';
		MyShip_4 = 'W';
	}
	else
	{
		Enemy_1 =	'H';
		Enemy_2 =	'F';
		Enemy_3 =	'T';
		Enemy_4 = 'W';
		MyShip_1 = 'h';
		MyShip_2 = 'f';
		MyShip_3 = 't';
		MyShip_4 = 'w';
	}

	for (int i = My_Ships -1; i > -1; i--)
	{
		int ship_Type = Input.Type_IN[i];
		char type;
		if (ship_Type == 0)
			type = MyShip_1;
		if (ship_Type == 1)
			type = MyShip_2;
		if (ship_Type == 2)
			type = MyShip_3;

		int ship_x = Input.X_IN[i];
		int ship_y = Input.Y_IN[i];
		int ship_rotation = Input.Rotation_IN[i];
		int ship_storage = Input.Storage_IN[i];
		int MAX_Storage = 0;
		int Range = 1;

		for (int i = 0; i < MAP.size(); i++)
			for (int j = 0; j <MAP[i].size(); j++)
				if (MAP[j][i] == Enemy_1 || MAP[j][i] == Enemy_2 || MAP[j][i] == Enemy_3 || MAP[j][i] == Enemy_4)
					MAP[j][i] = 'E';

		int moves = 0;
		if (ship_Type == 0)
		{
			moves = 2;
			MAX_Storage = 10000;
			Range = 2;
		}
		if (ship_Type == 1)
		{
			moves = 3;
			MAX_Storage = 5;
			Range = 3;
		}
		if (ship_Type == 2)
		{
			moves = 2;
			MAX_Storage = 50;
			Range = 2;
		}

		while(moves != 0)
		{

		//BUILD WORKSHOP IF YOU CAN
		if (Input.Storage_IN[0] > 25)
		{
			if (ship_y > 0 && ship_y < MAP.size()-1 && ship_x > 0 && ship_x < MAP.size()-1 )
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x+1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x-1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y+1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y-1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_y == 0 && ship_x == 0)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x+1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y+1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_y == MAP.size()-1 && ship_x == MAP.size()-1)
			{
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x-1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y-1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_y == 0 && ship_x == MAP.size()-1)
			{
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x-1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y+1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_y == MAP.size()-1 && ship_x == 0)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x+1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y-1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_y < MAP.size()-1 && ship_y > 0 && ship_x == 0)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x+1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y+1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y-1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_y < MAP.size()-1 && ship_y > 0 && ship_x == MAP.size()-1)
			{
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x-1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y+1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y-1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_x < MAP.size()-1 && ship_x > 0 && ship_y == 0)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x+1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x-1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y+1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_x < MAP.size()-1 && ship_x > 0 && ship_y == MAP.size()-1)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x+1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x-1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y-1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
		}

		int move_performed = 0;

		//DIG IF THERE IS MINE
		if (move_performed == 0 && ship_storage < MAX_Storage && ship_Type == 0)
		switch (ship_rotation)
		{
			case 1:
				if(ship_x < MAP.size()-1)
					if(MAP[ship_y][ship_x+1] == 'M')
					{
						OUT = "DIG " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
						ship_storage+=5;
					}
				break;
			case 2:
				if(ship_x > 0)
					if(MAP[ship_y][ship_x-1] == 'M')
					{
						OUT = "DIG " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
						ship_storage+=5;
					}
				break;
			case 3:
				if(ship_y < MAP.size()-1)
					if(MAP[ship_y+1][ship_x] == 'M')
					{
						OUT = "DIG " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
						ship_storage+=5;
					}
				break;
			case 4:
				if(ship_y > 0)
					if(MAP[ship_y-1][ship_x] == 'M')
					{
						OUT = "DIG " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
						ship_storage+=5;
					}
				break;				
		}

		//SHOOT IF YOU SEE ENEMY
		switch (ship_rotation)
		{
			case 1:
				if(ship_x < MAP.size()-1)
				{
					if(MAP[ship_y][ship_x+1] == 'E')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_x+1 < MAP.size()-1 && Range > 1)
				{
					if(MAP[ship_y][ship_x+2] == 'E' && MAP[ship_y][ship_x+1] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_x+2 < MAP.size()-1 && Range > 2)
				{
					if(MAP[ship_y][ship_x+3] == 'E' && MAP[ship_y][ship_x+2] == '.' && MAP[ship_y][ship_x+1] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				break;
			case 2:
				if(ship_x > 0)
				{
					if(MAP[ship_y][ship_x-1] == 'E')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_x-1 > 0 && Range > 1)
				{
					if(MAP[ship_y][ship_x-2] == 'E' && MAP[ship_y][ship_x-1] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_x-2 > 0 && Range > 2)
				{
					if(MAP[ship_y][ship_x-3] == 'E' && MAP[ship_y][ship_x-2] == '.' && MAP[ship_y][ship_x-1] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				break;
			case 3:
				if(ship_y < MAP.size()-1)
				{
					if(MAP[ship_y+1][ship_x] == 'E')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_y+1 < MAP.size()-1 && Range > 1)
				{
					if(MAP[ship_y+2][ship_x] == 'E' && MAP[ship_y+1][ship_x] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_y+2 < MAP.size()-1 && Range > 2)
				{
					if(MAP[ship_y+3][ship_x] == 'E' && MAP[ship_y+2][ship_x] == '.' && MAP[ship_y+1][ship_x] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				break;
			case 4:
				if(ship_y > 0)
				{
					if(MAP[ship_y-1][ship_x] == 'E')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_y-1 > 0 && Range > 1)
				{
					if(MAP[ship_y-2][ship_x] == 'E' && MAP[ship_y-1][ship_x] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_y-2 > 0 && Range > 2)
				{
					if(MAP[ship_y-3][ship_x] == 'E' && MAP[ship_y-2][ship_x] == '.' && MAP[ship_y-1][ship_x] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				break;				
		}

		//MOVE IF YOU CAN
		if (move_performed == 0)
		switch (ship_rotation)
		{
			case 1:
				if(ship_x < MAP.size()-1)
					if(MAP[ship_y][ship_x+1] == '.')
					{
						OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						MAP[ship_y][ship_x] = '.';
						MAP[ship_y][ship_x+1] = type;
						ship_x++;
						moves--;
						move_performed = 1;
					}
				break;
			case 2:
				if(ship_x > 0)
					if(MAP[ship_y][ship_x-1] == '.')
					{
						OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						MAP[ship_y][ship_x] = '.';
						MAP[ship_y][ship_x-1] = type;
						ship_x--;
						moves--;
						move_performed = 1;
					}
				break;
			case 3:
				if(ship_y < MAP.size()-1)
					if(MAP[ship_y+1][ship_x] == '.')
					{
						OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						MAP[ship_y][ship_x] = '.';
						MAP[ship_y+1][ship_x] = type;
						ship_y++;
						moves--;
						move_performed = 1;
					}
				break;
			case 4:
				if(ship_y > 0)
					if(MAP[ship_y-1][ship_x] == '.')
					{
						OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						MAP[ship_y][ship_x] = '.';
						MAP[ship_y-1][ship_x] = type;
						ship_y--;
						moves--;
						move_performed = 1;
					}
				break;
		}


		//RANDOM ROTATE IF ON OTHER MOVES
		if (move_performed == 0)
		{
			if (rand()%2)
			{
				OUT = "ROTATE " +  std::to_string(Input.ID_IN[i]) + " R";
				if (ship_rotation == 2)
					ship_rotation = 4;
				else if (ship_rotation == 1)
					ship_rotation = 3;
				else if (ship_rotation == 3)
					ship_rotation = 2;
				else if (ship_rotation == 4)
					ship_rotation = 1;
			}
			else
			{
				OUT = "ROTATE " +  std::to_string(Input.ID_IN[i]) + " L";
				if (ship_rotation == 2)
					ship_rotation = 3;
				else if (ship_rotation == 1)
					ship_rotation = 4;
				else if (ship_rotation == 3)
					ship_rotation = 1;
				else if (ship_rotation == 4)
					ship_rotation = 2;
			}
			Output_local.Commands_OUT.push_back(OUT);
			moves--;
			move_performed = 1;
		}
		//OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
		//Output_local.Commands_OUT.push_back(OUT);
		}

	}
//Build Ships everywere!!!
		for (int i = 0; i < MAP.size(); i++)
		{
			for (int j = 0; j < MAP[i].size(); j++)
			{
				int Build_type;
					
				Build_type = 1;

				if (MAP[i][j] == MyShip_1 || MAP[i][j] == MyShip_4)
				{
					if (i > 0 && i < MAP.size()-1 && j > 0 && j < MAP.size()-1 )
					{
						if (MAP[i][j+1] == '.')
						{
							OUT = "BUILD " + std::to_string(j+1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i][j-1] == '.')
						{
							OUT = "BUILD " + std::to_string(j-1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i+1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i+1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i-1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i-1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (i == 0 && j == 0)
					{
						if (MAP[i][j+1] == '.')
						{
							OUT = "BUILD " + std::to_string(j+1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i+1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i+1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (i == MAP.size()-1 && j == MAP.size()-1)
					{
						if (MAP[i][j-1] == '.')
						{
							OUT = "BUILD " + std::to_string(j-1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i-1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i-1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (i == 0 && j == MAP.size()-1)
					{
						if (MAP[i][j-1] == '.')
						{
							OUT = "BUILD " + std::to_string(j-1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i+1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i+1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (i == MAP.size()-1 && j == 0)
					{
						if (MAP[i][j+1] == '.')
						{
							OUT = "BUILD " + std::to_string(j+1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i-1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i-1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (i < MAP.size()-1 && i > 0 && j == 0)
					{
						if (MAP[i][j+1] == '.')
						{
							OUT = "BUILD " + std::to_string(j+1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i+1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i+1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i-1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i-1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (i < MAP.size()-1 && i > 0 && j == MAP.size()-1)
					{
						if (MAP[i][j-1] == '.')
						{
							OUT = "BUILD " + std::to_string(j-1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i+1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i+1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i-1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i-1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (j < MAP.size()-1 && j > 0 && i == 0)
					{
						if (MAP[i][j+1] == '.')
						{
							OUT = "BUILD " + std::to_string(j+1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i][j-1] == '.')
						{
							OUT = "BUILD " + std::to_string(j-1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i+1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i+1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (j < MAP.size()-1 && j > 0 && i == MAP.size()-1)
					{
						if (MAP[i][j+1] == '.')
						{
							OUT = "BUILD " + std::to_string(j+1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i][j-1] == '.')
						{
							OUT = "BUILD " + std::to_string(j-1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i-1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i-1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
				}
				if (Input.Storage_IN[0] < 10)
					break;
			}
			if (Input.Storage_IN[0] < 10)
				break;
		}

	Output_local.Commands_OUT.push_back("END");

	Output = Output_local;
	time_t stop_time = clock();
	ANTS_LOG << difftime(stop_time, start_time) << "ms" << std::endl;
}


struct queueNode 
{ 
    int pt_x;
    int pt_y;
    int dist;
};

int rowNum[] = {-1, 0, 0, 1}; 
int colNum[] = {0, -1, 1, 0};

bool isValid(int row, int col, int max_row, int max_col) 
{        
    return (row >= 0) && (row < max_row) && (col >= 0) && (col < max_col); 
}

int BFS(std::vector<std::vector<char> > map, int x, int y, int target_x, int target_y) 
{
    int w = map[0].size();
    int h = map.size();
  
    int visited[h][w];

    for (int i = 0; i < h; i++) 
    {
        for (int j = 0; j < w; j++) 
        {
            visited[i][j] = 0;
        }
    }
      
    visited[y][x] = 1; 

    std::queue<queueNode> q; 
      
    queueNode s = {x, y, 0}; 
    q.push(s);
  
    while (!q.empty()) 
    { 
        queueNode curr = q.front(); 
        int pt_x = curr.pt_x;
        int pt_y = curr.pt_y;
  
        if (pt_x == target_x && pt_y == target_y)
        {
            return curr.dist; 
        }
        q.pop(); 
  
        for (int i = 0; i < 4; i++) 
        { 
            int row = (w+(pt_x + rowNum[i]))%w; 
            int col = (h+(pt_y + colNum[i]))%h;
              
            if (isValid(row, col, w, h) && (map[col][row] == '.' || map[col][row] == 'M') && !visited[col][row]) 
            { 
                visited[col][row] = 1; 
                queueNode Adjcell = {row, col, curr.dist + 1 }; 
                q.push(Adjcell); 
            } 
        } 
    }
    return -1; 
}

void Bees_Algorithm (Input_type Input, Output_type &Output)
{
	time_t start_time = clock();
	if (first_open_bees == 0)
	{
		BEES_LOG.open("logs/BEES_LOG.log");
		first_open_bees = 1;
	}
	srand(time(NULL));

	Output_type Output_local;
	int Player = Input.PLAYER_IN;
	std::vector<std::vector<char> > MAP = Input.MAP_IN;
	std::string OUT;

	int My_Ships = Input.No_Ships_IN;
	int My_Transport_Ships = 0;

	char Enemy_1;
	char Enemy_2;
	char Enemy_3;
	char Enemy_4;
	char MyShip_1;
	char MyShip_2;
	char MyShip_3;
	char MyShip_4;
	
	if (Player == 1)
	{
		Enemy_1 =	'h';
		Enemy_2 =	'f';
		Enemy_3 =	't';
		Enemy_4 = 'w';
		MyShip_1 = 'H';
		MyShip_2 = 'F';
		MyShip_3 = 'T';
		MyShip_4 = 'W';
	}
	else
	{
		Enemy_1 =	'H';
		Enemy_2 =	'F';
		Enemy_3 =	'T';
		Enemy_4 = 'W';
		MyShip_1 = 'h';
		MyShip_2 = 'f';
		MyShip_3 = 't';
		MyShip_4 = 'w';
	}

	for (int i = 0; i < My_Ships; i++)
	{
		int ship_Type = Input.Type_IN[i];

		if (ship_Type == 2)
		{
			My_Transport_Ships++;
		}		
		char type;
		if (ship_Type == 0)
			type = MyShip_1;
		if (ship_Type == 1)
			type = MyShip_2;
		if (ship_Type == 2)
			type = MyShip_3;

		int ship_x = Input.X_IN[i];
		int ship_y = Input.Y_IN[i];
		int ship_rotation = Input.Rotation_IN[i];
		int ship_storage = Input.Storage_IN[i];
		int MAX_Storage = 0;
		int Range = 1;

		for (int i = 0; i < MAP.size(); i++)
			for (int j = 0; j <MAP[i].size(); j++)
				if (MAP[j][i] == Enemy_1 || MAP[j][i] == Enemy_2 || MAP[j][i] == Enemy_3 || MAP[j][i] == Enemy_4)
					MAP[j][i] = 'E';

		int moves = 0;
		if (ship_Type == 0)
		{
			moves = 2;
			MAX_Storage = 10000;
			Range = 2;
		}
		if (ship_Type == 1)
		{
			moves = 3;
			MAX_Storage = 5;
			Range = 3;
		}
		if (ship_Type == 2)
		{
			moves = 2;
			MAX_Storage = 50;
			Range = 2;
		}

		while(moves != 0)
		{

		//BUILD WORKSHOP IF YOU CAN
		if (Input.Storage_IN[0] > 25)
		{
			if (ship_y > 0 && ship_y < MAP.size()-1 && ship_x > 0 && ship_x < MAP.size()-1 )
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x+1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x-1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y+1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y-1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_y == 0 && ship_x == 0)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x+1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y+1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_y == MAP.size()-1 && ship_x == MAP.size()-1)
			{
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x-1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y-1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_y == 0 && ship_x == MAP.size()-1)
			{
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x-1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y+1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_y == MAP.size()-1 && ship_x == 0)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x+1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y-1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_y < MAP.size()-1 && ship_y > 0 && ship_x == 0)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x+1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y+1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y-1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_y < MAP.size()-1 && ship_y > 0 && ship_x == MAP.size()-1)
			{
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x-1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y+1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y-1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_x < MAP.size()-1 && ship_x > 0 && ship_y == 0)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x+1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x-1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y+1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
			if (ship_x < MAP.size()-1 && ship_x > 0 && ship_y == MAP.size()-1)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x+1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y][ship_x-1] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
					MAP[ship_y-1][ship_x] == MyShip_4;
					Input.Storage_IN[0] -= 25;
				}
			}
		}

		int move_performed = 0;

		//DIG IF THERE IS MINE
		if (move_performed == 0 && ship_storage < MAX_Storage)
		switch (ship_rotation)
		{
			case 1:
				if(ship_x < MAP.size()-1)
					if(MAP[ship_y][ship_x+1] == 'M')
					{
						OUT = "DIG " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
						ship_storage+=5;
					}
				break;
			case 2:
				if(ship_x > 0)
					if(MAP[ship_y][ship_x-1] == 'M')
					{
						OUT = "DIG " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
						ship_storage+=5;
					}
				break;
			case 3:
				if(ship_y < MAP.size()-1)
					if(MAP[ship_y+1][ship_x] == 'M')
					{
						OUT = "DIG " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
						ship_storage+=5;
					}
				break;
			case 4:
				if(ship_y > 0)
					if(MAP[ship_y-1][ship_x] == 'M')
					{
						OUT = "DIG " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
						ship_storage+=5;
					}
				break;				
		}

		//SHOOT IF YOU SEE ENEMY
		switch (ship_rotation)
		{
			case 1:
				if(ship_x < MAP.size()-1)
				{
					if(MAP[ship_y][ship_x+1] == 'E')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_x+1 < MAP.size()-1 && Range > 1)
				{
					if(MAP[ship_y][ship_x+2] == 'E' && MAP[ship_y][ship_x+1] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_x+2 < MAP.size()-1 && Range > 2)
				{
					if(MAP[ship_y][ship_x+3] == 'E' && MAP[ship_y][ship_x+2] == '.' && MAP[ship_y][ship_x+1] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				break;
			case 2:
				if(ship_x > 0)
				{
					if(MAP[ship_y][ship_x-1] == 'E')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_x-1 > 0 && Range > 1)
				{
					if(MAP[ship_y][ship_x-2] == 'E' && MAP[ship_y][ship_x-1] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_x-2 > 0 && Range > 2)
				{
					if(MAP[ship_y][ship_x-3] == 'E' && MAP[ship_y][ship_x-2] == '.' && MAP[ship_y][ship_x-1] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				break;
			case 3:
				if(ship_y < MAP.size()-1)
				{
					if(MAP[ship_y+1][ship_x] == 'E')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_y+1 < MAP.size()-1 && Range > 1)
				{
					if(MAP[ship_y+2][ship_x] == 'E' && MAP[ship_y+1][ship_x] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_y+2 < MAP.size()-1 && Range > 2)
				{
					if(MAP[ship_y+3][ship_x] == 'E' && MAP[ship_y+2][ship_x] == '.' && MAP[ship_y+1][ship_x] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				break;
			case 4:
				if(ship_y > 0)
				{
					if(MAP[ship_y-1][ship_x] == 'E')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_y-1 > 0 && Range > 1)
				{
					if(MAP[ship_y-2][ship_x] == 'E' && MAP[ship_y-1][ship_x] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				if(ship_y-2 > 0 && Range > 2)
				{
					if(MAP[ship_y-3][ship_x] == 'E' && MAP[ship_y-2][ship_x] == '.' && MAP[ship_y-1][ship_x] == '.')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				}
				break;				
		}


		//Move to mine or HQ
		if ( (ship_Type == 0 || ship_Type == 2) && move_performed == 0)
		{
			int best_dist = 9999;
			int best_x = 9999; 
			int best_y = 9999; 
			for (int map_xx = 0; map_xx < MAP.size(); map_xx++)
			{
				for (int map_yy = 0; map_yy < MAP[0].size(); map_yy++)
				{
					if (MAP[map_yy][map_xx] == 'M' && ( (ship_storage < 50 && ship_Type == 2) || ship_Type == 0) )
					{
						int distance = BFS(MAP, ship_x, ship_y, map_xx, map_yy);

				std::cout << "BFS temp: " << map_xx << " " << map_yy << " " << distance << std::endl;
						if (distance != -1 && distance < best_dist)
						{
							best_dist = distance;
							best_x = map_xx;
							best_y = map_yy;
						}
					}
					if ( (ship_storage == 50 && ship_Type == 2) )
					{	
						best_x = Input.X_IN[0];
						best_y = Input.Y_IN[0];
						best_dist = -2;
					}
				}
			}
			if (best_dist != 9999)
			{
				switch (ship_rotation)
				{
					case 1:
						if(ship_x < best_x)
							if(MAP[ship_y][ship_x+1] == '.')
							{
								OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
								Output_local.Commands_OUT.push_back(OUT);
								MAP[ship_y][ship_x] = '.';
								MAP[ship_y][ship_x+1] = type;
								ship_x++;
								moves--;
								move_performed = 1;
							}
						break;
					case 2:
						if(ship_x > best_x)
							if(MAP[ship_y][ship_x-1] == '.')
							{
								OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
								Output_local.Commands_OUT.push_back(OUT);
								MAP[ship_y][ship_x] = '.';
								MAP[ship_y][ship_x-1] = type;
								ship_x--;
								moves--;
								move_performed = 1;
							}
						break;
					case 3:
						if(ship_y < best_y)
							if(MAP[ship_y+1][ship_x] == '.')
							{
								OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
								Output_local.Commands_OUT.push_back(OUT);
								MAP[ship_y][ship_x] = '.';
								MAP[ship_y+1][ship_x] = type;
								ship_y++;
								moves--;
								move_performed = 1;
							}
						break;
					case 4:
						if(ship_y > best_y)
							if(MAP[ship_y-1][ship_x] == '.')
							{
								OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
								Output_local.Commands_OUT.push_back(OUT);
								MAP[ship_y][ship_x] = '.';
								MAP[ship_y-1][ship_x] = type;
								ship_y--;
								moves--;
								move_performed = 1;
							}
						break;
				}
				if (move_performed == 0)
				{
					OUT = "ROTATE " +  std::to_string(Input.ID_IN[i]) + " R";
					if (ship_rotation == 2)
						ship_rotation = 4;
					else if (ship_rotation == 1)
						ship_rotation = 3;
					else if (ship_rotation == 3)
						ship_rotation = 2;
					else if (ship_rotation == 4)
						ship_rotation = 1;

					moves--;
					move_performed = 1;
					Output_local.Commands_OUT.push_back(OUT);
				}

				std::cout << "BFS: " << best_x << " " << best_y << " " << best_dist << std::endl;
				std::cout << "OUT: " << OUT << std::endl;
			}
		}

		//MOVE IF YOU CAN
		if (move_performed == 0)
		switch (ship_rotation)
		{
			case 1:
				if(ship_x < MAP.size()-1)
					if(MAP[ship_y][ship_x+1] == '.')
					{
						OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						MAP[ship_y][ship_x] = '.';
						MAP[ship_y][ship_x+1] = type;
						ship_x++;
						moves--;
						move_performed = 1;
					}
				break;
			case 2:
				if(ship_x > 0)
					if(MAP[ship_y][ship_x-1] == '.')
					{
						OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						MAP[ship_y][ship_x] = '.';
						MAP[ship_y][ship_x-1] = type;
						ship_x--;
						moves--;
						move_performed = 1;
					}
				break;
			case 3:
				if(ship_y < MAP.size()-1)
					if(MAP[ship_y+1][ship_x] == '.')
					{
						OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						MAP[ship_y][ship_x] = '.';
						MAP[ship_y+1][ship_x] = type;
						ship_y++;
						moves--;
						move_performed = 1;
					}
				break;
			case 4:
				if(ship_y > 0)
					if(MAP[ship_y-1][ship_x] == '.')
					{
						OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						MAP[ship_y][ship_x] = '.';
						MAP[ship_y-1][ship_x] = type;
						ship_y--;
						moves--;
						move_performed = 1;
					}
				break;
		}


		//RANDOM ROTATE IF ON OTHER MOVES
		if (move_performed == 0)
		{
			if (rand()%2)
			{
				OUT = "ROTATE " +  std::to_string(Input.ID_IN[i]) + " R";
				if (ship_rotation == 2)
					ship_rotation = 4;
				else if (ship_rotation == 1)
					ship_rotation = 3;
				else if (ship_rotation == 3)
					ship_rotation = 2;
				else if (ship_rotation == 4)
					ship_rotation = 1;
			}
			else
			{
				OUT = "ROTATE " +  std::to_string(Input.ID_IN[i]) + " L";
				if (ship_rotation == 2)
					ship_rotation = 3;
				else if (ship_rotation == 1)
					ship_rotation = 4;
				else if (ship_rotation == 3)
					ship_rotation = 1;
				else if (ship_rotation == 4)
					ship_rotation = 2;
			}
			Output_local.Commands_OUT.push_back(OUT);
			moves--;
			move_performed = 1;
		}
		//OUT = "MOVE " +  std::to_string(Input.ID_IN[i]);
		//Output_local.Commands_OUT.push_back(OUT);
		}

	}
		//Build Ships everywere!!!
		for (int i = 0; i < MAP.size(); i++)
		{
			for (int j = 0; j < MAP[i].size(); j++)
			{
				int Build_type;
				if (Input.Storage_IN[0] >= 20 && My_Transport_Ships < 3)
					Build_type = 2;
				else
					Build_type = 1;

				if (MAP[i][j] == MyShip_1 || MAP[i][j] == MyShip_4)
				{
					if (i > 0 && i < MAP.size()-1 && j > 0 && j < MAP.size()-1 )
					{
						if (MAP[i][j+1] == '.')
						{
							OUT = "BUILD " + std::to_string(j+1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i][j-1] == '.')
						{
							OUT = "BUILD " + std::to_string(j-1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i+1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i+1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i-1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i-1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (i == 0 && j == 0)
					{
						if (MAP[i][j+1] == '.')
						{
							OUT = "BUILD " + std::to_string(j+1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i+1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i+1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (i == MAP.size()-1 && j == MAP.size()-1)
					{
						if (MAP[i][j-1] == '.')
						{
							OUT = "BUILD " + std::to_string(j-1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i-1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i-1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (i == 0 && j == MAP.size()-1)
					{
						if (MAP[i][j-1] == '.')
						{
							OUT = "BUILD " + std::to_string(j-1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i+1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i+1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (i == MAP.size()-1 && j == 0)
					{
						if (MAP[i][j+1] == '.')
						{
							OUT = "BUILD " + std::to_string(j+1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i-1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i-1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (i < MAP.size()-1 && i > 0 && j == 0)
					{
						if (MAP[i][j+1] == '.')
						{
							OUT = "BUILD " + std::to_string(j+1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i+1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i+1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i-1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i-1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (i < MAP.size()-1 && i > 0 && j == MAP.size()-1)
					{
						if (MAP[i][j-1] == '.')
						{
							OUT = "BUILD " + std::to_string(j-1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i+1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i+1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i-1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i-1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (j < MAP.size()-1 && j > 0 && i == 0)
					{
						if (MAP[i][j+1] == '.')
						{
							OUT = "BUILD " + std::to_string(j+1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i][j-1] == '.')
						{
							OUT = "BUILD " + std::to_string(j-1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i+1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i+1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
					if (j < MAP.size()-1 && j > 0 && i == MAP.size()-1)
					{
						if (MAP[i][j+1] == '.')
						{
							OUT = "BUILD " + std::to_string(j+1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i][j-1] == '.')
						{
							OUT = "BUILD " + std::to_string(j-1) + " " + std::to_string(i) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
						if (MAP[i-1][j] == '.')
						{
							OUT = "BUILD " + std::to_string(j) + " " + std::to_string(i-1) + " " + std::to_string(Build_type) + " "  + std::to_string(rand()%4+1);
							Output_local.Commands_OUT.push_back(OUT);
							Input.Storage_IN[0] -= 10;
						}
					}
				}
				if (Input.Storage_IN[0] < 10)
					break;
			}
			if (Input.Storage_IN[0] < 10)
				break;
		}

	Output_local.Commands_OUT.push_back("END");

	Output = Output_local;
	time_t stop_time = clock();
	BEES_LOG << difftime(stop_time, start_time) << "ms" << std::endl;
}

void Replayer_Algorithm (Input_type Input, Output_type &Output)
{
	time_t start_time = clock();
	if (first_open_rep == 0)
	{
		REPLAY_FILE.open("Replays/ACTIONS_LOG.log");
		REPLAYER_LOG.open("logs/REPLAYER_LOG.log");
		first_open_rep = 1;
	}
	Output_type Output_local;
	std::string OUT;
	int Turn = 1;
	getline(REPLAY_FILE, OUT); // ignore first (seed) line
	while (Turn != 0 && !REPLAY_FILE.eof() )
	{
		getline(REPLAY_FILE, OUT);
		if (!OUT.empty())
			Output_local.Commands_OUT.push_back(OUT);
		if (OUT == "END")
			Turn = 0;
	}
	Output = Output_local;
	if (REPLAY_FILE.eof())
		REPLAY_FILE.close();

	time_t stop_time = clock();
	REPLAYER_LOG << difftime(stop_time, start_time) << "ms" << std::endl;
}


