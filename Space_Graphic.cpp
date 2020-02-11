#include <stdio.h>
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "Space_Graphic.h"

#define PI 3.141592653589793238462643383279502884197169
#define TILE_SIZE 64
#define IMAGE_SIZE 16

int Ship_Rotate(std::vector<Ship_Class> Ships, int y, int x);

int seed;

ALLEGRO_DISPLAY *display = NULL;

ALLEGRO_BITMAP *Space_Background_1 = NULL;
ALLEGRO_BITMAP *Space_Background_2 = NULL;
ALLEGRO_BITMAP *Space_Galayx_1 = NULL;
ALLEGRO_BITMAP *Space_Galayx_2 = NULL;
ALLEGRO_BITMAP *Space_Galayx_3 = NULL;
ALLEGRO_BITMAP *Asteroid_1 = NULL;
ALLEGRO_BITMAP *Asteroid_2 = NULL;
ALLEGRO_BITMAP *Asteroid_3 = NULL;
ALLEGRO_BITMAP *Mine_1 = NULL;
ALLEGRO_BITMAP *Mine_2 = NULL;
ALLEGRO_BITMAP *Mine_3 = NULL;
ALLEGRO_BITMAP *HQ_1 = NULL;
ALLEGRO_BITMAP *HQ_2 = NULL;
ALLEGRO_BITMAP *Transport_1 = NULL;
ALLEGRO_BITMAP *Transport_2 = NULL;
ALLEGRO_BITMAP *Fighter_1 = NULL;
ALLEGRO_BITMAP *Fighter_2 = NULL;
ALLEGRO_BITMAP *Workshop_1 = NULL;
ALLEGRO_BITMAP *Workshop_2 = NULL;
ALLEGRO_BITMAP *Laser = NULL;
ALLEGRO_BITMAP *Boom = NULL;

void Create_Display(int MAP_SIZE)
{
	seed = time(NULL);

	al_init();
	al_init_image_addon();
	display = al_create_display(MAP_SIZE*TILE_SIZE, MAP_SIZE*TILE_SIZE);

	Space_Background_1 = al_load_bitmap("Images/Space_Background_1.jpg");
	Space_Background_2 = al_load_bitmap("Images/Space_Background_2.jpg");
	Space_Galaxy_1 = al_load_bitmap("Images/Space_Galaxy_1");
	Space_Galaxy_2 = al_load_bitmap("Images/Space_Galaxy_2");
	Space_Galaxy_3 = al_load_bitmap("Images/Space_Galaxy_3");
	Asteroid_1 = al_load_bitmap("Images/Asteroid_1.png");
	Asteroid_2 = al_load_bitmap("Images/Asteroid_2.png");
	Asteroid_3 = al_load_bitmap("Images/Asteroid_3.png");
	Mine_1 = al_load_bitmap("Images/Mine_1.png");
	Mine_2 = al_load_bitmap("Images/Mine_2.png");
	Mine_3 = al_load_bitmap("Images/Mine_3.png");
	HQ_1 = al_load_bitmap("Images/HQ_1.png");
	HQ_2 = al_load_bitmap("Images/HQ_2.png");
	Transport_1 = al_load_bitmap("Images/Transport_1.png");
	Transport_2 = al_load_bitmap("Images/Transport_2.png");
	Fighter_1 = al_load_bitmap("Images/Fighter_1.png");
	Fighter_2 = al_load_bitmap("Images/Fighter_2.png");
	Workshop_1 = al_load_bitmap("Images/Workshop_1.png");
	Workshop_2 = al_load_bitmap("Images/Workshop_2.png");
	Laser = al_load_bitmap("Images/Laser.png");
	Boom = al_load_bitmap("Images/Boom.png");
}

void Draw_Bitmap(std::vector<std::vector<char> > MAP, std::vector<Ship_Class> Ships)
{
	int MAP_SIZE = MAP[0].size();
	srand(seed);
	
	for(int j = 0; j < MAP.size(); j++)
	{
		for(int i = 0; i < MAP.size(); i++)
		{
			int rotate = (PI/2) * (rand()%4);
			int Space_Type = rand()%6 +1;
			int Mine_Type = rand()%3 +1;
			int Asteroid_Type = rand()%3 +1;
			switch (MAP[j][i])
			{
				case '.':
					if (Space_Type == 1)
					{
						al_draw_scaled_rotated_bitmap(Space_1, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					}
					if (Space_Type == 2)
					{
						al_draw_scaled_rotated_bitmap(Space_2, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					}
					if (Space_Type == 3)
					{
						al_draw_scaled_rotated_bitmap(Space_3, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					}
					if (Space_Type == 4)
					{
						al_draw_scaled_rotated_bitmap(Space_4, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					}
					if (Space_Type == 5)
					{
						al_draw_scaled_rotated_bitmap(Space_5, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					}
					if (Space_Type == 6)
					{
						al_draw_scaled_rotated_bitmap(Space_6, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					}
					break;
				case 'A':
					if (Asteroid_Type == 1)
					{
						al_draw_scaled_rotated_bitmap(Asteroid_1, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					}
					if (Asteroid_Type == 2)
					{
						al_draw_scaled_rotated_bitmap(Asteroid_2, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					}
					if (Asteroid_Type == 3)
					{
						al_draw_scaled_rotated_bitmap(Asteroid_3, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					}
					break;
				case 'M':
					if (Mine_Type == 1)
					{
						al_draw_scaled_rotated_bitmap(Mine_1, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					}
					if (Mine_Type == 2)
					{
						al_draw_scaled_rotated_bitmap(Mine_2, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					}
					if (Mine_Type == 3)
					{
						al_draw_scaled_rotated_bitmap(Mine_3, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					}
					break;
				case 'W':
					al_draw_scaled_rotated_bitmap(Workshop_1, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					break;
				case 'w':
					al_draw_scaled_rotated_bitmap(Workshop_2, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					break;
				case 'H':
					al_draw_scaled_rotated_bitmap(HQ_1, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					break;
				case 'h':
					al_draw_scaled_rotated_bitmap(HQ_2, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  rotate, 0);
					break;
				case 'F':
					al_draw_scaled_rotated_bitmap(Fighter_1, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  Ship_Rotate(Ships, i, j), 0);
					break;
				case 'f':
					al_draw_scaled_rotated_bitmap(Fighter_2, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  Ship_Rotate(Ships, i, j), 0);
					break;
				case 'T':
					al_draw_scaled_rotated_bitmap(Transport_1, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  Ship_Rotate(Ships, i, j), 0);
					break;
				case 't':
					al_draw_scaled_rotated_bitmap(Transport_2, IMAGE_SIZE/2, IMAGE_SIZE/2, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, TILE_SIZE/IMAGE_SIZE, TILE_SIZE/IMAGE_SIZE,  Ship_Rotate(Ships, i, j), 0);
					break;
			}
		}
	}
	al_flip_display();
	//al_rest(1);
}

void Destroy_Display()
{
	al_destroy_display(display);
	al_destroy_bitmap(Space_1);
}

int Ship_Rotate(std::vector<Ship_Class> Ships, int x, int y)
{
	int res = 1;
	for (int i = 0; i < Ships.size(); i++)
	{
		if (Ships[i].x == x && Ships[i].y == y)
		{
			res = Ships[i].Rotation;
			break;
		}
	}
	return (PI/2)*res +2;
}