#ifndef SPACE_CLASSES_H
#define SPACE_CLASSES_H

#include "Return_Types.h"

class Asteroid_Class
{
public:
	int ID;
	int x, y; // coordinates in space
	int HP; // Health points
	int Workshop; // 0 - none, 1 = Player 1, 2 = Player 2;

	Asteroid_Class (int p_x, int p_y);
};

class Mine_Class
{
public:
	int ID;
	int x, y; // coordinates in space
	int HP; // Health points

	Mine_Class (int p_x, int p_y);
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

	Ship_Class (int p_Type, int p_Player, int p_x, int p_y, int p_Rotation);

	Return_Type MOVE (void);

	Return_Type ROTATE (char site);

	void reset_speed(void);

};


#endif
