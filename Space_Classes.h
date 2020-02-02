#ifndef SPACE_CLASSES_H
#define SPACE_CLASSES_H

#include "Return_Types.h"

extern int MAP_SIZE;
int Global_ID_Ship = 0;
int Global_ID_Mine = 0;
int Global_ID_Asteroid = 0;

class Asteroid_Class
{
public:
	int ID;
	int x, y; // coordinates in space
	int HP; // Health points
	int Workshop; // 0 - none, 1 = Player 1, 2 = Player 2;

	Asteroid_Class (int p_x, int p_y)
	{
		ID = Global_ID_Asteroid;
		Global_ID_Asteroid++;
		x = p_x;
		y = p_y;
		HP = 50;
		Workshop = 0;
	}
};

class Mine_Class
{
public:
	int ID;
	int x, y; // coordinates in space
	int HP; // Health points

	Mine_Class (int p_x, int p_y)
	{
		ID = Global_ID_Mine;
		Global_ID_Mine++;
		x = p_x;
		y = p_y;
		HP = 50;
	}
};

class Ship_Class
{
public:
	int ID; // unique ID of this ship
	int Type; // Type of the ship
	int Player; // 1 = Player 1, 2 = Player 2;
	int x, y; // coordinates in space
	int Rotation; // coordinates in space 1 = x++ 2 = x-- 3 = y++ 4 = y--
	int HP; // Health points
	int Damage; // Damage shill will do when hit something
	int MAX_Storage; //Maximun count of materials that this ship can carry
	int Storage; //Actual count of materials that this sheep is carring
	int Speed; // Numbers of moves that ship can perform during one tour
	int Range; // Range of lasers

	Ship_Class (int p_Type, int p_Player, int p_x, int p_y, int p_Rotation)
	{
		ID = Global_ID_Ship;
		Global_ID_Ship++;
		Type = p_Type;
		Player = p_Player;
		x = p_x;
		y = p_y;
		Rotation = p_Rotation;
		if (Type == 0)
		{
			HP = 100;
			Damage = 1;
			MAX_Storage = 1000;
			Storage = 50;
			Speed = 2;
			Range = 2;
		}
		if (Type == 1)
		{
			HP = 5;
			Damage = 2;
			MAX_Storage = 5;
			Storage = 0;
			Speed = 3;
			Range = 3;
		}
		else if (Type == 2)
		{
			HP = 10;
			Damage = 1;
			MAX_Storage = 50;
			Storage = 0;
			Speed = 2;
			Range = 2;
		}
	}

	Return_Type MOVE (void)
	{
		Return_Type return_val = E_NOK;
		switch (Rotation)
		{
			case 1:
				if (x < MAP_SIZE - 1)
				{
					x++;
					return_val = E_OK;
				}			
				break;
			case 2:
				if (x > 0)
				{
					x--;
					return_val = E_OK;
				}			
				break;
			case 3:
				if (y < MAP_SIZE - 1)
				{
					y++;
					return_val = E_OK;
				}			
				break;
			case 4:
				if (y > 0)
				{
					y--;
					return_val = E_OK;
				}			
				break;
			default:
				return_val = E_NOK;
				break;
		}
	return return_val;
	}

	Return_Type ROTATE (char site)
	{
		Return_Type return_val = E_NOK;
		if ( (site == 'L' && Rotation == 1) || (site == 'R' && Rotation == 2) )
		{
			Rotation = 4;
			return_val = E_OK;
		}
		else if ( (site == 'L' && Rotation == 2) || (site == 'R' && Rotation == 1) )
		{
			Rotation = 3;
			return_val = E_OK;
		}
		else if ( (site == 'L' && Rotation == 4) || (site == 'R' && Rotation == 3) )
		{
			Rotation = 2;
			return_val = E_OK;
		}
		else if ( (site == 'L' && Rotation == 3) || (site == 'R' && Rotation == 4) )
		{
			Rotation = 1;
			return_val = E_OK;
		}
		else
		{
			return_val = E_NOK;
		}
		return return_val;
	}

	void reset_speed(void)
	{
		if (Type == 0)
		{
			Speed = 2;
		}
		if (Type == 1)
		{
			Speed = 3;
		}
		else if (Type == 2)
		{
			Speed = 2;
		}
	}

};


#endif
