#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include "Space_Functions.h"
#include "Space_Graphic.h"

std::ofstream COLISION_DETECTOR_LOG;
std::ofstream ACTIONS_LOG;
std::ofstream ERROR_ACTIONS_LOG;

void Space_Functions_Open()
{
	COLISION_DETECTOR_LOG.open("logs/COLISION_DETECTOR_LOG.log");
	ACTIONS_LOG.open("logs/ACTIONS_LOG.log");
	ERROR_ACTIONS_LOG.open("logs/ERROR_ACTIONS_LOG.log");
}

void Space_Functions_Close()
{
	COLISION_DETECTOR_LOG.close();
	ACTIONS_LOG.close();
	ERROR_ACTIONS_LOG.close();
}

int count_digits(const std::string& s)
{
	int ret_val;
	ret_val = std::count_if(s.begin(), s.end(),[](unsigned char c){ return std::isdigit(c); } );
	if (ret_val > 5)
	{
		ret_val = 0;
	}
	return ret_val;
}

int Build_Near_By(int y, int x, int Player, std::vector<std::vector<char> > MAP)
{
	char HQ;
	char Workshop;
	int ret_val = 0;
	if (Player == 1)
	{
		HQ = 'H';
		Workshop = 'W';
	}
	else
	{
		HQ = 'h';
		Workshop = 'w';
	}
	int size = MAP[0].size() - 1;
	if (x == 0 && y == 0)
	{
		if ( MAP[x+1][y] == HQ 
			|| MAP[x+1][y] == Workshop 
			|| MAP[x][y+1] == HQ 
			|| MAP[x][y+1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (x == 0 && y == size)
	{
		if ( MAP[x+1][y] == HQ 
			|| MAP[x+1][y] == Workshop 
			|| MAP[x][y-1] == HQ 
			|| MAP[x][y-1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (x == size && y == 0)
	{
		if ( MAP[x-1][y] == HQ 
			|| MAP[x-1][y] == Workshop 
			|| MAP[x][y+1] == HQ 
			|| MAP[x][y+1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (x == size && y == size)
	{
		if ( MAP[x-1][y] == HQ 
			|| MAP[x-1][y] == Workshop 
			|| MAP[x][y-1] == HQ 
			|| MAP[x][y-1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (x == 0)
	{
		if ( MAP[x+1][y] == HQ 
			|| MAP[x+1][y] == Workshop 
			|| MAP[x][y+1] == HQ 
			|| MAP[x][y+1] == Workshop 
			|| MAP[x][y-1] == HQ 
			|| MAP[x][y-1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (x == size)
	{
		if ( MAP[x-1][y] == HQ 
			|| MAP[x-1][y] == Workshop 
			|| MAP[x][y+1] == HQ 
			|| MAP[x][y+1] == Workshop 
			|| MAP[x][y-1] == HQ 
			|| MAP[x][y-1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (y == 0)
	{
		if ( MAP[x+1][y] == HQ 
			|| MAP[x+1][y] == Workshop 
			|| MAP[x-1][y] == HQ 
			|| MAP[x-1][y] == Workshop 
			|| MAP[x][y+1] == HQ 
			|| MAP[x][y+1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (y == size)
	{
		if ( MAP[x+1][y] == HQ 
			|| MAP[x+1][y] == Workshop 
			|| MAP[x-1][y] == HQ 
			|| MAP[x-1][y] == Workshop 
			|| MAP[x][y-1] == HQ 
			|| MAP[x][y-1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else // x > 0 && x < size && y > 0 && y < size
	{
		if ( MAP[x+1][y] == HQ 
			|| MAP[x+1][y] == Workshop 
			|| MAP[x-1][y] == HQ 
			|| MAP[x-1][y] == Workshop 
			|| MAP[x][y+1] == HQ 
			|| MAP[x][y+1] == Workshop 
			|| MAP[x][y-1] == HQ 
			|| MAP[x][y-1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	return ret_val;
}

int Workshop_Near_By(int y, int x, int Player, std::vector<std::vector<char> > MAP)
{
	char HQ;
	char Workshop;
	char Transport;
	char Fighter;
	int ret_val = 0;
	if (Player == 1)
	{
		HQ = 'H';
		Workshop = 'W';
		Transport = 'T';
		Fighter = 'F';
	}
	else
	{
		HQ = 'h';
		Workshop = 'w';
		Transport = 't';
		Fighter = 'f';
	}
	int size = MAP[0].size() - 1;
	if (x == 0 && y == 0)
	{
		if ( MAP[x+1][y] == HQ 
			|| MAP[x+1][y] == Workshop 
			|| MAP[x+1][y] == Transport 
			|| MAP[x+1][y] == Fighter
			|| MAP[x][y+1] == HQ 
			|| MAP[x][y+1] == Workshop  
			|| MAP[x][y+1] == Transport 
			|| MAP[x][y+1] == Fighter )
		{
			ret_val = 1; 
		}
	}
	else if (x == 0 && y == size)
	{
		if ( MAP[x+1][y] == HQ 
			|| MAP[x+1][y] == Workshop
			|| MAP[x+1][y] == Transport 
			|| MAP[x+1][y] == Fighter 
			|| MAP[x][y-1] == HQ 
			|| MAP[x][y-1] == Workshop 
			|| MAP[x][y-1] == Transport 
			|| MAP[x][y-1] == Fighter )
		{
			ret_val = 1; 
		}
	}
	else if (x == size && y == 0)
	{
		if ( MAP[x-1][y] == HQ 
			|| MAP[x-1][y] == Workshop 
			|| MAP[x-1][y] == Transport 
			|| MAP[x-1][y] == Fighter 
			|| MAP[x][y+1] == HQ 
			|| MAP[x][y+1] == Workshop 
			|| MAP[x][y+1] == Transport 
			|| MAP[x][y+1] == Fighter )
		{
			ret_val = 1; 
		}
	}
	else if (x == size && y == size)
	{
		if ( MAP[x-1][y] == HQ 
			|| MAP[x-1][y] == Workshop
			|| MAP[x-1][y] == Transport 
			|| MAP[x-1][y] == Fighter 
			|| MAP[x][y-1] == HQ 
			|| MAP[x][y-1] == Workshop
			|| MAP[x][y-1] == Transport 
			|| MAP[x][y-1] == Fighter )
		{
			ret_val = 1; 
		}
	}
	else if (x == 0)
	{
		if ( MAP[x+1][y] == HQ 
			|| MAP[x+1][y] == Workshop
			|| MAP[x+1][y] == Transport 
			|| MAP[x+1][y] == Fighter
			|| MAP[x][y+1] == HQ 
			|| MAP[x][y+1] == Workshop 
			|| MAP[x][y+1] == Transport 
			|| MAP[x][y+1] == Fighter
			|| MAP[x][y-1] == HQ 
			|| MAP[x][y-1] == Workshop
			|| MAP[x][y-1] == Transport 
			|| MAP[x][y-1] == Fighter)
		{
			ret_val = 1; 
		}
	}
	else if (x == size)
	{
		if ( MAP[x-1][y] == HQ 
			|| MAP[x-1][y] == Workshop 
			|| MAP[x-1][y] == Transport 
			|| MAP[x-1][y] == Fighter
			|| MAP[x][y+1] == HQ 
			|| MAP[x][y+1] == Workshop 
			|| MAP[x][y+1] == Transport 
			|| MAP[x][y+1] == Fighter
			|| MAP[x][y-1] == HQ 
			|| MAP[x][y-1] == Workshop
			|| MAP[x][y-1] == Transport 
			|| MAP[x][y-1] == Fighter)
		{
			ret_val = 1; 
		}
	}
	else if (y == 0)
	{
		if ( MAP[x+1][y] == HQ 
			|| MAP[x+1][y] == Workshop 
			|| MAP[x+1][y] == Transport
			|| MAP[x+1][y] == Fighter 
			|| MAP[x-1][y] == HQ 
			|| MAP[x-1][y] == Workshop 
			|| MAP[x-1][y] == Transport 
			|| MAP[x-1][y] == Fighter
			|| MAP[x][y+1] == HQ 
			|| MAP[x][y+1] == Workshop
			|| MAP[x][y+1] == Transport 
			|| MAP[x][y+1] == Fighter)
		{
			ret_val = 1; 
		}
	}
	else if (y == size)
	{
		if ( MAP[x+1][y] == HQ 
			|| MAP[x+1][y] == Workshop 
			|| MAP[x+1][y] == Transport 
			|| MAP[x+1][y] == Fighter 
			|| MAP[x-1][y] == HQ 
			|| MAP[x-1][y] == Workshop 
			|| MAP[x-1][y] == Transport 
			|| MAP[x-1][y] == Fighter
			|| MAP[x][y-1] == HQ 
			|| MAP[x][y-1] == Workshop
			|| MAP[x][y-1] == Transport 
			|| MAP[x][y-1] == Fighter)
		{
			ret_val = 1; 
		}
	}
	else // x > 0 && x < size && y > 0 && y < size
	{
		if ( MAP[x+1][y] == HQ 
			|| MAP[x+1][y] == Workshop 
			|| MAP[x+1][y] == Transport 
			|| MAP[x+1][y] == Fighter
			|| MAP[x-1][y] == HQ 
			|| MAP[x-1][y] == Workshop 
			|| MAP[x-1][y] == Transport 
			|| MAP[x-1][y] == Fighter
			|| MAP[x][y+1] == HQ 
			|| MAP[x][y+1] == Workshop 
			|| MAP[x][y+1] == Transport 
			|| MAP[x][y+1] == Fighter
			|| MAP[x][y-1] == HQ 
			|| MAP[x][y-1] == Workshop
			|| MAP[x][y-1] == Transport 
			|| MAP[x][y-1] == Fighter)
		{
			ret_val = 1; 
		}
	}
	return ret_val;
}


int COLISION_DETECTOR(int x, int y, std::vector<Mine_Class> Mines, std::vector<Asteroid_Class> Asteroids, std::vector<Ship_Class> Ships, char* Obj_Type)
{
	int ret_val = -1;
	char Type = '.';
	for (int i = 0; i < Mines.size(); i++)
	{
		if (x == Mines[i].x && y == Mines[i].y)
		{
			Type = 'M';
			ret_val = i;
			break;
		}
	}
	if (ret_val == -1)
	for (int i = 0; i < Asteroids.size(); i++)
	{
		if (x == Asteroids[i].x && y == Asteroids[i].y)
		{
			Type = 'A';
			ret_val = i;
			break;
		}
	}

	if (ret_val == -1)
	for (int i = 0; i < Ships.size(); i++)
	{
		if (x == Ships[i].x && y == Ships[i].y)
		{
			Type = 'S';
			ret_val = i;
			break;
		}
	}
	COLISION_DETECTOR_LOG << "INPUT: x " << x << " y " << y << " Ship_ID " << std::endl;
	COLISION_DETECTOR_LOG << "DETECT " << Type << " ID " << ret_val << std::endl;
	COLISION_DETECTOR_LOG << std::endl;
	*Obj_Type = Type;
	return ret_val;

}


int Perform_Actions(Output_type Output_Player, std::vector<Mine_Class>& Mines, std::vector<Asteroid_Class>& Asteroids, std::vector<Ship_Class>& Ships, std::vector<std::vector<char> >& MAP, int Player)
{
	static int first_line = 0;
	if (first_line == 0)
	{
		extern int MAP_seed;
		first_line = 1;
		ACTIONS_LOG << MAP_seed << std::endl;
	}
	ACTIONS_LOG << std::endl;
	int MAP_SIZE = MAP[0].size();
	int Winner = 0;
	extern int game_end;
	
	for (int i = 0; i < Output_Player.Commands_OUT.size(); i++)
	{
		if (Winner != 0)
		{
			break;
		}
		std::string message = Output_Player.Commands_OUT[i];
		//std::cout << Player << ": " << Ships[Player-1].Storage << std::endl;
		ACTIONS_LOG << message << std::endl;
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
						if ( (Build_Type == 1 && Ships[Player -1].Storage >= 10) || (Build_Type == 2 && Ships[Player -1].Storage >= 20))
						{
							if (MAP[Build_y][Build_x] == '.' && Build_Near_By(Build_x,Build_y, Player, MAP) )
							{
								Ship_Class Ship = Ship_Class(Build_Type, Player, Build_x, Build_y, Build_Rotation);
								Ships.push_back(Ship);
								char res;
								if (Player == 1)
								{
									switch (Build_Type)
									{
										case 0:
											res = 'H';
											break;
										case 1:
											res = 'F';
											Ships[Player -1].Storage -= 10;
											break;
										case 2:
											res = 'T';
											Ships[Player -1].Storage -= 20;
											break;
									}
								}
								if (Player == 2)
								{
									switch (Build_Type)
									{
										case 0:
											res = 'h';
											break;
										case 1:
											res = 'f';
											Ships[Player -1].Storage -= 10;
											break;
										case 2:
											res = 't';
											Ships[Player -1].Storage -= 20;
											break;
									}
								}
								MAP[Build_y][Build_x] = res;
								Draw_Build_Ship(Build_x, Build_y, Build_Type, Build_Rotation, Player);
							}
							else
							{
								ERROR_ACTIONS_LOG << std::endl;
								ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
								ERROR_ACTIONS_LOG << message << std::endl;
								ERROR_ACTIONS_LOG << "YOU CAN BUILD NEW SHIP OLNY NEAR BY HQ OR WORKSHOP ON EMPTY SPACE" << std::endl;
							}
						}
						else
						{
							ERROR_ACTIONS_LOG << std::endl;
							ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
							ERROR_ACTIONS_LOG << message << std::endl;
							ERROR_ACTIONS_LOG << "NOT ENOUGHT MATERIALS TO BUILD NEW SHIP" << std::endl;
						}
					}
					else
					{
						ERROR_ACTIONS_LOG << std::endl;
						ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
						ERROR_ACTIONS_LOG << message << std::endl;
						ERROR_ACTIONS_LOG << "BUILD COORDINATES, SHIP TYPE OR ROTATION ARE INCORRECT" << std::endl;
					}
				}
				else
				{
					ERROR_ACTIONS_LOG << std::endl;
					ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
					ERROR_ACTIONS_LOG << message << std::endl;
					ERROR_ACTIONS_LOG << "WRONG BUILD COMMAND" << std::endl;
				}
			}
			if (split[0] == "MOVE")
			{
				if ( count_digits(split[1]) )
				{
					int Move_ID = std::stoi(split[1]);
					int Move_iterator = -1;
					for (int i = 0; i < Ships.size(); i++)
					{
						if (Move_ID == Ships[i].ID &&  Ships[i].Player == Player )
						{
							Move_iterator = i;
						}
					}
					if (Move_iterator != -1)
					{
						if ( Ships[Move_iterator].Speed > 0 && Ships[Move_iterator].HP > 0)
						{
							int old_x = Ships[Move_iterator].x;
							int old_y = Ships[Move_iterator].y;
							char p_ship = MAP[old_y][old_x];
							if (E_OK == Ships[Move_iterator].MOVE() )
							{
								Ships[Move_iterator].Speed--;
								int p_x = Ships[Move_iterator].x;
								int p_y = Ships[Move_iterator].y;

								MAP[old_y][old_x] = '.';
								if (MAP[p_y][p_x] != '.')
								{
									char Type, colision_object;
									int Colision_Rotation = 0;
									int Colision_ID = COLISION_DETECTOR(p_x, p_y, Mines, Asteroids, Ships, &Type);
									if (Type == 'M')
									{
										colision_object = 'M';
										int HP_Mine = Mines[Colision_ID].HP - Ships[Move_iterator].HP;
										int HP_Ship = Ships[Move_iterator].HP - Mines[Colision_ID].HP;
										Mines[Colision_ID].HP = HP_Mine;
										Ships[Move_iterator].HP = HP_Ship;
										if ( Mines[Colision_ID].HP <= 0 && Ships[Move_iterator].HP <= 0)
										{
											MAP[p_y][p_x] = '.';
										}
										else if( Ships[Move_iterator].HP <= 0 )
										{
											MAP[p_y][p_x] = 'M';
										}
										else if( Mines[Colision_ID].HP <= 0 )
										{
											MAP[p_y][p_x] = p_ship;
										}
									}
									if (Type == 'A')
									{
										if (Asteroids[Colision_ID].Workshop == 0)
											colision_object = 'A';
										if (Asteroids[Colision_ID].Workshop == 1)
											colision_object = 'W';
										if (Asteroids[Colision_ID].Workshop == 2)
											colision_object = 'w';
										int HP_Asteroid = Asteroids[Colision_ID].HP - Ships[Move_iterator].HP;
										int HP_Ship = Ships[Move_iterator].HP - Asteroids[Colision_ID].HP;
										Asteroids[Colision_ID].HP = HP_Asteroid;
										Ships[Move_iterator].HP = HP_Ship;
										if ( Asteroids[Colision_ID].HP <= 0 && Ships[Move_iterator].HP <= 0)
										{
											MAP[p_y][p_x] = '.';
										}
										else if( Ships[Move_iterator].HP <= 0 )
										{
											MAP[p_y][p_x] = colision_object;
										}
										else if( Asteroids[Colision_ID].HP <= 0 )
										{
											MAP[p_y][p_x] = p_ship;
										}
									}
									if (Type == 'S')
									{
										int HP_Ship_Col = Ships[Colision_ID].HP - Ships[Move_iterator].HP;
										int HP_Ship_Mov = Ships[Move_iterator].HP - Ships[Colision_ID].HP;
										char c_ship;
										Colision_Rotation = Ships[Colision_ID].Rotation;
										if ( Ships[Colision_ID].Player == 1)
										{
											switch (Ships[Colision_ID].Type)
											{
												case 0:
													c_ship = 'H';
													colision_object = 'H';
													break;
												case 1:
													c_ship = 'F';
													colision_object = 'F';
													break;
												case 2:
													c_ship = 'T';
													colision_object = 'T';
													break;
											}
										}
										if (Ships[Colision_ID].Player == 2)
										{
											switch (Ships[Colision_ID].Type)
											{
												case 0:
													c_ship = 'h';
													colision_object = 'h';
													break;
												case 1:
													c_ship = 'f';
													colision_object = 'f';
													break;
												case 2:
													c_ship = 't';
													colision_object = 't';
													break;
											}
										}
										Ships[Colision_ID].HP = HP_Ship_Col;
										Ships[Move_iterator].HP = HP_Ship_Mov;
										if ( Ships[Colision_ID].HP <= 0 && Ships[Move_iterator].HP <= 0)
										{
											MAP[p_y][p_x] = '.';
										}
										else if( Ships[Move_iterator].HP <= 0 )
										{
											MAP[p_y][p_x] = c_ship;
										}
										else if( Ships[Colision_ID].HP <= 0 )
										{
											MAP[p_y][p_x] = p_ship;
										}
									}
								Draw_Ship_Move(p_x, p_y, Ships[Move_iterator].Rotation, Player, Ships[Move_iterator].Type, colision_object, Colision_Rotation);
								Draw_Explosion(p_x, p_y);
								Winner = Destroy_Ships(Mines, Asteroids, Ships);
								}
								else
								{
									MAP[p_y][p_x] = p_ship;
									Draw_Ship_Move(p_x, p_y, Ships[Move_iterator].Rotation, Player, Ships[Move_iterator].Type, '.', 0);
								}
							}
							else
							{
								ERROR_ACTIONS_LOG << std::endl;
								ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
								ERROR_ACTIONS_LOG << message << std::endl;
								ERROR_ACTIONS_LOG << "THIS SHIP CAN'T MOVE AT THIS DIRECTION" << std::endl;
							}
						}
						else
						{
							ERROR_ACTIONS_LOG << std::endl;
							ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
							ERROR_ACTIONS_LOG << message << std::endl;
							ACTIONS_LOG << "THIS SHIP HAVE NO POWER TO PERFORM ANY ACTION THIS TURN" << std::endl;
						}
					}
					else
					{
						ERROR_ACTIONS_LOG << std::endl;
						ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
						ERROR_ACTIONS_LOG << message << std::endl;
						ERROR_ACTIONS_LOG << "INAVLID SHIP ID" << std::endl;
					}
				}
					else
				{
					ERROR_ACTIONS_LOG << std::endl;
					ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
					ERROR_ACTIONS_LOG << message << std::endl;
					ERROR_ACTIONS_LOG << "WRONG MOVE COMMAND" << std::endl;
				}
			}
			if (split[0] == "ROTATE")
			{
				if (count_digits(split[1]) && (split[2] == "L" ||  split[2] == "R") )
				{
					int Rotate_ID = std::stoi(split[1]);
					char Rotate_Direction = split[2][0];
					int Rotate_iterator = -1;
					for (int i = 0; i < Ships.size(); i++)
					{
						if (Rotate_ID == Ships[i].ID &&  Ships[i].Player == Player)
						{
							Rotate_iterator = i;
						}
					}
					if (Rotate_iterator != -1 )
					{
						if ( Ships[Rotate_iterator].Speed > 0 && Ships[Rotate_iterator].HP > 0 )
						{
							int old_rotation = Ships[Rotate_iterator].Rotation;
							if (E_OK == Ships[Rotate_iterator].ROTATE(Rotate_Direction) )
							{
								Ships[Rotate_iterator].Speed--;
								Draw_Ship_Rotation(Ships[Rotate_iterator].x, Ships[Rotate_iterator].y, Ships[Rotate_iterator].Type, Player, Rotate_Direction, old_rotation);
							}
						}
						else
						{
							ERROR_ACTIONS_LOG << std::endl;
							ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
							ERROR_ACTIONS_LOG << message << std::endl;
							ERROR_ACTIONS_LOG << "THIS SHIP HAVE NO POWER TO PERFORM ANY ACTION THIS TURN" << std::endl;
						}
					}
					else
					{
						ERROR_ACTIONS_LOG << std::endl;
						ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
						ERROR_ACTIONS_LOG << message << std::endl;
						ERROR_ACTIONS_LOG << "INAVLID SHIP ID" << std::endl;
					}
				}
				else
				{
					ERROR_ACTIONS_LOG << std::endl;
					ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
					ERROR_ACTIONS_LOG << message << std::endl;
					ERROR_ACTIONS_LOG << "WRONG ROTATE COMMAND" << std::endl;
				}
			}
			if (split[0] == "SHOOT")
			{
				if ( count_digits(split[1]) )
				{
					int Shoot_ID = std::stoi(split[1]);
					int Shoot_iterator = -1;
					for (int i = 0; i < Ships.size(); i++)
					{
						if (Shoot_ID == Ships[i].ID && Ships[i].Player == Player)
						{
							Shoot_iterator = i;
						}
					}
					if (Shoot_iterator != -1)
					{
						if ( Ships[Shoot_iterator].Speed > 0 && Ships[Shoot_iterator].HP > 0)
						{
							Ships[Shoot_iterator].Speed--;
							int flag = 0;
							for (int i = 0; i < Ships[Shoot_iterator].Range; i++)
							{
								int p_x = Ships[Shoot_iterator].x;
								int p_y = Ships[Shoot_iterator].y;
								if (Ships[Shoot_iterator].Rotation == 1 && p_x < MAP_SIZE -i -1)
								{
									if (MAP[p_y][p_x +i +1] != '.')
									{
										flag = 1;
										char Type, col_obj;
										int Colision_ID = COLISION_DETECTOR(p_x +i +1, p_y, Mines, Asteroids, Ships, &Type);
										if (Type == 'M')
										{
											Mines[Colision_ID].HP -= Ships[Shoot_iterator].Damage;
											col_obj = 'M';
											Draw_Laser(p_x, p_y, Ships[Shoot_iterator].Rotation, Player, Ships[Shoot_iterator].Type, col_obj, 0, i+1);
											Draw_Explosion(Mines[Colision_ID].x, Mines[Colision_ID].y);
											if (Mines[Colision_ID].HP <= 0)
												MAP[Mines[Colision_ID].y][Mines[Colision_ID].x] = '.';
										}	
										if (Type == 'A')
										{
											Asteroids[Colision_ID].HP -= Ships[Shoot_iterator].Damage;
											if (Asteroids[Colision_ID].Workshop == 0)
												col_obj = 'A';
											if (Asteroids[Colision_ID].Workshop == 1)
												col_obj = 'W';
											if (Asteroids[Colision_ID].Workshop == 2)
												col_obj = 'w';
											Draw_Laser(p_x, p_y, Ships[Shoot_iterator].Rotation, Player, Ships[Shoot_iterator].Type, col_obj, 0, i+1);
											Draw_Explosion(Asteroids[Colision_ID].x, Asteroids[Colision_ID].y);
											if (Asteroids[Colision_ID].HP <= 0)
												MAP[Asteroids[Colision_ID].y][Asteroids[Colision_ID].x] = '.';
										}
										if (Type == 'S')
										{
											Ships[Colision_ID].HP -= Ships[Shoot_iterator].Damage;
											if (Ships[Colision_ID].Player == 1)
											{
												if (Ships[Colision_ID].Type == 0)
													col_obj = 'H';
												if (Ships[Colision_ID].Type == 1)
													col_obj = 'F';
												if (Ships[Colision_ID].Type == 2)
													col_obj = 'T';
											}
											if (Ships[Colision_ID].Player == 2)
											{
												if (Ships[Colision_ID].Type == 0)
													col_obj = 'h';
												if (Ships[Colision_ID].Type == 1)
													col_obj = 'f';
												if (Ships[Colision_ID].Type == 2)
													col_obj = 't';
											}
											Draw_Laser(p_x, p_y, Ships[Shoot_iterator].Rotation, Player, Ships[Shoot_iterator].Type, col_obj, Ships[Colision_ID].Rotation, i+1);
											Draw_Explosion(Ships[Colision_ID].x, Ships[Colision_ID].y);
											if (Ships[Colision_ID].HP <= 0)
												MAP[Ships[Colision_ID].y][Ships[Colision_ID].x] = '.';
										}
										Winner = Destroy_Ships(Mines, Asteroids, Ships);
										break;
									}
								}
								if (Ships[Shoot_iterator].Rotation == 2 && p_x > i) 
								{
									if (MAP[p_y][p_x -i -1] != '.')
									{
										flag = 1;
										char Type, col_obj;
										int Colision_ID = COLISION_DETECTOR(p_x -i -1, p_y, Mines, Asteroids, Ships, &Type);
										if (Type == 'M')
										{
											Mines[Colision_ID].HP -= Ships[Shoot_iterator].Damage;
											col_obj = 'M';
											Draw_Laser(p_x, p_y, Ships[Shoot_iterator].Rotation, Player, Ships[Shoot_iterator].Type, col_obj, 0, i+1);
											Draw_Explosion(Mines[Colision_ID].x, Mines[Colision_ID].y);
											if (Mines[Colision_ID].HP <= 0)
												MAP[Mines[Colision_ID].y][Mines[Colision_ID].x] = '.';
										}	
										if (Type == 'A')
										{
											Asteroids[Colision_ID].HP -= Ships[Shoot_iterator].Damage;
											if (Asteroids[Colision_ID].Workshop == 0)
												col_obj = 'A';
											if (Asteroids[Colision_ID].Workshop == 1)
												col_obj = 'W';
											if (Asteroids[Colision_ID].Workshop == 2)
												col_obj = 'w';
											Draw_Laser(p_x, p_y, Ships[Shoot_iterator].Rotation, Player, Ships[Shoot_iterator].Type, col_obj, 0, i+1);
											Draw_Explosion(Asteroids[Colision_ID].x, Asteroids[Colision_ID].y);
											if (Asteroids[Colision_ID].HP <= 0)
												MAP[Asteroids[Colision_ID].y][Asteroids[Colision_ID].x] = '.';
										}
										if (Type == 'S')
										{
											Ships[Colision_ID].HP -= Ships[Shoot_iterator].Damage;
											if (Ships[Colision_ID].Player == 1)
											{
												if (Ships[Colision_ID].Type == 0)
													col_obj = 'H';
												if (Ships[Colision_ID].Type == 1)
													col_obj = 'F';
												if (Ships[Colision_ID].Type == 2)
													col_obj = 'T';
											}
											if (Ships[Colision_ID].Player == 2)
											{
												if (Ships[Colision_ID].Type == 0)
													col_obj = 'h';
												if (Ships[Colision_ID].Type == 1)
													col_obj = 'f';
												if (Ships[Colision_ID].Type == 2)
													col_obj = 't';
											}
											Draw_Laser(p_x, p_y, Ships[Shoot_iterator].Rotation, Player, Ships[Shoot_iterator].Type, col_obj, Ships[Colision_ID].Rotation, i+1);
											Draw_Explosion(Ships[Colision_ID].x, Ships[Colision_ID].y);
											if (Ships[Colision_ID].HP <= 0)
												MAP[Ships[Colision_ID].y][Ships[Colision_ID].x] = '.';
										}
										Winner = Destroy_Ships(Mines, Asteroids, Ships);
										break;
									}
								}
								if (Ships[Shoot_iterator].Rotation == 3 && p_y < MAP_SIZE -i -1)
								{
									if (MAP[p_y +i +1][p_x] != '.')
									{
										flag = 1;
										char Type, col_obj;
										int Colision_ID = COLISION_DETECTOR(p_x, p_y +i +1, Mines, Asteroids, Ships, &Type);
										if (Type == 'M')
										{
											Mines[Colision_ID].HP -= Ships[Shoot_iterator].Damage;
											col_obj = 'M';
											Draw_Laser(p_x, p_y, Ships[Shoot_iterator].Rotation, Player, Ships[Shoot_iterator].Type, col_obj, 0, i+1);
											Draw_Explosion(Mines[Colision_ID].x, Mines[Colision_ID].y);
											if (Mines[Colision_ID].HP <= 0)
												MAP[Mines[Colision_ID].y][Mines[Colision_ID].x] = '.';
										}	
										if (Type == 'A')
										{
											Asteroids[Colision_ID].HP -= Ships[Shoot_iterator].Damage;
											if (Asteroids[Colision_ID].Workshop == 0)
												col_obj = 'A';
											if (Asteroids[Colision_ID].Workshop == 1)
												col_obj = 'W';
											if (Asteroids[Colision_ID].Workshop == 2)
												col_obj = 'w';
											Draw_Laser(p_x, p_y, Ships[Shoot_iterator].Rotation, Player, Ships[Shoot_iterator].Type, col_obj, 0, i+1);
											Draw_Explosion(Asteroids[Colision_ID].x, Asteroids[Colision_ID].y);
											if (Asteroids[Colision_ID].HP <= 0)
												MAP[Asteroids[Colision_ID].y][Asteroids[Colision_ID].x] = '.';
										}
										if (Type == 'S')
										{
											Ships[Colision_ID].HP -= Ships[Shoot_iterator].Damage;
											if (Ships[Colision_ID].Player == 1)
											{
												if (Ships[Colision_ID].Type == 0)
													col_obj = 'H';
												if (Ships[Colision_ID].Type == 1)
													col_obj = 'F';
												if (Ships[Colision_ID].Type == 2)
													col_obj = 'T';
											}
											if (Ships[Colision_ID].Player == 2)
											{
												if (Ships[Colision_ID].Type == 0)
													col_obj = 'h';
												if (Ships[Colision_ID].Type == 1)
													col_obj = 'f';
												if (Ships[Colision_ID].Type == 2)
													col_obj = 't';
											}
											Draw_Laser(p_x, p_y, Ships[Shoot_iterator].Rotation, Player, Ships[Shoot_iterator].Type, col_obj, Ships[Colision_ID].Rotation, i+1);
											Draw_Explosion(Ships[Colision_ID].x, Ships[Colision_ID].y);
											if (Ships[Colision_ID].HP <= 0)
												MAP[Ships[Colision_ID].y][Ships[Colision_ID].x] = '.';
										}
										Winner = Destroy_Ships(Mines, Asteroids, Ships);
										break;
									}
								}
								if (Ships[Shoot_iterator].Rotation == 4 && p_y > i)
								{
									if (MAP[p_y -i -1][p_x] != '.')
									{
										flag = 1;
										char Type, col_obj;
										int Colision_ID = COLISION_DETECTOR(p_x, p_y -i -1, Mines, Asteroids, Ships, &Type);
										if (Type == 'M')
										{
											Mines[Colision_ID].HP -= Ships[Shoot_iterator].Damage;
											col_obj = 'M';
											Draw_Laser(p_x, p_y, Ships[Shoot_iterator].Rotation, Player, Ships[Shoot_iterator].Type, col_obj, 0, i+1);
											Draw_Explosion(Mines[Colision_ID].x, Mines[Colision_ID].y);
											if (Mines[Colision_ID].HP <= 0)
												MAP[Mines[Colision_ID].y][Mines[Colision_ID].x] = '.';
										}	
										if (Type == 'A')
										{
											Asteroids[Colision_ID].HP -= Ships[Shoot_iterator].Damage;
											if (Asteroids[Colision_ID].Workshop == 0)
												col_obj = 'A';
											if (Asteroids[Colision_ID].Workshop == 1)
												col_obj = 'W';
											if (Asteroids[Colision_ID].Workshop == 2)
												col_obj = 'w';
											Draw_Laser(p_x, p_y, Ships[Shoot_iterator].Rotation, Player, Ships[Shoot_iterator].Type, col_obj, 0, i+1);
											Draw_Explosion(Asteroids[Colision_ID].x, Asteroids[Colision_ID].y);
											if (Asteroids[Colision_ID].HP <= 0)
												MAP[Asteroids[Colision_ID].y][Asteroids[Colision_ID].x] = '.';
										}
										if (Type == 'S')
										{
											Ships[Colision_ID].HP -= Ships[Shoot_iterator].Damage;
											if (Ships[Colision_ID].Player == 1)
											{
												if (Ships[Colision_ID].Type == 0)
													col_obj = 'H';
												if (Ships[Colision_ID].Type == 1)
													col_obj = 'F';
												if (Ships[Colision_ID].Type == 2)
													col_obj = 'T';
											}
											if (Ships[Colision_ID].Player == 2)
											{
												if (Ships[Colision_ID].Type == 0)
													col_obj = 'h';
												if (Ships[Colision_ID].Type == 1)
													col_obj = 'f';
												if (Ships[Colision_ID].Type == 2)
													col_obj = 't';
											}
											Draw_Laser(p_x, p_y, Ships[Shoot_iterator].Rotation, Player, Ships[Shoot_iterator].Type, col_obj, Ships[Colision_ID].Rotation, i+1);
											Draw_Explosion(Ships[Colision_ID].x, Ships[Colision_ID].y);
											if (Ships[Colision_ID].HP <= 0)
												MAP[Ships[Colision_ID].y][Ships[Colision_ID].x] = '.';
										}
										Winner = Destroy_Ships(Mines, Asteroids, Ships);
										break;
									}
								}
							}
							if (flag == 0)
							{
								Draw_Laser(Ships[Shoot_iterator].x, Ships[Shoot_iterator].y, Ships[Shoot_iterator].Rotation, Player, Ships[Shoot_iterator].Type, '.', 0, Ships[Shoot_iterator].Range);
							}
						}
						else
						{
							ERROR_ACTIONS_LOG << std::endl;
							ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
							ERROR_ACTIONS_LOG << message << std::endl;
							ERROR_ACTIONS_LOG << "THIS SHIP HAVE NO POWER TO PERFORM ANY ACTION THIS TURN" << std::endl;
						}
					}
					else
					{
						ERROR_ACTIONS_LOG << std::endl;
						ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
						ERROR_ACTIONS_LOG << message << std::endl;
						ERROR_ACTIONS_LOG << "INAVLID SHIP ID" << std::endl;
					}
				}
				else
				{
					ERROR_ACTIONS_LOG << std::endl;
					ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
					ERROR_ACTIONS_LOG << message << std::endl;
					ERROR_ACTIONS_LOG << "WRONG SHOOT COMMAND" << std::endl;
				}
			}
			if (split[0] == "WORKSHOP")
			{
				if ( count_digits(split[1]) && count_digits(split[2]) )
				{
					int Workshop_x = std::stoi(split[1]);
					int Workshop_y = std::stoi(split[2]);
					if ( (Workshop_x >= 0 && Workshop_x < MAP_SIZE) && (Workshop_y >= 0 && Workshop_y < MAP_SIZE) ) 
					{
						if ( Ships[Player -1].Storage >= 25 )
						{
							if (MAP[Workshop_y][Workshop_x] == 'A' && Workshop_Near_By(Workshop_x, Workshop_y, Player, MAP) )
							{
								int Workshop_iterator;
								for (int i = 0; i < Asteroids.size(); i++)
								{
									if (Workshop_x == Asteroids[i].x && Workshop_y == Asteroids[i].y )
									{
										Workshop_iterator = i;
									}
								}
								Asteroids[Workshop_iterator].Workshop = Player;
								if (Player == 1)
									MAP[Workshop_y][Workshop_x] = 'W';
								if (Player == 2)
									MAP[Workshop_y][Workshop_x] = 'w';

								Draw_Build_Workshop(Workshop_x, Workshop_y, Player);
								Ships[Player -1].Storage -= 25;									
							}
							else
							{
								ERROR_ACTIONS_LOG << std::endl;
								ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
								ERROR_ACTIONS_LOG << message << std::endl;
								ERROR_ACTIONS_LOG << "YOU CAN BUILD NEW WORKSHOP OLNY NEAR BY HQ, ANOTHER WORKSHOP OR ONE OF YOURS SHIPS ON ASTEROID" << std::endl;
							}
						}
						else
						{
							ERROR_ACTIONS_LOG << std::endl;
							ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
							ERROR_ACTIONS_LOG << message << std::endl;
							ERROR_ACTIONS_LOG << "NOT ENOUGHT MATERIALS TO BUILD NEW WORKSHOP" << std::endl;
						}
					}
					else
					{
						ERROR_ACTIONS_LOG << std::endl;
						ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
						ERROR_ACTIONS_LOG << message << std::endl;
						ERROR_ACTIONS_LOG << "BUILD COORDINATES ARE INCORRECT" << std::endl;
					}
				}
				else
				{
					ERROR_ACTIONS_LOG << std::endl;
					ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
					ERROR_ACTIONS_LOG << message << std::endl;
					ERROR_ACTIONS_LOG << "WRONG WORKSHOP COMMAND" << std::endl;
				}
			}
			if (split[0] == "DIG")
			{
				if ( count_digits(split[1]) )
				{
					int Dig_ID = std::stoi(split[1]);
					int Dig_iterator = -1;
					for (int i = 0; i < Ships.size(); i++)
					{
						if (Dig_ID == Ships[i].ID &&  Ships[i].Player == Player)
						{
							Dig_iterator = i;
						}
					}
					if (Dig_iterator != -1)
					{
						if ( Ships[Dig_iterator].Speed > 0 && Ships[Dig_iterator].HP > 0 )
						{
							Ships[Dig_iterator].Speed--;
							int p_x = Ships[Dig_iterator].x;
							int p_y = Ships[Dig_iterator].y;
							int Mine_iterator;
							if (Ships[Dig_iterator].Rotation == 1 && p_x < MAP_SIZE -1)
							{
								if (MAP[p_y][p_x +1] == 'M')
								{
									for (int i = 0; i < Mines.size(); i++)
									{
										if (p_x +1 == Mines[i].x && p_y == Mines[i].y)
										{
											Mine_iterator = i;
										}
									}
									Ships[Dig_iterator].Storage += 5;
									Mines[Mine_iterator].HP--;
									if (Ships[Dig_iterator].Storage > Ships[Dig_iterator].MAX_Storage)
									{
										Ships[Dig_iterator].Storage = Ships[Dig_iterator].MAX_Storage;
									}
									Draw_Dig(p_x, p_y, Ships[Dig_iterator].Rotation, Player, Ships[Dig_iterator].Type, 'M');
								}
								else
								{
									Draw_Dig(p_x, p_y, Ships[Dig_iterator].Rotation, Player, Ships[Dig_iterator].Type, '.');
								}
							}
							if (Ships[Dig_iterator].Rotation == 2 && p_x > 0) 
							{
								if (MAP[p_y][p_x -1] == 'M')
								{
									for (int i = 0; i < Mines.size(); i++)
									{
										if (p_x -1 == Mines[i].x && p_y == Mines[i].y)
										{
											Mine_iterator = i;
										}
									}
									Ships[Dig_iterator].Storage += 5;
									Mines[Mine_iterator].HP--;
									if (Ships[Dig_iterator].Storage > Ships[Dig_iterator].MAX_Storage)
									{
										Ships[Dig_iterator].Storage = Ships[Dig_iterator].MAX_Storage;
									}
									Draw_Dig(p_x, p_y, Ships[Dig_iterator].Rotation, Player, Ships[Dig_iterator].Type, 'M');
								}
								else
								{
									Draw_Dig(p_x, p_y, Ships[Dig_iterator].Rotation, Player, Ships[Dig_iterator].Type, '.');
								}
							}
							if (Ships[Dig_iterator].Rotation == 3 && p_y < MAP_SIZE -1)
							{
								if (MAP[p_y +1][p_x] == 'M')
								{
									for (int i = 0; i < Mines.size(); i++)
									{
										if (p_x == Mines[i].x && p_y +1 == Mines[i].y)
										{
											Mine_iterator = i;
										}
									}
									Ships[Dig_iterator].Storage += 5;
									Mines[Mine_iterator].HP--;
									if (Ships[Dig_iterator].Storage > Ships[Dig_iterator].MAX_Storage)
									{
										Ships[Dig_iterator].Storage = Ships[Dig_iterator].MAX_Storage;
									}
									Draw_Dig(p_x, p_y, Ships[Dig_iterator].Rotation, Player, Ships[Dig_iterator].Type, 'M');
								}
								else
								{
									Draw_Dig(p_x, p_y, Ships[Dig_iterator].Rotation, Player, Ships[Dig_iterator].Type, '.');
								}
							}
							if (Ships[Dig_iterator].Rotation == 4 && p_y > 0)
							{
								if (MAP[p_y -1][p_x] == 'M')
								{
									for (int i = 0; i < Mines.size(); i++)
									{
										if (p_x == Mines[i].x && p_y -1 == Mines[i].y)
										{
											Mine_iterator = i;
										}
									}
									Ships[Dig_iterator].Storage += 5;
									Mines[Mine_iterator].HP--;
									if (Ships[Dig_iterator].Storage > Ships[Dig_iterator].MAX_Storage)
									{
										Ships[Dig_iterator].Storage = Ships[Dig_iterator].MAX_Storage;
									}
									Draw_Dig(p_x, p_y, Ships[Dig_iterator].Rotation, Player, Ships[Dig_iterator].Type, 'M');
								}
								else
								{
									Draw_Dig(p_x, p_y, Ships[Dig_iterator].Rotation, Player, Ships[Dig_iterator].Type, '.');
								}
							}
							if (Mines[Mine_iterator].HP <= 0)
								MAP[Mines[Mine_iterator].y][Mines[Mine_iterator].x] = '.';
							Winner = Destroy_Ships(Mines, Asteroids, Ships);
						}
						else
						{
							ERROR_ACTIONS_LOG << std::endl;
							ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
							ERROR_ACTIONS_LOG << message << std::endl;
							ERROR_ACTIONS_LOG << "THIS SHIP HAVE NO POWER TO PERFORM ANY ACTION THIS TURN" << std::endl;
						}
					}
					else
					{
						ERROR_ACTIONS_LOG << std::endl;
						ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
						ERROR_ACTIONS_LOG << message << std::endl;
						ERROR_ACTIONS_LOG << "INAVLID SHIP ID" << std::endl;
					}
				}
				else
				{
					ERROR_ACTIONS_LOG << std::endl;
					ERROR_ACTIONS_LOG << "Player" << Player << std::endl;
					ERROR_ACTIONS_LOG << message << std::endl;
					ERROR_ACTIONS_LOG << "WRONG DIG COMMAND" << std::endl;
				}
			}
			if (split[0] == "END" || game_end == 0)
			{
				break;
			}
		}
		Draw_Whole_MAP(MAP, Mines, Asteroids, Ships);
	}
	if (Winner != 0)
		ACTIONS_LOG << "END" << std::endl << std::endl;
	return Winner;
}

int Destroy_Ships(std::vector<Mine_Class>& Mines, std::vector<Asteroid_Class>& Asteroids, std::vector<Ship_Class>& Ships)
{
	int Winner = 0;
	std::vector<int>  it_to_del;
	for (int i = 0; i < Mines.size(); i++)
	{
		std::cout << "Mine " << Mines[i].ID << " x " << Mines[i].x << " y " << Mines[i].y << " HP " << Mines[i].HP << std::endl;
		if (Mines[i].HP <= 0)
		{
			it_to_del.push_back(i);
		}
	}
	for (int i = it_to_del.size() -1; i >= 0 ; i--)
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
	for (int i = it_to_del.size() -1; i >= 0; i--)
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
			if (Ships[i].Type == 0 && Ships[i].Player == 1 )
			{
				Winner = 2;
			}
			if (Ships[i].Type == 0 && Ships[i].Player == 2 )
			{
				Winner = 1;
			}
		}
	}
	for (int i = it_to_del.size() -1; i >= 0; i--)
	{
		Ships.erase(Ships.begin() + it_to_del[i]);
	}
	it_to_del.clear();
	return Winner;
}
