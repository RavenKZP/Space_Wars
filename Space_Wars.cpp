#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <errno.h>
#include <string>
#include <cctype>
#include <boost/algorithm/string.hpp>

int MAP_SIZE = 10;

#include "Return_Types.h"
#include "Space_Classes.h"
#include "Algorithms/Algorithms.h"
#include "Space_Functions.h"

int main()
{
	int seed = time(NULL);
	//std::cout << "seed " << seed << std::endl;
	srand(seed);
	//MAP
	std::vector<std::vector<char> > MAP;
	//generating map
	
	int Number_of_Asteroids = MAP_SIZE/10 * (MAP_SIZE - rand()%(MAP_SIZE/2)); 			//for MAP_SIZE = 10 is from 5 to 10
	int Number_of_Mines = MAP_SIZE/10 * (MAP_SIZE - rand()%(MAP_SIZE/2)); 					//for MAP_SIZE = 10 is from 5 to 10
	//std::cout << "Number_of_Asteroids " << Number_of_Asteroids << std::endl << "Number_of_Mines " << Number_of_Mines << std::endl;

	std::vector<int> A_coords;
	std::vector<int>::iterator it_A;
	std::vector<int> M_coords;
	std::vector<int>::iterator it_M;

	//generating random coordinates for Asteroids

	for (int i = 0; i < Number_of_Asteroids; i++)
	{
		int coords = rand()%( ((MAP_SIZE*MAP_SIZE)/2));
		it_A = find(A_coords.begin(), A_coords.end(), coords);
		if (it_A != A_coords.end() || coords == 0 || coords == 1 || coords == MAP_SIZE || coords == MAP_SIZE + 1)
		{
			i--;
		}
		else
		{
			//std::cout << "A_coords " << coords << std::endl;
			A_coords.push_back(coords);
		}
	}

	//generating random coordinates for Minse

	for (int i = 0; i < Number_of_Mines; i++)
	{
		int coords = rand()%( ((MAP_SIZE*MAP_SIZE)/2));
		it_A = find(A_coords.begin(), A_coords.end(), coords);
		it_M = find(M_coords.begin(), M_coords.end(), coords);
		if (it_M != M_coords.end() || it_A != A_coords.end() || coords == 0 || coords == 1 || coords == MAP_SIZE || coords == MAP_SIZE + 1)
		{
			i--;
		}
		else
		{
			//std::cout << "M_coords " << coords << std::endl;
			M_coords.push_back(coords);
		}
	}

  //Filling the map by empty space (.)

	for (int y = 0; y < MAP_SIZE; y++)
	{
		std::vector<char> temp;
		for (int x = 0; x < MAP_SIZE; x++)
		{
			temp.push_back('.');
		}
	MAP.push_back(temp);
	} 

	//placing Head Quaters for both players
	std::vector<Ship_Class> Ships_Player_1;
	std::vector<Ship_Class> Ships_Player_2;

	Ship_Class HQ_Player_1 = Ship_Class(0, 1, 0, 0, 3);
	Ship_Class HQ_Player_2 = Ship_Class(0, 2, MAP_SIZE-1, MAP_SIZE-1, 4);

	Ships_Player_1.push_back(HQ_Player_1);
	Ships_Player_2.push_back(HQ_Player_2);

	
	int game_end = MAP_SIZE*MAP_SIZE*5;
	while(game_end > 0)
	{
		//reset spped for ships
		for (int i = 0; i < Ships_Player_1.size(); i++)
		{
			Ships_Player_1[i].reset_speed();
		}
		for (int i = 0; i < Ships_Player_2.size(); i++)
		{
			Ships_Player_2[i].reset_speed();
		}

		//placing Asteroids on map

		for (int i = 0; i < A_coords.size(); i++)
		{
			int max_size = MAP_SIZE ;
			int x = A_coords[i];
			int y = 0;
			while(1)
			{
				if (x >= max_size)
				{
					y++;
					x -= max_size;
					max_size--;
				}
				else
				{
					MAP[y][x] = 'A';
					//std::cout << "y " << y << " x " << x <<std::endl;
					MAP[MAP_SIZE - y - 1][MAP_SIZE - x - 1] = 'A';
					break;
				}
			}
		}
	
		//placing Mines on map
	
		for (int i = 0; i < M_coords.size(); i++)
		{
			int max_size = MAP_SIZE;
			int x = M_coords[i];
			int y = 0;
			while(1)
			{
				if (x >= max_size)
				{
					y++;
					x -= max_size;
					//std::cout << x << std::endl; 
					max_size--;
				}
				else
				{
					MAP[y][x] = 'M';
					//std::cout << "y " << y << "x " << x <<std::endl;
					MAP[MAP_SIZE - y - 1][MAP_SIZE - x - 1] = 'M';
					break;
				}
			}
		}
	
		//Placing Ships on map
	
		for (int i = 0; i <	Ships_Player_1.size(); i++)
		{
			char res;
			switch (Ships_Player_1[i].Type)
			{
				case 0:
					res = 'H';
					break;
				case 1:
					res = 'F';
					break;
				case 2:
					res = 'T';
					break;
			}
			MAP[Ships_Player_1[i].y][Ships_Player_1[i].x] = res;
		}
	
		for (int i = 0; i <	Ships_Player_2.size(); i++)
		{
			char res;
			switch (Ships_Player_2[i].Type)
			{
				case 0:
					res = 'h';
					break;
				case 1:
					res = 'f';
					break;
				case 2:
					res = 't';
					break;
			}
			MAP[Ships_Player_2[i].y][Ships_Player_2[i].x] = res;
		}
	
		// Print map on console
	
		for (int y = 0; y < MAP_SIZE; y++)
		{
			for (int x = 0; x < MAP_SIZE; x++)
			{
				std::cout << MAP[y][x] << " ";
			}
		std::cout << std::endl;
		}

		// MAP is ready, now let's call algorithms
	
		//Preparing input structure for Player 1;

		Input_type Input_Player_1;
		Output_type Output_Player_1;
	
		Input_Player_1.MAP_SIZE_IN = MAP_SIZE;
		Input_Player_1.MAP_IN = MAP;
		Input_Player_1.No_Ships_IN = Ships_Player_1.size();
		for (int i = 0; i < Ships_Player_1.size(); i++)
		{
			Input_Player_1.ID_IN.push_back(Ships_Player_1[i].ID);
			Input_Player_1.Type_IN.push_back(Ships_Player_1[i].Type);
			Input_Player_1.Rotation_IN.push_back(Ships_Player_1[i].Rotation);
			Input_Player_1.HP_IN.push_back(Ships_Player_1[i].HP);
			Input_Player_1.Storage_IN.push_back(Ships_Player_1[i].Storage);
		}

		//Test_Alg_1(Input_Player_1, &Output_Player_1);
/*
		for (int i = 0; i < Output_Player_1.Commands_OUT.size(); i++)
		{
			std::cout << Output_Player_1.Commands_OUT[i] << std::endl;
		}
*/


	//Preparing input structure for Player 2;

		Input_type Input_Player_2;
		Output_type Output_Player_2;
	
		Input_Player_2.MAP_SIZE_IN = MAP_SIZE;
		Input_Player_2.MAP_IN = MAP;
		Input_Player_2.No_Ships_IN = Ships_Player_2.size();
		for (int i = 0; i < Ships_Player_2.size(); i++)
		{
			Input_Player_2.ID_IN.push_back(Ships_Player_2[i].ID);
			Input_Player_2.Type_IN.push_back(Ships_Player_2[i].Type);
			Input_Player_2.Rotation_IN.push_back(Ships_Player_2[i].Rotation);
			Input_Player_2.HP_IN.push_back(Ships_Player_2[i].HP);
			Input_Player_2.Storage_IN.push_back(Ships_Player_2[i].Storage);
		}

		Test_Alg_1(Input_Player_2, &Output_Player_2);

		for (int i = 0; i < Output_Player_2.Commands_OUT.size(); i++)
		{
			const int Player = 2;
			std::string message = Output_Player_2.Commands_OUT[i];
			std::cout << message << std::endl;
			std::vector<std::string> split;
			boost::split(split, message, boost::is_any_of(" ") );
			if (split.size() > 0)
			{
				if (split[0] == "BUILD")
				{
					if ( count_digits(split[1]) && count_digits(split[2]) && count_digits(split[3]) && count_digits(split[4]) )
					{
						int Build_x = std::stoi(split[1]);
						int Build_y = std::stoi(split[2]);
						int Build_Type = std::stoi(split[3]);
						int Build_Rotation = std::stoi(split[4]);
						if ( (Build_x >= 0 && Build_x < MAP_SIZE) && (Build_y >= 0 && Build_y < MAP_SIZE) && (Build_Type == 1 || Build_Type == 2) && (Build_Rotation > 0 && Build_Rotation < 5) ) 
						{
							if ( (Build_Type == 1 && Ships_Player_2[0].Storage > 10) || (Build_Type == 2 && Ships_Player_2[0].Storage > 20))
							{
								if (MAP[Build_y][Build_x] == '.' && Build_Near_By(Build_x,Build_y, Player, MAP) )
								{
									Ship_Class Ship = Ship_Class(Build_Type, Player, Build_x, Build_y, Build_Rotation);
									Ships_Player_2.push_back(Ship);
								}
								else
								{
									std::cout << "YOU CAN BUILD NEW SHIP OLNY NEAR BY HQ OR WORKSHOP ON EMPTY SPACE" << std::endl;
								}
							}
							else
							{
								std::cout << "NOT ENOUGHT MATERIALS TO BUILD NEW SHIP" << std::endl;
							}
						}
						else
						{
							std::cout << "BUILD COORDINATES, SHIP TYPE OR ROTATION ARE INCORRECT" << std::endl;
						}
					}
					else
					{
						std::cout << "WRONG BUILD COMMAND" << std::endl;
					}
				}
				if (split[0] == "MOVE")
				{
					if ( count_digits(split[1]) )
					{
						int Move_ID = std::stoi(split[1]);
						if (Move_ID < Ships_Player_2.size() && Move_ID != 0)
						{
							if ( Ships_Player_2[Move_ID].Speed > 0)
							{
								if (E_OK == Ships_Player_2[Move_ID].MOVE() )
								{
									Ships_Player_2[Move_ID].Speed--;
								}
								else
								{
									std::cout << "THIS SHIP CAN'T MOVE AT THIS DIRECTION" << std::endl;
								}
							}
							else
							{
								std::cout << "THIS SHIP HAVE NO POWER TO PERFORM ANY ACTION THIS TURN" << std::endl;
							}
						}
						else
						{
							std::cout << "INAVLID SHIP ID" << std::endl;
						}
					}
					else
					{
						std::cout << "WRONG MOVE COMMAND" << std::endl;
					}
				}
				if (split[0] == "ROTATE")
				{
					if (count_digits(split[1]) && (split[2] == "L" ||  split[2] == "R") )
					{
						int Rotate_ID = std::stoi(split[1]);
						char Rotate_Direction = split[2][0];
						if (Rotate_ID > Ships_Player_2.size() )
						{
							if ( Ships_Player_2[Rotate_ID].Speed > 0 )
							{
								if (E_OK == Ships_Player_2[Rotate_ID].ROTATE(Rotate_Direction) )
								{
									Ships_Player_2[Rotate_ID].Speed--;
								}
							}
							else
							{
								std::cout << "THIS SHIP HAVE NO POWER TO PERFORM ANY ACTION THIS TURN" << std::endl;
							}
						}
						else
						{
							std::cout << "INAVLID SHIP ID" << std::endl;
						}
						
					}
					else
					{
						std::cout << "WRONG ROTATE COMMAND" << std::endl;
					}
				}
				if (split[0] == "SHOOT")
				{
					if ( count_digits(split[1]) )
					{
						int Shoot_ID = std::stoi(split[1]);
						std::cout << "ID " << Shoot_ID << std::endl;
					}
				}
				if (split[0] == "WORKSHOP")
				{
					if ( count_digits(split[1]) && count_digits(split[2]) )
					{
						int Workshop_x = std::stoi(split[1]);
						int Workshop_y = std::stoi(split[2]);
						std::cout << "x " << Workshop_x << " y " << Workshop_y << std::endl;
					}
				}
				if (split[0] == "DIG")
				{
					if ( count_digits(split[1]) )
					{
						int Dig_ID = std::stoi(split[1]);
						std::cout << "ID " << Dig_ID << std::endl;
					}
				}
				if (split[0] == "END")
				{
					break;
				}
			}
		}
		std::cout << "Turns Left: " << --game_end << std::endl;
	}
	
	return E_OK;
}
