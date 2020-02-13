#ifndef SPACE_GRAPHIC_H
#define SPACE_GRAPHIC_H

#include "Return_Types.h"
#include "Space_Classes.h"

typedef struct Graphical_Data
{
	int Rotate_Data;
	int Space_Data;
	int Mine_Data;
	int Asteroid_Data;

} Graphical_Data_type;

void Create_Display(int in_MAP_SIZE);
void Draw_Whole_MAP(std::vector<std::vector<char> > MAP, std::vector<Ship_Class> Ships);
void Draw_Explosion(int x, int y);
void Draw_Laser(int x, int y, int Rotation, int Player, int Type, char Colision, int Other_Rotation, int Range);
void Draw_Space(int Space_Type, int i, int j, int Center, float Scale, float Rotate);
void Draw_Mine(int Mine_Type, int i, int j, int Center, float Scale, float Rotate);
void Draw_Asteroid(int Asteroid_Type, int i, int j, int Center, float Scale, float Rotate);
void Draw_Workshop(int Player_Type, int i, int j, int Center, float Scale, float Rotate);
void Draw_HQ(int Player_Type, int i, int j, int Center, float Scale, float Rotate);
void Draw_Fighter(int Player_Type, int i, int j, int Center, float Scale, float Rotate);
void Draw_Transport(int Player_Type, int i, int j, int Center, float Scale, float Rotate);
void Draw_Build_Ship(int x, int y, int Type, int Rotation, int Player);
void Draw_Ship_Rotation(int x, int y, int Type, int Player, char Rotation, int New_Rotation);
void Draw_Ship_Move(int x, int y, int Rotation, int Player, int Type, char Colision, int Other_Rotation);
void Draw_Build_Workshop(int x, int y, int Player);
void Destroy_Display(void);

#endif

