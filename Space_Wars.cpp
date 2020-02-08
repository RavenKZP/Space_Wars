#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <errno.h>
#include <string>
#include <cctype>

int MAP_SIZE = 10;

#include "Algorithms/Algorithms.h"
#include "Space_Functions.h"
#include "Space_Graphic.h"

int main()
{
	int seed = time(NULL);
	//seed = 1580950395;
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
	std::vector<Ship_Class> Ships;
	std::vector<Mine_Class> Mines;
	std::vector<Asteroid_Class> Asteroids;

	Ship_Class HQ_Player_1 = Ship_Class(0, 1, 0, 0, 3);
	Ship_Class HQ_Player_2 = Ship_Class(0, 2, MAP_SIZE-1, MAP_SIZE-1, 4);

	Ships.push_back(HQ_Player_1);
	Ships.push_back(HQ_Player_2);


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
				Asteroid_Class Asteroid = Asteroid_Class(x,y);
				Asteroids.push_back(Asteroid); 
				//MAP[y][x] = 'A';
				//std::cout << "y " << y << " x " << x <<std::endl;
				//MAP[MAP_SIZE - y - 1][MAP_SIZE - x - 1] = 'A';
				Asteroid_Class Asteroid_2 = Asteroid_Class(MAP_SIZE - x - 1,MAP_SIZE - y - 1);
				Asteroids.push_back(Asteroid_2);
				break;
			}
		}
	}

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
				Mine_Class Mine = Mine_Class(x,y);
				Mines.push_back(Mine);
				//MAP[y][x] = 'M';
				//std::cout << "y " << y << "x " << x <<std::endl;
				//MAP[MAP_SIZE - y - 1][MAP_SIZE - x - 1] = 'M';
				Mine_Class Mine_2 = Mine_Class(MAP_SIZE -x -1,MAP_SIZE -y -1);
				Mines.push_back(Mine_2);
				break;
			}
		}
	}

	Create_Display(MAP_SIZE);
	int game_end = MAP_SIZE*MAP_SIZE*5;
	while(game_end > 0)
	{
		//Reset MAP
		for (int i = 0; i < MAP_SIZE; i++)
		{
			for (int j = 0; j < MAP_SIZE; j++)
			{
				MAP[i][j] = '.';
			}
		}
		//reset spped for ships
		for (int i = 0; i < Ships.size(); i++)
		{
			Ships[i].reset_speed();
		}

		//placing Asteroids on map
		for (int i = 0; i <	Asteroids.size(); i++)
		{
			if (Asteroids[i].Workshop == 2)
			{
				MAP[Asteroids[i].y][Asteroids[i].x] = 'w';
			}
			else if (Asteroids[i].Workshop == 1)
			{
				MAP[Asteroids[i].y][Asteroids[i].x] = 'W';
			}
			else
			{
				MAP[Asteroids[i].y][Asteroids[i].x] = 'A';
			}
		}
	
		//placing Mines on map
		for (int i = 0; i <	Mines.size(); i++)
		{
			MAP[Mines[i].y][Mines[i].x] = 'M';
		}
	
		//Placing Ships on map
	
		for (int i = 0; i <	Ships.size(); i++)
		{
			char res;
			if (Ships[i].Player == 1)
			{
				switch (Ships[i].Type)
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
				MAP[Ships[i].y][Ships[i].x] = res;
			}
			if (Ships[i].Player == 2)
			{
				switch (Ships[i].Type)
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
				MAP[Ships[i].y][Ships[i].x] = res;
			}
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

		Draw_Bitmap(MAP, Ships);
		// MAP is ready, now let's call algorithms
	
		//Preparing input structure for Player 1;

		int Player = 1;

		Input_type Input_Player_1;
		Output_type Output_Player_1;
	
		Input_Player_1.MAP_SIZE_IN = MAP_SIZE;
		Input_Player_1.MAP_IN = MAP;
		Input_Player_1.No_Ships_IN = Ships.size();
		for (int i = 0; i < Ships.size(); i++)
		{
			Input_Player_1.ID_IN.push_back(Ships[i].ID);
			Input_Player_1.Type_IN.push_back(Ships[i].Type);
			Input_Player_1.Rotation_IN.push_back(Ships[i].Rotation);
			Input_Player_1.HP_IN.push_back(Ships[i].HP);
			Input_Player_1.Storage_IN.push_back(Ships[i].Storage);
		}

		Test_Alg_1(Input_Player_1, &Output_Player_1);

		std::cout << "PLAYER " << Player << std::endl << std::endl;
		Perform_Actions(Output_Player_1, Mines, Asteroids, Ships, MAP, Player);


	//Preparing input structure for Player 2;

		Player = 2;

		Input_type Input_Player_2;
		Output_type Output_Player_2;
	
		Input_Player_2.MAP_SIZE_IN = MAP_SIZE;
		Input_Player_2.MAP_IN = MAP;
		Input_Player_2.No_Ships_IN = Ships.size();
		for (int i = 0; i < Ships.size(); i++)
		{
			Input_Player_2.ID_IN.push_back(Ships[i].ID);
			Input_Player_2.Type_IN.push_back(Ships[i].Type);
			Input_Player_2.Rotation_IN.push_back(Ships[i].Rotation);
			Input_Player_2.HP_IN.push_back(Ships[i].HP);
			Input_Player_2.Storage_IN.push_back(Ships[i].Storage);
		}

		Test_Alg_1(Input_Player_2, &Output_Player_2);

		std::cout << "PLAYER " << Player << std::endl << std::endl;
		Perform_Actions(Output_Player_2, Mines, Asteroids, Ships, MAP, Player);


		for (int i = 0; i < Ships.size(); i++)
		{
			if (Ships[i].Player == 1)
			{
				if ( (Ships[i].x == 0 && Ships[i].y == 1) || (Ships[i].x == 1 && Ships[i].y == 0) )
				{
					Ships[0].Storage += Ships[i].Storage;
					Ships[i].Storage = 0;
				}
			}
			if (Player == 2)
			{
				if ( (Ships[i].x == MAP_SIZE -1 && Ships[i].y == MAP_SIZE -2) || (Ships[i].x == MAP_SIZE -2 && Ships[i].y == MAP_SIZE -1) )
				{
					Ships[1].Storage += Ships[i].Storage;
					Ships[i].Storage = 0;
				}
			}
		}
		

		
		std::vector<int> it_to_del;
		for (int i = 0; i < Mines.size(); i++)
		{
			std::cout << "Mine " << Mines[i].ID << " x " << Mines[i].x << " y " << Mines[i].y << " HP " << Mines[i].HP << std::endl;
			if (Mines[i].HP <= 0)
			{
				it_to_del.push_back(i);
			}
		}
		for (int i = 0; i < it_to_del.size(); i++)
		{
			Mines.erase(Mines.begin() + it_to_del[i]);
		}
		it_to_del.clear();
		for (int i = 0; i < Asteroids.size(); i++)
		{
			std::cout << "Asteroid " << Asteroids[i].ID << " x " << Asteroids[i].x << " y " << Asteroids[i].y << " HP " << Asteroids[i].HP << " Workshop_Player " << Asteroids[i].Workshop << std::endl;
			if (Asteroids[i].HP <= 0)
			{
				it_to_del.push_back(i);
			}
		}
		for (int i = 0; i < it_to_del.size(); i++)
		{
			Asteroids.erase(Asteroids.begin() + it_to_del[i]);
		}
		it_to_del.clear();
		for (int i = 0; i < Ships.size(); i++)
		{
			std::cout << "Ship " << Ships[i].ID << " x " << Ships[i].x << " y " << Ships[i].y << " HP " << Ships[i].HP << " Rotation " << Ships[i].Rotation << " Type " << Ships[i].Type << " Player " << Ships[i].Player << " Storage " << Ships[i].Storage << std::endl;
			if (Ships[i].HP <= 0)
			{
				it_to_del.push_back(i);
			}
		}
		for (int i = 0; i < it_to_del.size(); i++)
		{
			Ships.erase(Ships.begin() + it_to_del[i]);
		}
		it_to_del.clear();

		std::cout << "Seed: " << seed << std::endl;
		std::cout << "Turns Left: " << --game_end << std::endl;
	}
	Destroy_Display();
	return E_OK;
}
