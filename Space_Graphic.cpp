#include <stdio.h>
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Space_Graphic.h"

#define PI 3.141592653589793238462643383279502884197169
#define RADIANS 1.57079633 // 90 degrees
#define TILE_SIZE 80.0
#define IMAGE_SIZE 330.0
#define FONT_SIZE 15

float animation_speed = 0.01;

float Ship_Rotate(std::vector<Ship_Class> Ships, int y, int x);

int Player_1_Type = 0;
int	Player_2_Type = 0;

int seed;
extern int MAP_SIZE;

std::vector<std::vector< Graphical_Data_type>> Graphical_Data_Matrix;

ALLEGRO_DISPLAY *display = NULL;

ALLEGRO_BITMAP *Asteroid_1 = NULL;
ALLEGRO_BITMAP *Asteroid_2 = NULL;
ALLEGRO_BITMAP *Asteroid_3 = NULL;
ALLEGRO_BITMAP *Black = NULL;
ALLEGRO_BITMAP *Explosion_1 = NULL;
ALLEGRO_BITMAP *Fighter_1 = NULL;
ALLEGRO_BITMAP *Fighter_2 = NULL;
ALLEGRO_BITMAP *Fighter_3 = NULL;
ALLEGRO_BITMAP *Fighter_4 = NULL;
ALLEGRO_BITMAP *HQ_1 = NULL;
ALLEGRO_BITMAP *HQ_2 = NULL;
ALLEGRO_BITMAP *HQ_3 = NULL;
ALLEGRO_BITMAP *HQ_4 = NULL;
ALLEGRO_BITMAP *Laser_1 = NULL;
ALLEGRO_BITMAP *Laser_2 = NULL;
ALLEGRO_BITMAP *Laser_3 = NULL;
ALLEGRO_BITMAP *Laser_4 = NULL;
ALLEGRO_BITMAP *Mine_1 = NULL;
ALLEGRO_BITMAP *Mine_2 = NULL;
ALLEGRO_BITMAP *Mine_3 = NULL;
ALLEGRO_BITMAP *Mine_4 = NULL;
ALLEGRO_BITMAP *Stars_1 = NULL;
ALLEGRO_BITMAP *Stars_2 = NULL;
ALLEGRO_BITMAP *Stars_3 = NULL;
ALLEGRO_BITMAP *Stars_4 = NULL;
ALLEGRO_BITMAP *Transport_1 = NULL;
ALLEGRO_BITMAP *Transport_2 = NULL;
ALLEGRO_BITMAP *Transport_3 = NULL;
ALLEGRO_BITMAP *Transport_4 = NULL;
ALLEGRO_BITMAP *Workshop_1 = NULL;
ALLEGRO_BITMAP *Workshop_2 = NULL;
ALLEGRO_BITMAP *Workshop_3 = NULL;
ALLEGRO_BITMAP *Workshop_4 = NULL;
ALLEGRO_BITMAP *Ship = NULL;

ALLEGRO_FONT *font = NULL;

void Create_Display()
{
	seed = time(NULL);	
	srand(seed);

	while(Player_2_Type == Player_1_Type)
	{
		Player_2_Type = rand()%4+1;
		Player_1_Type = rand()%4+1;
	}

	for(int j = 0; j < MAP_SIZE; j++)
	{
		std::vector<Graphical_Data_type> temp;
		for(int i = 0; i < MAP_SIZE; i++)
		{
			float Rotate = rand();
			int Space_Type = rand()%10 +1;
			int Mine_Type = rand()%4 +1;
			int Asteroid_Type = rand()%3 +1;
			Graphical_Data_type Type_temp;

			Type_temp.Rotate_Data = Rotate;
			Type_temp.Space_Data = Space_Type;
			Type_temp.Mine_Data = Mine_Type;
			Type_temp.Asteroid_Data = Asteroid_Type;
			temp.push_back(Type_temp);
		}
		Graphical_Data_Matrix.push_back(temp);
	}
	
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	display = al_create_display(MAP_SIZE*TILE_SIZE+TILE_SIZE*5, MAP_SIZE*TILE_SIZE);


  font = al_load_ttf_font("Fonts/Year 2000.ttf", FONT_SIZE, 0 );


	Asteroid_1 = al_load_bitmap("Images/Asteroid_1.png");
	Asteroid_2 = al_load_bitmap("Images/Asteroid_2.png");
	Asteroid_3 = al_load_bitmap("Images/Asteroid_3.png");
	Explosion_1 = al_load_bitmap("Images/Explosion_1.png");
	Black = al_load_bitmap("Images/Black.png");
	Fighter_1 = al_load_bitmap("Images/Fighter_1.png");
	Fighter_2 = al_load_bitmap("Images/Fighter_2.png");
	Fighter_3 = al_load_bitmap("Images/Fighter_3.png");
	Fighter_4 = al_load_bitmap("Images/Fighter_4.png");
	HQ_1 = al_load_bitmap("Images/HQ_1.png");
	HQ_2 = al_load_bitmap("Images/HQ_2.png");
	HQ_3 = al_load_bitmap("Images/HQ_3.png");
	HQ_4 = al_load_bitmap("Images/HQ_4.png");
	Laser_1 = al_load_bitmap("Images/Laser_1.png");
	Laser_2 = al_load_bitmap("Images/Laser_2.png");
	Laser_3 = al_load_bitmap("Images/Laser_3.png");
	Laser_4 = al_load_bitmap("Images/Laser_4.png");
	Mine_1 = al_load_bitmap("Images/Mine_1.png");
	Mine_2 = al_load_bitmap("Images/Mine_2.png");
	Mine_3 = al_load_bitmap("Images/Mine_3.png");
	Mine_4 = al_load_bitmap("Images/Mine_4.png");
	Stars_1 = al_load_bitmap("Images/Stars_1.png");
	Stars_2 = al_load_bitmap("Images/Stars_2.png");
	Stars_3 = al_load_bitmap("Images/Stars_3.png");
	Stars_4 = al_load_bitmap("Images/Stars_4.png");
	Transport_1 = al_load_bitmap("Images/Transport_1.png");
	Transport_2 = al_load_bitmap("Images/Transport_2.png");
	Transport_3 = al_load_bitmap("Images/Transport_3.png");
	Transport_4 = al_load_bitmap("Images/Transport_4.png");
	Workshop_1 = al_load_bitmap("Images/Workshop_1.png");
	Workshop_2 = al_load_bitmap("Images/Workshop_2.png");
	Workshop_3 = al_load_bitmap("Images/Workshop_3.png");
	Workshop_4 = al_load_bitmap("Images/Workshop_4.png");
}

