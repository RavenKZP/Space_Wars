#include <stdio.h>
#include <iostream>
#include <unistd.h>

#include "Algorithms.h"

//#define MANUAL_TESTING

void Test_Alg_1 (Input_type Input, Output_type &Output)
{
	srand(time(NULL));

	Output_type Output_local;
#ifndef MANUAL_TESTING
	int Player = Input.PLAYER_IN;
	std::vector<std::vector<char> > MAP = Input.MAP_IN;
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
		MyShip_1 = 'T';
		MyShip_2 = 'W';
	}
	else
	{
		Enemy_1 =	'H';
		Enemy_2 =	'F';
		Enemy_3 =	'T';
		Enemy_4 = 'W';
		MyShip_1 = 'h';
		MyShip_2 = 'f';
		MyShip_1 = 't';
		MyShip_2 = 'w';
	}

	for (int i = 0; i < My_Ships; i++)
	{
		std::string OUT;
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

		for (int i = 0; i < MAP.size(); i++)
			for (int j = 0; j <MAP[i].size(); j++)
				if (MAP[j][i] == Enemy_1 || MAP[j][i] == Enemy_2 || MAP[j][i] == Enemy_3 || MAP[j][i] == Enemy_4)
					MAP[j][i] = 'E';

		int moves = 0;
		if (ship_Type == 0)
			moves = 2;
		if (ship_Type == 1)
			moves = 3;
		if (ship_Type == 2)
			moves = 2;

		//Build Fighters everywere!!!
		for (int i = 0; i < MAP.size(); i++)
		{
			for (int j = 0; j <MAP[i].size(); j++)
			{
				if (MAP[j][i] == MyShip_1 || MAP[j][i] == MyShip_4)
				{
					
				}
			}
		}

		while(moves != 0)
		{

		//BUILD WORKSHOP IF CAN
		if (Input.Storage_IN[0] > 25)
		{
			if (ship_y > 0 && ship_y < MAP.size()-1 && ship_x > 0 && ship_x < MAP.size()-1 )
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
				}
			}
			if (ship_y == 0 && ship_x == 0)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
				}
			}
			if (ship_y == MAP.size()-1 && ship_x == MAP.size()-1)
			{
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
				}
			}
			if (ship_y == 0 && ship_x == MAP.size()-1)
			{
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
				}
			}
			if (ship_y == MAP.size()-1 && ship_x == 0)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
				}
			}
			if (ship_y < MAP.size()-1 && ship_y > 0 && ship_x == 0)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
				}
			}
			if (ship_y < MAP.size()-1 && ship_y > 0 && ship_x == MAP.size()-1)
			{
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
				}
			}
			if (ship_x < MAP.size()-1 && ship_x > 0 && ship_y == 0)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y+1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y+1);
					Output_local.Commands_OUT.push_back(OUT);
				}
			}
			if (ship_x < MAP.size()-1 && ship_x > 0 && ship_y == MAP.size()-1)
			{
				if (MAP[ship_y][ship_x+1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x+1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y][ship_x-1] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x-1) + " " + std::to_string(ship_y);
					Output_local.Commands_OUT.push_back(OUT);
				}
				if (MAP[ship_y-1][ship_x] == 'A')
				{
					OUT = "WORKSHOP " + std::to_string(ship_x) + " " + std::to_string(ship_y-1);
					Output_local.Commands_OUT.push_back(OUT);
				}
			}
		}

		int move_performed = 0;

		//SHOOT IF ENEMY
		switch (ship_rotation)
		{
			case 1:
				if(ship_x < MAP.size()-1)
					if(MAP[ship_y][ship_x+1] == 'E')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				break;
			case 2:
				if(ship_x > 0)
					if(MAP[ship_y][ship_x-1] == 'E')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				break;
			case 3:
				if(ship_y < MAP.size()-1)
					if(MAP[ship_y+1][ship_x] == 'E')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				break;
			case 4:
				if(ship_y > 0)
					if(MAP[ship_y-1][ship_x] == 'E')
					{
						OUT = "SHOOT " +  std::to_string(Input.ID_IN[i]);
						Output_local.Commands_OUT.push_back(OUT);
						moves--;
						move_performed = 1;
					}
				break;				
		}

		//ONLY HQ DIG IF MINE
		if (move_performed == 0 && ship_Type == 0)
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
					}
				break;				
		}

		//MOVE IF EMPTY
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

	Output_local.Commands_OUT.push_back("END");

#else
	char command[100];
	std::cout << "Enter commands" << std::endl;
	std::string end;
	while (end != "END")
	{
		std::cin.getline(command, sizeof(command));
		Output_local.Commands_OUT.push_back(command);
		end = command;
	}
#endif

	Output = Output_local;
}


void Test_Alg_2 (Input_type Input, Output_type &Output)
{
	usleep(200);
}


