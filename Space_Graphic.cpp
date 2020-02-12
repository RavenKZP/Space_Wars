#include <stdio.h>
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "Space_Graphic.h"

#define PI 3.141592653589793238462643383279502884197169
#define RADIANS 1.57079633 // 90 degrees
#define TILE_SIZE 64
#define IMAGE_SIZE 330

float Ship_Rotate(std::vector<Ship_Class> Ships, int y, int x);

int seed;

ALLEGRO_DISPLAY *display = NULL;

ALLEGRO_BITMAP *Asteroid_1 = NULL;
ALLEGRO_BITMAP *Asteroid_2 = NULL;
ALLEGRO_BITMAP *Asteroid_3 = NULL;
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

void Create_Display(int MAP_SIZE)
{
	seed = time(NULL);

	al_init();
	al_init_image_addon();
	display = al_create_display(MAP_SIZE*TILE_SIZE, MAP_SIZE*TILE_SIZE);


	Asteroid_1 = al_load_bitmap("Images/Asteroid_1.png");
	Asteroid_2 = al_load_bitmap("Images/Asteroid_2.png");
	Asteroid_3 = al_load_bitmap("Images/Asteroid_3.png");
	Explosion_1 = al_load_bitmap("Images/Explosion_1.png");
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

void Draw_Bitmap(std::vector<std::vector<char> > MAP, std::vector<Ship_Class> Ships)
{
	float Scale = 0.2;
	float Center = IMAGE_SIZE/2;
	int MAP_SIZE = MAP[0].size();
	srand(seed);
	al_clear_to_color(al_map_rgb(0,0,0));
	for(int j = 0; j < MAP.size(); j++)
	{
		for(int i = 0; i < MAP.size(); i++)
		{
			int rotate = rand();
			int Space_Type = rand()%4 +1;
			int Mine_Type = rand()%4 +1;
			int Asteroid_Type = rand()%3 +1;
			if (Space_Type == 1 && i%2 == 0 && j%2 == 0)
			{
				al_draw_scaled_rotated_bitmap(Stars_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale*2, Scale*2,  rotate, 0);
			}
			if (Space_Type == 2 && i%2 == 0 && j%2 == 0)
			{
				al_draw_scaled_rotated_bitmap(Stars_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale*2, Scale*2,  rotate, 0);
			}
			if (Space_Type == 3 && i%2 == 0 && j%2 == 0)
			{
				al_draw_scaled_rotated_bitmap(Stars_3, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale*2, Scale*2,  rotate, 0);
			}
			if (Space_Type == 4 && i%2 == 0 && j%2 == 0)
			{
				al_draw_scaled_rotated_bitmap(Stars_4, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale*2, Scale*2,  rotate, 0);
			}
			switch (MAP[j][i])
			{
				case 'A':
					if (Asteroid_Type == 1)
					{
						al_draw_scaled_rotated_bitmap(Asteroid_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  rotate, 0);
					}
					if (Asteroid_Type == 2)
					{
						al_draw_scaled_rotated_bitmap(Asteroid_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  rotate, 0);
					}
					if (Asteroid_Type == 3)
					{
						al_draw_scaled_rotated_bitmap(Asteroid_3, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  rotate, 0);
					}
					break;
				case 'M':
					if (Mine_Type == 1)
					{
						al_draw_scaled_rotated_bitmap(Mine_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  rotate, 0);
					}
					if (Mine_Type == 2)
					{
						al_draw_scaled_rotated_bitmap(Mine_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  rotate, 0);
					}
					if (Mine_Type == 3)
					{
						al_draw_scaled_rotated_bitmap(Mine_3, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  rotate, 0);
					}
					if (Mine_Type == 4)
					{
						al_draw_scaled_rotated_bitmap(Mine_4, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  rotate, 0);
					}
					break;
				case 'W':
					al_draw_scaled_rotated_bitmap(Workshop_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  rotate, 0);
					break;
				case 'w':
					al_draw_scaled_rotated_bitmap(Workshop_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  rotate, 0);
					break;
				case 'H':
					al_draw_scaled_rotated_bitmap(HQ_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  rotate, 0);
					break;
				case 'h':
					al_draw_scaled_rotated_bitmap(HQ_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  rotate, 0);
					break;
				case 'F':
					al_draw_scaled_rotated_bitmap(Fighter_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Ship_Rotate(Ships, i, j), 0);
					break;
				case 'f':
					al_draw_scaled_rotated_bitmap(Fighter_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Ship_Rotate(Ships, i, j), 0);
					break;
				case 'T':
					al_draw_scaled_rotated_bitmap(Transport_1, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Ship_Rotate(Ships, i, j), 0);
					break;
				case 't':
					al_draw_scaled_rotated_bitmap(Transport_2, Center, Center, i*TILE_SIZE +TILE_SIZE/2, j*TILE_SIZE +TILE_SIZE/2, Scale, Scale,  Ship_Rotate(Ships, i, j), 0);
					break;
			}
		}
	}
	al_flip_display();
	al_rest(0.2);
}

void Destroy_Display()
{
	al_destroy_display(display);

	al_destroy_bitmap(Asteroid_1);
	al_destroy_bitmap(Asteroid_2);
	al_destroy_bitmap(Asteroid_3);
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
}

float Ship_Rotate(std::vector<Ship_Class> Ships, int x, int y)
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
	return RADIANS*(res+1);
}