void Display_Stats(std::vector<Mine_Class> Mines, std::vector<Asteroid_Class> Asteroids, std::vector<Ship_Class> Ships)
{
	int global_i = 0;
	for (int i = 0; i < Mines.size(); i++)
	{
		std::string Mine_description;
		Mine_description = "Mine x " + std::to_string(Mines[i].x) + " y " + std::to_string(Mines[i].y) + " ID " + std::to_string(Mines[i].ID) + " HP " +  std::to_string(Mines[i].HP);
		char desc[Mine_description.size()];
		for (int j = 0; j < sizeof(desc); j++) 
		{ 
    	desc[j] = Mine_description[j]; 
    } 
		al_draw_text(font, al_map_rgb(255,255,255), MAP_SIZE*TILE_SIZE+TILE_SIZE*2.5, global_i*FONT_SIZE, ALLEGRO_ALIGN_CENTRE, desc);
		global_i += 1;
	}
	for (int i = 0; i < Asteroids.size(); i++)
	{
		std::string Asteroid_description;
		Asteroid_description = "Asteroid x " + std::to_string(Asteroids[i].x) + " y " + std::to_string(Asteroids[i].y) + " ID " + std::to_string(Asteroids[i].ID) + " HP " +  std::to_string(Asteroids[i].HP) + " Workshop: " + std::to_string(Asteroids[i].Workshop);
		char desc[Asteroid_description.size()];
		for (int j = 0; j < sizeof(desc); j++) 
		{ 
    	desc[j] = Asteroid_description[j]; 
    } 
		al_draw_text(font, al_map_rgb(255,255,255), MAP_SIZE*TILE_SIZE+TILE_SIZE*2.5, global_i*FONT_SIZE, ALLEGRO_ALIGN_CENTRE, desc);
		global_i += 1;
	}
	for (int i = 0; i < Ships.size(); i++)
	{
		std::string Ship_description;
		Ship_description = "Ship x " + std::to_string(Ships[i].x) + " y " + std::to_string(Ships[i].y) + " ID " + std::to_string(Ships[i].ID) + " HP " +  std::to_string(Ships[i].HP);
		char desc[Ship_description.size()];
		for (int j = 0; j < sizeof(desc); j++) 
		{ 
    	desc[j] = Ship_description[j]; 
    } 
		al_draw_text(font, al_map_rgb(255,255,255), MAP_SIZE*TILE_SIZE+TILE_SIZE*2.5, global_i*FONT_SIZE, ALLEGRO_ALIGN_CENTRE, desc);
		global_i += 1;
	}
}

void Draw_Whole_MAP(std::vector<std::vector<char> > MAP, std::vector<Mine_Class> Mines, std::vector<Asteroid_Class> Asteroids, std::vector<Ship_Class> Ships)
{
	srand(seed);
	float Scale = TILE_SIZE/IMAGE_SIZE;
	float Center = IMAGE_SIZE/2;
	int MAP_SIZE = MAP[0].size();

	al_clear_to_color(al_map_rgb(0,0,0));

	for(int j = 0; j < MAP.size(); j++)
	{
		for(int i = 0; i < MAP.size(); i++)
		{
			float Rotate = Graphical_Data_Matrix[j][i].Rotate_Data;
			int Space_Type = Graphical_Data_Matrix[j][i].Space_Data;
			int Mine_Type = Graphical_Data_Matrix[j][i].Mine_Data;
			int Asteroid_Type = Graphical_Data_Matrix[j][i].Asteroid_Data;
			Draw_Space(Space_Type, i, j, Center, Scale, Rotate);
			switch (MAP[j][i])
			{
				case 'A':
					Draw_Asteroid(Asteroid_Type, i, j, Center, Scale, Rotate);
					break;
				case 'M':
					Draw_Mine(Mine_Type, i, j, Center, Scale, Rotate);
					break;
				case 'W':
					Draw_Workshop(Player_1_Type, i, j, Center, Scale, Rotate);
					break;
				case 'w':
					Draw_Workshop(Player_2_Type, i, j, Center, Scale, Rotate);
					break;
				case 'H':
					Draw_HQ(Player_1_Type, i, j, Center, Scale, Ship_Rotate(Ships, i, j));
					break;
				case 'h':
					Draw_HQ(Player_2_Type, i, j, Center, Scale, Ship_Rotate(Ships, i, j));
					break;
				case 'F':
					Draw_Fighter(Player_1_Type, i, j, Center, Scale, Ship_Rotate(Ships, i, j));
					break;
				case 'f':
					Draw_Fighter(Player_2_Type, i, j, Center, Scale, Ship_Rotate(Ships, i, j));
					break;
				case 'T':
					Draw_Transport(Player_1_Type, i, j, Center, Scale, Ship_Rotate(Ships, i, j));
					break;
				case 't':
					Draw_Transport(Player_2_Type, i, j, Center, Scale, Ship_Rotate(Ships, i, j));
					break;
			}
		}
	}
	Display_Stats(Mines, Asteroids, Ships);
	al_flip_display();
	al_rest(animation_speed*2);
}

