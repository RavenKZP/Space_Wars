#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string>
#include <cctype>
#include <thread>

int MAP_seed = time(NULL);
int MAP_SIZE = 10;
int Player_Alg[2] = {1,1};
int game_end = MAP_SIZE*MAP_SIZE*5;

#include "Algorithms/Algorithms.h"
#include "Space_Functions.h"
#include "Space_Graphic.h"


int main()
{
	std::ofstream MAP_LOG;
	MAP_LOG.open("logs/MAP_LOG.log");
	Space_Functions_Open();
	Create_Display();
	TITLE_SCREEN();
	srand(MAP_seed);
	//MAP
	std::vector<std::vector<char> > MAP;
	//generating map
	
	int Number_of_Asteroids = MAP_SIZE/10 * (MAP_SIZE - rand()%(MAP_SIZE/2)); 			//for MAP_SIZE = 10 is from 5 to 10
	int Number_of_Mines = MAP_SIZE/10 * (MAP_SIZE - rand()%(MAP_SIZE/2)); 					//for MAP_SIZE = 10 is from 5 to 10

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
				max_size--;
			}
			else
			{
				Mine_Class Mine = Mine_Class(x,y);
				Mines.push_back(Mine);
				Mine_Class Mine_2 = Mine_Class(MAP_SIZE -x -1,MAP_SIZE -y -1);
				Mines.push_back(Mine_2);
				break;
			}
		}
	}

	int Winner = 0;
	int Player = 1;
	int Other_Player = 2;

	MAP_LOG << MAP_seed << std::endl;
	game_end = MAP_SIZE*MAP_SIZE*5;

	while(game_end > 0 && Winner == 0)
	{
		int No_Ships_Player = 0;
		//reset spped for ships
		for (int i = 0; i < Ships.size(); i++)
		{
			Ships[i].reset_speed();
		}

		//Reset MAP
		for (int i = 0; i < MAP_SIZE; i++)
		{
			for (int j = 0; j < MAP_SIZE; j++)
			{
				MAP[i][j] = '.';
			}
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

		Draw_Whole_MAP(MAP, Mines, Asteroids, Ships);
		// MAP is ready, now let's call algorithms
		MAP_LOG << "Turn: " << MAP_SIZE*MAP_SIZE*5 - game_end << std::endl;

		MAP_LOG << "MINES" << std::endl;
		for (int i = 0; i < Mines.size(); i++)
		{
			MAP_LOG << "Mine coords: x = " << Mines[i].x << " y = " << Mines[i].y;
			MAP_LOG << " ID: " << Mines[i].ID;
			MAP_LOG << " HP: " << Mines[i].HP;
			MAP_LOG << std::endl;
			
		}
		MAP_LOG << "ASTEROIDS" << std::endl;
		for (int i = 0; i < Asteroids.size(); i++)
		{
			MAP_LOG << "Asteroid coords: x = " << Asteroids[i].x << " y = " << Asteroids[i].y;
			MAP_LOG << " ID: " << Asteroids[i].ID;
			MAP_LOG << " HP: " << Asteroids[i].HP;
			MAP_LOG << " Ws: " << Asteroids[i].Workshop;
			MAP_LOG << std::endl;
			
		}

		MAP_LOG << "SHIPS" << std::endl;
		for (int i = 0; i < Ships.size(); i++)
		{
			MAP_LOG << "Ship coords: x = " << Ships[i].x << " y = " << Ships[i].y;
			MAP_LOG << " ID: " << Ships[i].ID;
			MAP_LOG << " Tp: " << Ships[i].Type;
			MAP_LOG << " Rt: " << Ships[i].Rotation;
			MAP_LOG << " HP: " << Ships[i].HP;
			MAP_LOG << " St: " << Ships[i].Storage;
			MAP_LOG << " Mv: " << Ships[i].Speed;
			MAP_LOG << std::endl;	
		}

		for (int i = 0; i < MAP.size(); i++)
		{
			for (int j = 0; j < MAP[i].size(); j++)
			{
				MAP_LOG << MAP[i][j];
			}
		MAP_LOG << std::endl;
		}
		MAP_LOG << std::endl;
	
		//Preparing input structure for Player;

		Input_type Input_Player;
		Output_type Output_Player;
	
		Input_Player.MAP_SIZE_IN = MAP_SIZE;
		Input_Player.MAP_IN = MAP;
		Input_Player.PLAYER_IN = Player;
		for (int i = 0; i < Ships.size(); i++)
		{
			if (Ships[i].Player == Player)
			{
				Input_Player.ID_IN.push_back(Ships[i].ID);
				Input_Player.Type_IN.push_back(Ships[i].Type);
				Input_Player.Rotation_IN.push_back(Ships[i].Rotation);
				Input_Player.HP_IN.push_back(Ships[i].HP);
				Input_Player.Storage_IN.push_back(Ships[i].Storage);
				Input_Player.X_IN.push_back(Ships[i].x);
				Input_Player.Y_IN.push_back(Ships[i].y);
				No_Ships_Player++;
			}
		}
		Input_Player.No_Ships_IN = No_Ships_Player;
		std::thread thread_Player;

		if (Player_Alg[Player-1] == 1)
			thread_Player = std::thread(Ants_Algorithm, Input_Player, std::ref(Output_Player) );
		if (Player_Alg[Player-1] == 2)
			thread_Player = std::thread(Replayer_Alborithm, Input_Player, std::ref(Output_Player) );

		usleep(500);

		if (!Output_Player.Commands_OUT.empty())
			Winner = Perform_Actions(Output_Player, Mines, Asteroids, Ships, MAP, Player);
		else
			Winner = Other_Player;

		thread_Player.detach();

		for (int i = 2; i < Ships.size(); i++)
		{
			if (Ships[i].Player == 1)
			{
				if ( (Ships[i].x +1 == Ships[0].x && Ships[i].y == Ships[0].y) || (Ships[i].x == Ships[0].x -1 && Ships[i].y == Ships[0].y) || (Ships[i].x == Ships[0].x && Ships[i].y +1 == Ships[0].y) || (Ships[i].x == Ships[0].x && Ships[i].y -1 == Ships[0].y))
				{
					Ships[0].Storage += Ships[i].Storage;
					Ships[i].Storage = 0;
				}
			}
			if (Player == 2)
			{
				if ( (Ships[i].x +1 == Ships[1].x && Ships[i].y == Ships[1].y) || (Ships[i].x == Ships[1].x -1 && Ships[i].y == Ships[1].y) || (Ships[i].x == Ships[1].x && Ships[i].y +1 == Ships[1].y) || (Ships[i].x == Ships[1].x && Ships[i].y -1 == Ships[1].y))
				{
					Ships[1].Storage += Ships[i].Storage;
					Ships[i].Storage = 0;
				}
			}
		}
	
		int Income = 11 - No_Ships_Player;
		if (Income > 0)
			Ships[Player-1].Storage += Income;

		if (Ships[Player-1].Storage > Ships[Player-1].MAX_Storage)
		{
			Ships[Player-1].Storage = Ships[Player-1].MAX_Storage;
		}

		std::swap(Player, Other_Player);

		std::cout << "Seed: " << MAP_seed << std::endl;
		std::cout << "Turns Left: " << --game_end << std::endl;
	}
	if (Winner == 0)
		if (Ships[0].Storage > Ships[1].Storage)
			Winner = 1;
		else
			Winner = 2;

	std::cout << "WINNER IS: Player " << Winner << std::endl;
	Display_Winner(Winner);
	MAP_LOG.close();
	Destroy_Display();	
	Space_Functions_Close();
	return E_OK;
}
