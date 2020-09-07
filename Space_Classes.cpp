#include "Space_Classes.h"

extern int MAP_SIZE;
int Global_ID_Ship = 0;
int Global_ID_Mine = 0;
int Global_ID_Asteroid = 0;

Asteroid_Class::Asteroid_Class (int p_x, int p_y)
{
	ID = Global_ID_Asteroid;
	Global_ID_Asteroid++;
	x = p_x;
	y = p_y;
	HP = 50;
	Workshop = 0;
}

Mine_Class::Mine_Class (int p_x, int p_y)
{
	ID = Global_ID_Mine;
	Global_ID_Mine++;
	x = p_x;
	y = p_y;
	HP = 50;
}


Ship_Class::Ship_Class (int p_Type, int p_Player, int p_x, int p_y, int p_Rotation)
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
		MAX_Storage = 10000;
		Storage = 100;
		Speed = 0;
		Range = 2;
	}
	if (Type == 1)
	{
		HP = 4;
		Damage = 2;
		MAX_Storage = 5;
		Storage = 0;
		Speed = 0;
		Range = 3;
	}
	else if (Type == 2)
	{
		HP = 10;
		Damage = 1;
		MAX_Storage = 50;
		Storage = 0;
		Speed = 0;
		Range = 2;
	}
}


Return_Type Ship_Class::MOVE (void)
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

Return_Type Ship_Class::ROTATE (char site)
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

void Ship_Class::reset_speed(void)
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