void Draw_Explosion(int x, int y)
{
	float Center = IMAGE_SIZE/2;
	float Scale;
	float Rotate = rand();
	for (int i = 0; i < 15; i++)
	{
		Scale = (TILE_SIZE/IMAGE_SIZE) * (i/10.0);
		al_draw_scaled_rotated_bitmap(Explosion_1, Center, Center, x*TILE_SIZE +TILE_SIZE/2, y*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
		al_flip_display();
		al_rest(animation_speed);
	}
}

void Draw_Space(int Space_Type, int i, int j, int Center, float Scale, float Rotate)
{
	if (Space_Type == 2)
		al_draw_scaled_rotated_bitmap(Stars_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale, RADIANS*Rotate, 0);
	else if (Space_Type == 4)
		al_draw_scaled_rotated_bitmap(Stars_3, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale, RADIANS*Rotate, 0);
	else if (Space_Type == 6)
		al_draw_scaled_rotated_bitmap(Stars_4, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale, RADIANS*Rotate, 0);
	else
		al_draw_scaled_rotated_bitmap(Stars_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale, RADIANS*Rotate, 0);
}

void Draw_Mine(int Mine_Type, int i, int j, int Center, float Scale, float Rotate)
{
	if (Mine_Type == 1)
		al_draw_scaled_rotated_bitmap(Mine_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Mine_Type == 2)
		al_draw_scaled_rotated_bitmap(Mine_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Mine_Type == 3)
		al_draw_scaled_rotated_bitmap(Mine_3, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Mine_Type == 4)
		al_draw_scaled_rotated_bitmap(Mine_4, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
}

void Draw_Asteroid(int Asteroid_Type, int i, int j, int Center, float Scale, float Rotate)
{
	if (Asteroid_Type == 1)
		al_draw_scaled_rotated_bitmap(Asteroid_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Asteroid_Type == 2)
		al_draw_scaled_rotated_bitmap(Asteroid_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Asteroid_Type == 3)
		al_draw_scaled_rotated_bitmap(Asteroid_3, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
}

void Draw_Workshop(int Player_Type, int i, int j, int Center, float Scale, float Rotate)
{
	if (Player_Type == 1)
		al_draw_scaled_rotated_bitmap(Workshop_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Player_Type == 2)
		al_draw_scaled_rotated_bitmap(Workshop_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Player_Type == 3)
		al_draw_scaled_rotated_bitmap(Workshop_3, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Player_Type == 4)
		al_draw_scaled_rotated_bitmap(Workshop_4, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
}


void Draw_HQ(int Player_Type, int i, int j, int Center, float Scale, float Rotate)
{
	if (Player_Type == 1)
		al_draw_scaled_rotated_bitmap(HQ_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Player_Type == 2)
		al_draw_scaled_rotated_bitmap(HQ_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Player_Type == 3)
		al_draw_scaled_rotated_bitmap(HQ_3, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Player_Type == 4)
		al_draw_scaled_rotated_bitmap(HQ_4, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
}


void Draw_Fighter(int Player_Type, int i, int j, int Center, float Scale, float Rotate)
{
	if (Player_Type == 1)
		al_draw_scaled_rotated_bitmap(Fighter_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Player_Type == 2)
		al_draw_scaled_rotated_bitmap(Fighter_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Player_Type == 3)
		al_draw_scaled_rotated_bitmap(Fighter_3, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Player_Type == 4)
		al_draw_scaled_rotated_bitmap(Fighter_4, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
}
void Draw_Transport(int Player_Type, int i, int j, int Center, float Scale, float Rotate)
{
	if (Player_Type == 1)
		al_draw_scaled_rotated_bitmap(Transport_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Player_Type == 2)
		al_draw_scaled_rotated_bitmap(Transport_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Player_Type == 3)
		al_draw_scaled_rotated_bitmap(Transport_3, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
	if (Player_Type == 4)
		al_draw_scaled_rotated_bitmap(Transport_4, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Rotate, 0);
}

float Ship_Rotate(std::vector<Ship_Class> Ships, int x, int y)
{
	int res = 1;
	float Return_value;
	for (int i = 0; i < Ships.size(); i++)
	{
		if (Ships[i].x == x && Ships[i].y == y)
		{
			res = Ships[i].Rotation;
			break;
		}
	}
	if (res == 1)
		Return_value = RADIANS*1.0;
	if (res == 2)
		Return_value = RADIANS*3.0;
	if (res == 3)
		Return_value = RADIANS*2.0;
	if (res == 4)
		Return_value = RADIANS*0.0;

	return Return_value;
}

float Simple_Ship_Rotate(int Ship_Rotation)
{
	int res = Ship_Rotation;
	float Return_value;
	if (res == 1)
		Return_value = RADIANS*1.0;
	if (res == 2)
		Return_value = RADIANS*3.0;
	if (res == 3)
		Return_value = RADIANS*2.0;
	if (res == 4)
		Return_value = RADIANS*0.0;

	return Return_value;
}

void Draw_Build_Ship(int x, int y, int Type, int Rotation, int Player)
{
	float Scale = TILE_SIZE/IMAGE_SIZE;
	float Center = IMAGE_SIZE/2;
	int Player_Type;
	float Rotate;
	float Position_x = (x*TILE_SIZE +TILE_SIZE/2);
	float Position_y = (y*TILE_SIZE +TILE_SIZE/2);

	if (Player == 1)
		Player_Type = Player_1_Type;
	if (Player == 2)
		Player_Type = Player_2_Type;

	if (Type == 1) //Fighter
	{
		if (Player_Type == 1)
			Ship = Fighter_1;
		if (Player_Type == 2)
			Ship = Fighter_2;
		if (Player_Type == 3)
			Ship = Fighter_3;
		if (Player_Type == 4)
			Ship = Fighter_4;
	}
	if (Type == 2) //Transport
	{
		if (Player_Type == 1)
			Ship = Transport_1;
		if (Player_Type == 2)
			Ship = Transport_2;
		if (Player_Type == 3)
			Ship = Transport_3;
		if (Player_Type == 4)
			Ship = Transport_4;
	}

	if (Rotation == 1)
		Rotate = RADIANS*1.0;
	if (Rotation == 2)
		Rotate = RADIANS*3.0;
	if (Rotation == 3)
		Rotate = RADIANS*2.0;
	if (Rotation == 4)
		Rotate = RADIANS*0.0;

	for (int i = 0; i < 15; i++)
	{
		float Currect_Scale = ((i*Scale)/14.0);
		//DRAW BLACK ON ANIMATED TILES
		al_draw_scaled_rotated_bitmap(Black, Center, Center, Position_x, Position_y, Scale, Scale,  0, 0);
		//DRAW SPACE ON ANIMATED TILES
		Draw_Space(Graphical_Data_Matrix[y][x].Space_Data, x, y, Center, Scale, Graphical_Data_Matrix[y][x].Rotate_Data);

		//DRAW SHIP ON ANIMATED TILES
		al_draw_scaled_rotated_bitmap(Ship, Center, Center, Position_x, Position_y, Currect_Scale, Currect_Scale, (i*Rotate)/14.0, 0);
		al_flip_display();
		al_rest(animation_speed);
	}
}

void Draw_Ship_Rotation(int x, int y, int Type, int Player, char Rotation, int Old_Rotation)
{
	
	float Scale = TILE_SIZE/IMAGE_SIZE;
	float Center = IMAGE_SIZE/2;
	int Player_Type;
	float New_Rotate, Old_Rotate;
	float Position_x = (x*TILE_SIZE +TILE_SIZE/2);
	float Position_y = (y*TILE_SIZE +TILE_SIZE/2);

	if (Player == 1)
		Player_Type = Player_1_Type;
	if (Player == 2)
		Player_Type = Player_2_Type;


	if (Type == 0) //HQ
	{
		if (Player_Type == 1)
			Ship = HQ_1;
		if (Player_Type == 2)
			Ship = HQ_2;
		if (Player_Type == 3)
			Ship = HQ_3;
		if (Player_Type == 4)
			Ship = HQ_4;
	}
	if (Type == 1) //Fighter
	{
		if (Player_Type == 1)
			Ship = Fighter_1;
		if (Player_Type == 2)
			Ship = Fighter_2;
		if (Player_Type == 3)
			Ship = Fighter_3;
		if (Player_Type == 4)
			Ship = Fighter_4;
	}
	if (Type == 2) //Transport
	{
		if (Player_Type == 1)
			Ship = Transport_1;
		if (Player_Type == 2)
			Ship = Transport_2;
		if (Player_Type == 3)
			Ship = Transport_3;
		if (Player_Type == 4)
			Ship = Transport_4;
	}

	if (Old_Rotation == 1)
		Old_Rotate = RADIANS*5.0;
	if (Old_Rotation == 2)
		Old_Rotate = RADIANS*7.0;
	if (Old_Rotation == 3)
		Old_Rotate = RADIANS*6.0;
	if (Old_Rotation == 4)
		Old_Rotate = RADIANS*4.0;

	for (int i = 0; i < 15; i++)
	{
		float Rotate;
		if (Rotation == 'R')
	  	Rotate = Old_Rotate + RADIANS*i/14.0;
		else
			Rotate = Old_Rotate - RADIANS*i/14.0;
			
		//DRAW BLACK ON ANIMATED TILES
		al_draw_scaled_rotated_bitmap(Black, Center, Center, Position_x, Position_y, Scale, Scale,  0, 0);
		//DRAW SPACE ON ANIMATED TILES
		Draw_Space(Graphical_Data_Matrix[y][x].Space_Data, x, y, Center, Scale, Graphical_Data_Matrix[y][x].Rotate_Data);

		//DRAW SHIP ON ANIMATED TILES
		al_draw_scaled_rotated_bitmap(Ship, Center, Center, Position_x, Position_y, Scale, Scale, Rotate, 0);
		al_flip_display();
		al_rest(animation_speed);
	}
}

void Draw_Laser(int x, int y, int Rotation, int Player, int Type, char Colision, int Other_Rotation, int Range)
{
	float Scale = TILE_SIZE/IMAGE_SIZE;
	float Center = IMAGE_SIZE/2;
	int Player_Type;
	float Rotate, Ship_Rotate;	
	float Position_x = (x*TILE_SIZE +TILE_SIZE/2);
	float Position_y = (y*TILE_SIZE +TILE_SIZE/2);
	float first_x = (x*TILE_SIZE +TILE_SIZE/2);
	float first_y = (y*TILE_SIZE +TILE_SIZE/2);
	float secound_x = (x*TILE_SIZE +TILE_SIZE/2);
	float secound_y = (y*TILE_SIZE +TILE_SIZE/2);
	float third_x = (x*TILE_SIZE +TILE_SIZE/2);
	float third_y = (y*TILE_SIZE +TILE_SIZE/2);
	float fourth_x = (x*TILE_SIZE +TILE_SIZE/2);
	float fourth_y = (y*TILE_SIZE +TILE_SIZE/2);
	int x_1, x_2, x_3;
	int y_1, y_2, y_3;

	x_1 = x;
	x_2 = x;
	x_3 = x;
	y_1 = y;
	y_2 = y;
	y_3 = y;
	if (Rotation == 1)
	{
		secound_x = ((x+1)*TILE_SIZE +TILE_SIZE/2);
		third_x = ((x+2)*TILE_SIZE +TILE_SIZE/2);
		fourth_x = ((x+3)*TILE_SIZE +TILE_SIZE/2);
		x_1 = x+1;
		x_2 = x+2;
		x_3 = x+3;
		if (x_1 > MAP_SIZE -1)
			Range = 0;
		else if (x_2 > MAP_SIZE -1)
			Range = 1;
		else if (x_2 > MAP_SIZE -1)
			Range = 2;
	}
	if (Rotation == 2)
	{
		secound_x = ((x-1)*TILE_SIZE +TILE_SIZE/2);
		third_x = ((x-2)*TILE_SIZE +TILE_SIZE/2);
		fourth_x = ((x-3)*TILE_SIZE +TILE_SIZE/2);
		x_1 = x-1;
		x_2 = x-2;
		x_3 = x-3;
		if (x_1 < 0)
			Range = 0;
		else if (x_2 < 0)
			Range = 1;
		else if (x_2 < 0)
			Range = 2;
	}
	if (Rotation == 3)
	{
		secound_y = ((y+1)*TILE_SIZE +TILE_SIZE/2);
		third_y = ((y+2)*TILE_SIZE +TILE_SIZE/2);
		fourth_y = ((y+3)*TILE_SIZE +TILE_SIZE/2);
		y_1 = y+1;
		y_2 = y+2;
		y_3 = y+3;
		if (y_1 > MAP_SIZE -1)
			Range = 0;
		else if (y_2 > MAP_SIZE -1)
			Range = 1;
		else if (y_2 > MAP_SIZE -1)
			Range = 2;
	}
	if (Rotation == 4)
	{
		secound_y = ((y-1)*TILE_SIZE +TILE_SIZE/2);
		third_y = ((y-2)*TILE_SIZE +TILE_SIZE/2);
		fourth_y = ((y-3)*TILE_SIZE +TILE_SIZE/2);
		y_1 = y-1;
		y_2 = y-2;
		y_3 = y-3;		
		if (y_1 < 0)
			Range = 0;
		else if (y_2 < 0)
			Range = 1;
		else if (y_2 < 0)
			Range = 2;
	}

	if (Player == 1)
		Player_Type = Player_1_Type;
	if (Player == 2)
		Player_Type = Player_2_Type;

	if (Type == 0) //HQ
	{
		if (Player_Type == 1)
			Ship = HQ_1;
		if (Player_Type == 2)
			Ship = HQ_2;
		if (Player_Type == 3)
			Ship = HQ_3;
		if (Player_Type == 4)
			Ship = HQ_4;
	}
	if (Type == 1) //Fighter
	{
		if (Player_Type == 1)
			Ship = Fighter_1;
		if (Player_Type == 2)
			Ship = Fighter_2;
		if (Player_Type == 3)
			Ship = Fighter_3;
		if (Player_Type == 4)
			Ship = Fighter_4;
	}
	if (Type == 2) //Transport
	{
		if (Player_Type == 1)
			Ship = Transport_1;
		if (Player_Type == 2)
			Ship = Transport_2;
		if (Player_Type == 3)
			Ship = Transport_3;
		if (Player_Type == 4)
			Ship = Transport_4;
	}

	if (Rotation == 1)
		Rotate = RADIANS*3.0;
	if (Rotation == 2)
		Rotate = RADIANS*1.0;
	if (Rotation == 3)
		Rotate = RADIANS*0.0;
	if (Rotation == 4)
		Rotate = RADIANS*2.0;

	if (Rotation == 1)
		Ship_Rotate = RADIANS*1.0;
	if (Rotation == 2)
		Ship_Rotate = RADIANS*3.0;
	if (Rotation == 3)
		Ship_Rotate = RADIANS*2.0;
	if (Rotation == 4)
		Ship_Rotate = RADIANS*0.0;


	for (int i = 0; i < (15.0*Range)-7; i++)
	{
		if (Rotation == 1)
			Position_x = ((x-1)*TILE_SIZE +TILE_SIZE/2) + (TILE_SIZE + ((i*TILE_SIZE)/(14.0)));
		if (Rotation == 2)
			Position_x = ((x+1)*TILE_SIZE +TILE_SIZE/2) - (TILE_SIZE + ((i*TILE_SIZE)/(14.0)));
		if (Rotation == 3)
			Position_y = ((y-1)*TILE_SIZE +TILE_SIZE/2) + (TILE_SIZE + ((i*TILE_SIZE)/(14.0)));
		if (Rotation == 4)
			Position_y = ((y+1)*TILE_SIZE +TILE_SIZE/2) - (TILE_SIZE + ((i*TILE_SIZE)/(14.0)));

		//DRAW BLACK ON ANIMATED TILES
		al_draw_scaled_rotated_bitmap(Black, Center, Center, first_x, first_y, Scale, Scale,  0, 0);
		if (Range >= 1)
			al_draw_scaled_rotated_bitmap(Black, Center, Center, secound_x, secound_y, Scale, Scale,  0, 0);
		if (Range >= 2)
			al_draw_scaled_rotated_bitmap(Black, Center, Center, third_x, third_y, Scale, Scale,  0, 0);
		if (Range >= 3)
			al_draw_scaled_rotated_bitmap(Black, Center, Center, fourth_x, fourth_y, Scale, Scale,  0, 0);

		//DRAW SPACE ON ANIMATED TILES

		Draw_Space(Graphical_Data_Matrix[y][x].Space_Data, x, y, Center, Scale, Graphical_Data_Matrix[y][x].Rotate_Data);
		if (Range >= 1)
			Draw_Space(Graphical_Data_Matrix[y_1][x_1].Space_Data, x_1, y_1, Center, Scale, Graphical_Data_Matrix[y_1][x_1].Rotate_Data);
		if (Range >= 2)
			Draw_Space(Graphical_Data_Matrix[y_2][x_2].Space_Data, x_2, y_2, Center, Scale, Graphical_Data_Matrix[y_2][x_2].Rotate_Data);
		if (Range >= 3)
			Draw_Space(Graphical_Data_Matrix[y_3][x_3].Space_Data, x_3, y_3, Center, Scale, Graphical_Data_Matrix[y_3][x_3].Rotate_Data);

		//DRAW MINES AND ASTEROIDS ON ANIMATED TILES
		if (Colision != '.')
		{
			int col_x, col_y;
			if (Range == 1)
				{ col_x = x_1; col_y = y_1; }
			if (Range == 2)
				{ col_x = x_2; col_y = y_2; }
			if (Range == 3)
				{ col_x = x_3; col_y = y_3; }

			if (Colision == 'A')
				Draw_Asteroid(Graphical_Data_Matrix[col_y][col_x].Asteroid_Data, col_x, col_y, Center, Scale, Graphical_Data_Matrix[col_y][col_x].Rotate_Data);
			if (Colision == 'M')
				Draw_Mine(Graphical_Data_Matrix[col_y][col_x].Mine_Data, col_x, col_y, Center, Scale, Graphical_Data_Matrix[col_y][col_x].Rotate_Data);
			if (Colision == 'H')
				Draw_HQ(Player_1_Type, col_x, col_y, Center, Scale, Simple_Ship_Rotate(Other_Rotation));
			if (Colision == 'h')
				Draw_HQ(Player_2_Type, col_x, col_y, Center, Scale, Simple_Ship_Rotate(Other_Rotation));
			if (Colision == 'F')
				Draw_Fighter(Player_1_Type, col_x, col_y, Center, Scale, Simple_Ship_Rotate(Other_Rotation));
			if (Colision == 'f')
				Draw_Fighter(Player_2_Type, col_x, col_y, Center, Scale, Simple_Ship_Rotate(Other_Rotation));
			if (Colision == 'T')
				Draw_Transport(Player_1_Type, col_x, col_y, Center, Scale, Simple_Ship_Rotate(Other_Rotation));
			if (Colision == 't')
				Draw_Transport(Player_2_Type, col_x, col_y, Center, Scale, Simple_Ship_Rotate(Other_Rotation));
			if (Colision == 'W')
				Draw_Workshop(Player_1_Type, col_x, col_y, Center, Scale, Graphical_Data_Matrix[col_y][col_x].Rotate_Data);
			if (Colision == 'w')
				Draw_Workshop(Player_2_Type, col_x, col_y, Center, Scale, Graphical_Data_Matrix[col_y][col_x].Rotate_Data);
		}
		
		//DRAW Laser ON ANIMATED TILES
		if (Player_Type == 1)
			al_draw_scaled_rotated_bitmap(Laser_1, Center, Center, Position_x, Position_y, Scale, Scale, Rotate, 0);
		if (Player_Type == 2)
			al_draw_scaled_rotated_bitmap(Laser_2, Center, Center, Position_x, Position_y, Scale, Scale, Rotate, 0);
		if (Player_Type == 3)
			al_draw_scaled_rotated_bitmap(Laser_3, Center, Center, Position_x, Position_y, Scale, Scale, Rotate, 0);
		if (Player_Type == 4)
			al_draw_scaled_rotated_bitmap(Laser_4, Center, Center, Position_x, Position_y, Scale, Scale, Rotate, 0);

		al_draw_scaled_rotated_bitmap(Ship, Center, Center, first_x, first_y, Scale, Scale, Ship_Rotate, 0);
		al_flip_display();
		al_rest(animation_speed);
	}
}

void Draw_Ship_Move(int x, int y, int Rotation, int Player, int Type, char Colision, int Other_Rotation)
{
	float Scale = TILE_SIZE/IMAGE_SIZE;
	float Center = IMAGE_SIZE/2;
	int Player_Type;
	float Rotate;
	float Position_x = (x*TILE_SIZE +TILE_SIZE/2);
	float Position_y = (y*TILE_SIZE +TILE_SIZE/2);
	int Y = y;
	int X = x;
	int old_x = (x*TILE_SIZE + TILE_SIZE/2);
	int old_y = (y*TILE_SIZE + TILE_SIZE/2);
	int new_x = (x*TILE_SIZE + TILE_SIZE/2);
	int new_y = (y*TILE_SIZE + TILE_SIZE/2);

	if (Rotation == 1)
	{
		old_x = ((x-2)*TILE_SIZE +TILE_SIZE/2) + (TILE_SIZE);
		X = x-1;
	}
	if (Rotation == 2)
	{
		old_x = ((x+2)*TILE_SIZE +TILE_SIZE/2) - (TILE_SIZE);
		X = x+1;
	}
	if (Rotation == 3)
	{
		old_y = ((y-2)*TILE_SIZE +TILE_SIZE/2) + (TILE_SIZE);
		Y = y-1;
	}
	if (Rotation == 4)
	{
		old_y = ((y+2)*TILE_SIZE +TILE_SIZE/2) - (TILE_SIZE);
		Y = y+1;
	}

	if (Player == 1)
		Player_Type = Player_1_Type;
	if (Player == 2)
		Player_Type = Player_2_Type;

	if (Type == 0) //HQ
	{
		if (Player_Type == 1)
			Ship = HQ_1;
		if (Player_Type == 2)
			Ship = HQ_2;
		if (Player_Type == 3)
			Ship = HQ_3;
		if (Player_Type == 4)
			Ship = HQ_4;
	}
	if (Type == 1) //Fighter
	{
		if (Player_Type == 1)
			Ship = Fighter_1;
		if (Player_Type == 2)
			Ship = Fighter_2;
		if (Player_Type == 3)
			Ship = Fighter_3;
		if (Player_Type == 4)
			Ship = Fighter_4;
	}
	if (Type == 2) //Transport
	{
		if (Player_Type == 1)
			Ship = Transport_1;
		if (Player_Type == 2)
			Ship = Transport_2;
		if (Player_Type == 3)
			Ship = Transport_3;
		if (Player_Type == 4)
			Ship = Transport_4;
	}

	if (Rotation == 1)
		Rotate = RADIANS*1.0;
	if (Rotation == 2)
		Rotate = RADIANS*3.0;
	if (Rotation == 3)
		Rotate = RADIANS*2.0;
	if (Rotation == 4)
		Rotate = RADIANS*0.0;


	for (int i = 0; i < 15; i++)
	{
		if (Rotation == 1)
			Position_x = ((x-2)*TILE_SIZE +TILE_SIZE/2) + (TILE_SIZE + ((i*TILE_SIZE)/14.0));
		if (Rotation == 2)
			Position_x = ((x+2)*TILE_SIZE +TILE_SIZE/2) - (TILE_SIZE + ((i*TILE_SIZE)/14.0));
		if (Rotation == 3)
			Position_y = ((y-2)*TILE_SIZE +TILE_SIZE/2) + (TILE_SIZE + ((i*TILE_SIZE)/14.0));
		if (Rotation == 4)
			Position_y = ((y+2)*TILE_SIZE +TILE_SIZE/2) - (TILE_SIZE + ((i*TILE_SIZE)/14.0));

		//DRAW BLACK ON ANIMATED TILES
		al_draw_scaled_rotated_bitmap(Black, Center, Center, old_x, old_y, Scale, Scale,  0, 0);
		al_draw_scaled_rotated_bitmap(Black, Center, Center, new_x, new_y, Scale, Scale,  0, 0);
		//DRAW SPACE ON ANIMATED TILES
		Draw_Space(Graphical_Data_Matrix[y][x].Space_Data, x, y, Center, Scale, Graphical_Data_Matrix[y][x].Rotate_Data);
		Draw_Space(Graphical_Data_Matrix[Y][X].Space_Data, X, Y, Center, Scale, Graphical_Data_Matrix[Y][X].Rotate_Data);
		//DRAW MINES AND ASTEROIDS ON ANIMATED TILES
		if (Colision != '.')
		{
			if (Colision == 'A')
				Draw_Asteroid(Graphical_Data_Matrix[y][x].Asteroid_Data, x, y, Center, Scale, Graphical_Data_Matrix[y][x].Rotate_Data);
			if (Colision == 'M')
				Draw_Mine(Graphical_Data_Matrix[y][x].Mine_Data, x, y, Center, Scale, Graphical_Data_Matrix[y][x].Rotate_Data);
			if (Colision == 'H')
				Draw_HQ(Player_1_Type, x, y, Center, Scale, Simple_Ship_Rotate(Other_Rotation));
			if (Colision == 'h')
				Draw_HQ(Player_2_Type, x, y, Center, Scale, Simple_Ship_Rotate(Other_Rotation));
			if (Colision == 'F')
				Draw_Fighter(Player_1_Type, x, y, Center, Scale, Simple_Ship_Rotate(Other_Rotation));
			if (Colision == 'f')
				Draw_Fighter(Player_2_Type, x, y, Center, Scale, Simple_Ship_Rotate(Other_Rotation));
			if (Colision == 'T')
				Draw_Transport(Player_1_Type, x, y, Center, Scale, Simple_Ship_Rotate(Other_Rotation));
			if (Colision == 't')
				Draw_Transport(Player_2_Type, x, y, Center, Scale, Simple_Ship_Rotate(Other_Rotation));
			if (Colision == 'W')
				Draw_Workshop(Player_1_Type, x, y, Center, Scale, Graphical_Data_Matrix[y][x].Rotate_Data);
			if (Colision == 'w')
				Draw_Workshop(Player_2_Type, x, y, Center, Scale, Graphical_Data_Matrix[y][x].Rotate_Data);
		}

		//DRAW SHIP ON ANIMATED TILES
		al_draw_scaled_rotated_bitmap(Ship, Center, Center, Position_x, Position_y, Scale, Scale, Rotate, 0);
		al_flip_display();
		al_rest(animation_speed);
	}
}

void Draw_Build_Workshop(int x, int y, int Player)
{
	float Scale = TILE_SIZE/IMAGE_SIZE;
	float Center = IMAGE_SIZE/2;
	int Player_Type;
	float Position_x = (x*TILE_SIZE +TILE_SIZE/2);
	float Position_y = (y*TILE_SIZE +TILE_SIZE/2);

	if (Player == 1)
		Player_Type = Player_1_Type;
	if (Player == 2)
		Player_Type = Player_2_Type;

	for (int i = 15; i > 0; i--)
	{
		float Currect_Scale = ((i*Scale)/14.0);
		//DRAW BLACK ON ANIMATED TILES
		al_draw_scaled_rotated_bitmap(Black, Center, Center, Position_x, Position_y, Scale, Scale,  0, 0);
		//DRAW SPACE ON ANIMATED TILES
		Draw_Space(Graphical_Data_Matrix[y][x].Space_Data, x, y, Center, Scale, Graphical_Data_Matrix[y][x].Rotate_Data);

		//DRAW SHIP ON ANIMATED TILES
		Draw_Asteroid(Graphical_Data_Matrix[y][x].Asteroid_Data, x, y, Center, Currect_Scale, Graphical_Data_Matrix[y][x].Rotate_Data);

		al_flip_display();
		al_rest(animation_speed);
	}

	for (int i = 0; i < 15; i++)
	{
		float Currect_Scale = ((i*Scale)/14.0);
		//DRAW BLACK ON ANIMATED TILES
		al_draw_scaled_rotated_bitmap(Black, Center, Center, Position_x, Position_y, Scale, Scale,  0, 0);
		//DRAW SPACE ON ANIMATED TILES
		Draw_Space(Graphical_Data_Matrix[y][x].Space_Data, x, y, Center, Scale, Graphical_Data_Matrix[y][x].Rotate_Data);

		//DRAW SHIP ON ANIMATED TILES
		Draw_Workshop(Player_Type, x, y, Center, Currect_Scale, Graphical_Data_Matrix[y][x].Rotate_Data);

		al_flip_display();
		al_rest(animation_speed);
	}
}

void Destroy_Display()
{
/*
	al_destroy_bitmap(Ship);

	al_destroy_bitmap(Asteroid_1);
	al_destroy_bitmap(Asteroid_2);
	al_destroy_bitmap(Asteroid_3);
	al_destroy_bitmap(Black);
	al_destroy_bitmap(Explosion_1);
	al_destroy_bitmap(Fighter_1);
	al_destroy_bitmap(Fighter_2);
	al_destroy_bitmap(Fighter_3);
	al_destroy_bitmap(Fighter_4);
	al_destroy_bitmap(HQ_1);
	al_destroy_bitmap(HQ_2);
	al_destroy_bitmap(HQ_3);
	al_destroy_bitmap(HQ_4);
	al_destroy_bitmap(Laser_1);
	al_destroy_bitmap(Laser_2);
	al_destroy_bitmap(Laser_3);
	al_destroy_bitmap(Laser_4);
	al_destroy_bitmap(Mine_1);
	al_destroy_bitmap(Mine_2);
	al_destroy_bitmap(Mine_3);
	al_destroy_bitmap(Mine_4);
	al_destroy_bitmap(Stars_1);
	al_destroy_bitmap(Stars_2);
	al_destroy_bitmap(Stars_3);
	al_destroy_bitmap(Stars_4);
	al_destroy_bitmap(Transport_1);
	al_destroy_bitmap(Transport_2);
	al_destroy_bitmap(Transport_3);
	al_destroy_bitmap(Transport_4);
	al_destroy_bitmap(Workshop_1);
	al_destroy_bitmap(Workshop_2);
	al_destroy_bitmap(Workshop_3);
	al_destroy_bitmap(Workshop_4);
*/
	al_destroy_display(display);

}
