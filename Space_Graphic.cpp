#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Space_Graphic.h"

#define PI 3.141592653589793238462643383279502884197169
#define RADIANS 1.57079633 // 90 degrees
#define TILE_SIZE 800.0/MAP_SIZE
#define IMAGE_SIZE 330.0
#define FONT_SIZE 180/MAP_SIZE

float animation_speed = 0.05;
int Display_IDs = 0;
int Display_HPs = 0;
int Display_STs = 0;
int Player_1_Type = 0;
int	Player_2_Type = 0;
int seed;
int Title_Screen = 1;
extern int MAP_SIZE;

float Ship_Rotate(std::vector<Ship_Class> Ships, int y, int x);


std::vector<std::vector< Graphical_Data_type>> Graphical_Data_Matrix;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_MOUSE_STATE mouse_state;
std::thread thread_Mouse;

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
ALLEGRO_BITMAP *Dig_1 = NULL;
ALLEGRO_BITMAP *Dig_2 = NULL;
ALLEGRO_BITMAP *Dig_3 = NULL;
ALLEGRO_BITMAP *Dig_4 = NULL;
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
ALLEGRO_FONT *title_font = NULL;
ALLEGRO_FONT *Winner_font = NULL;

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
	al_install_mouse();
	al_install_keyboard();
	display = al_create_display(MAP_SIZE*TILE_SIZE+TILE_SIZE*5, MAP_SIZE*TILE_SIZE);


  font = al_load_ttf_font("Fonts/Credit Valley.ttf", FONT_SIZE, 0 );
	title_font = al_load_ttf_font("Fonts/Credit Valley.ttf", MAP_SIZE*5, 0 );
	Winner_font = al_load_ttf_font("Fonts/Credit Valley.ttf", MAP_SIZE*5, 0 );


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
	Dig_1 = al_load_bitmap("Images/Dig_1.png");
	Dig_2 = al_load_bitmap("Images/Dig_2.png");
	Dig_3 = al_load_bitmap("Images/Dig_3.png");
	Dig_4 = al_load_bitmap("Images/Dig_4.png");
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

	thread_Mouse = std::thread(Mouse_functions);
}

void TITLE_SCREEN()
{
	float Scale = TILE_SIZE/IMAGE_SIZE;
	float Center = IMAGE_SIZE/2;

	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_scaled_rotated_bitmap(Mine_4, Center, Center, (MAP_SIZE*TILE_SIZE+TILE_SIZE*5)/2,(MAP_SIZE*TILE_SIZE)/2+FONT_SIZE*5, Scale, Scale, rand(), 0);
	al_draw_text(title_font, al_map_rgb(255,255,255), (MAP_SIZE*TILE_SIZE+TILE_SIZE*5)/2, (MAP_SIZE*TILE_SIZE)/2, ALLEGRO_ALIGN_CENTRE, "SPACE WARS");
	al_draw_text(font, al_map_rgb(255,255,255), (MAP_SIZE*TILE_SIZE+TILE_SIZE*5)/2, (MAP_SIZE*TILE_SIZE)/2+FONT_SIZE*5, ALLEGRO_ALIGN_CENTRE, "START");
	al_flip_display();
	while(Title_Screen)
	{

	}
}

void Mouse_functions()
{
	extern int MAP_seed;
	extern int MAP_SIZE;
	extern int Player_Alg[];
	extern int game_end;

	int LMB_clicked = 0;
	int LMB_clicked_old = 0;
	int Mouse_position_x;
	int Mouse_position_y;
	
	while (Title_Screen)
	{
		al_get_mouse_state(&mouse_state);

		if (mouse_state.buttons & 1)
			LMB_clicked = 1;
		else
			LMB_clicked = 0;
		al_rest(0.01);

		if (LMB_clicked == 1 && LMB_clicked_old == 0)
		{
			Mouse_position_x = mouse_state.x;
			Mouse_position_y = mouse_state.y;
			if ( Mouse_position_x > (MAP_SIZE*TILE_SIZE+TILE_SIZE*5)/2 - FONT_SIZE*2 && Mouse_position_x < (MAP_SIZE*TILE_SIZE+TILE_SIZE*5)/2 + FONT_SIZE*2 && Mouse_position_y > (MAP_SIZE*TILE_SIZE)/2 && Mouse_position_y < (MAP_SIZE*TILE_SIZE)/2+FONT_SIZE*5)
				Title_Screen = 0;

			
		}
		LMB_clicked_old = LMB_clicked;
	}

	while(game_end > 0)
	{
		al_get_mouse_state(&mouse_state);

		if (mouse_state.buttons & 1)
			LMB_clicked = 1;
		else
			LMB_clicked = 0;
		al_rest(0.01);

		if (LMB_clicked == 1 && LMB_clicked_old == 0)
		{
			Mouse_position_x = mouse_state.x;
			Mouse_position_y = mouse_state.y;
			if ( Mouse_position_x > (MAP_SIZE+1)*TILE_SIZE && Mouse_position_x < (MAP_SIZE+2)*TILE_SIZE && Mouse_position_y > TILE_SIZE && Mouse_position_y < 2*TILE_SIZE)
			{
				if (Display_IDs == 1)
					Display_IDs = 0;
				else //if (Display_IDs == 0)
					Display_IDs = 1;
			}
			if ( Mouse_position_x > (MAP_SIZE+2)*TILE_SIZE && Mouse_position_x <(MAP_SIZE+3)*TILE_SIZE && Mouse_position_y > TILE_SIZE && Mouse_position_y < 2*TILE_SIZE)
			{
				if (Display_HPs == 1)
					Display_HPs = 0;
				else //if (Display_HPs == 0)
					Display_HPs = 1;
			}
			if ( Mouse_position_x > (MAP_SIZE+3)*TILE_SIZE && Mouse_position_x < (MAP_SIZE+4)*TILE_SIZE && Mouse_position_y > TILE_SIZE && Mouse_position_y < 2*TILE_SIZE)
			{
				if (Display_STs == 1)
					Display_STs = 0;
				else //if (Display_STs == 0)
					Display_STs = 1;
			}

			if ( Mouse_position_x > (MAP_SIZE)*TILE_SIZE && Mouse_position_x < (MAP_SIZE+1)*TILE_SIZE && Mouse_position_y > TILE_SIZE*3 && Mouse_position_y < 4*TILE_SIZE)
			{
				animation_speed = 0.1000;
			}
			if ( Mouse_position_x > (MAP_SIZE+1)*TILE_SIZE && Mouse_position_x < (MAP_SIZE+2)*TILE_SIZE && Mouse_position_y > TILE_SIZE*3 && Mouse_position_y < 4*TILE_SIZE)
			{
				animation_speed = 0.0500;
			}
			if ( Mouse_position_x > (MAP_SIZE+2)*TILE_SIZE && Mouse_position_x < (MAP_SIZE+3)*TILE_SIZE && Mouse_position_y > TILE_SIZE*3 && Mouse_position_y < 4*TILE_SIZE)
			{
				animation_speed = 0.0250;
			}
			if ( Mouse_position_x > (MAP_SIZE+3)*TILE_SIZE && Mouse_position_x < (MAP_SIZE+4)*TILE_SIZE && Mouse_position_y > TILE_SIZE*3 && Mouse_position_y < 4*TILE_SIZE)
			{
				animation_speed = 0.0125;
			}
			if ( Mouse_position_x > (MAP_SIZE+4)*TILE_SIZE && Mouse_position_x < (MAP_SIZE+5)*TILE_SIZE && Mouse_position_y > TILE_SIZE*3 && Mouse_position_y < 4*TILE_SIZE)
			{
				animation_speed = 0.0000;
			}

			if ( Mouse_position_x > (MAP_SIZE+4)*TILE_SIZE && Mouse_position_x < (MAP_SIZE+5)*TILE_SIZE && Mouse_position_y > TILE_SIZE*(MAP_SIZE-1) && Mouse_position_y < TILE_SIZE*MAP_SIZE)
			{
				game_end = 0;
			}
		}
		LMB_clicked_old = LMB_clicked;
	}
}

void Display_Stats(std::vector<Mine_Class> Mines, std::vector<Asteroid_Class> Asteroids, std::vector<Ship_Class> Ships)
{
	float Scale = TILE_SIZE/IMAGE_SIZE;
	float Center = IMAGE_SIZE/2;

	if (Display_IDs || Display_HPs)
		for (int i = 0; i < Mines.size(); i++)
		{
			std::string Mine_ID, Mine_HP;
			int M_x = Mines[i].x;
			int M_y = Mines[i].y;
			std::string M_ID = std::to_string(Mines[i].ID);
			std::string M_HP = std::to_string(Mines[i].HP);

			Mine_ID = "ID " + M_ID;
			Mine_HP = "HP " + M_HP;
			char ID[Mine_ID.size()];
			char HP[Mine_HP.size()];

			memset(ID, ' ', Mine_ID.size());
			memset(HP, ' ', Mine_HP.size());

			for (int j = 0; j < sizeof(Mine_ID); j++)
		  	ID[j] = Mine_ID[j];
			for (int j = 0; j < sizeof(Mine_HP); j++)
				HP[j] = Mine_HP[j];

			int position = 0;

			if (Display_IDs)
				al_draw_text(font, al_map_rgb(255,255,255), M_x*TILE_SIZE+TILE_SIZE/2, (++position)*FONT_SIZE+M_y*TILE_SIZE, ALLEGRO_ALIGN_CENTRE, ID);
			if (Display_HPs)
				al_draw_text(font, al_map_rgb(255,255,255), M_x*TILE_SIZE+TILE_SIZE/2, (++position)*FONT_SIZE+M_y*TILE_SIZE, ALLEGRO_ALIGN_CENTRE, HP);
		}

	if (Display_IDs || Display_HPs)
		for (int i = 0; i < Asteroids.size(); i++)
		{
			ALLEGRO_COLOR color = al_map_rgb(255,255,255);
			std::string Asteroid_ID, Asteroid_HP;
			int A_x = Asteroids[i].x;
			int A_y = Asteroids[i].y;
			std::string A_ID = std::to_string(Asteroids[i].ID);
			std::string A_HP = std::to_string(Asteroids[i].HP);

			if (Asteroids[i].Workshop == 1)
				color = al_map_rgb(0,255,0);
			if (Asteroids[i].Workshop == 2)
				color = al_map_rgb(255,0,0);

			Asteroid_ID = "ID " + A_ID;
			Asteroid_HP = "HP " + A_HP;
			char ID[Asteroid_ID.size()];
			char HP[Asteroid_HP.size()];

			memset(ID, ' ', Asteroid_ID.size());
			memset(HP, ' ', Asteroid_HP.size());

			for (int j = 0; j < sizeof(Asteroid_ID); j++)
		  	ID[j] = Asteroid_ID[j];
			for (int j = 0; j < sizeof(Asteroid_HP); j++)
				HP[j] = Asteroid_HP[j];

			int position = 0;

			if (Display_IDs)
				al_draw_text(font, color, A_x*TILE_SIZE+TILE_SIZE/2, (++position)*FONT_SIZE+A_y*TILE_SIZE, ALLEGRO_ALIGN_CENTRE, ID);
			if (Display_HPs)
				al_draw_text(font, color, A_x*TILE_SIZE+TILE_SIZE/2, (++position)*FONT_SIZE+A_y*TILE_SIZE, ALLEGRO_ALIGN_CENTRE, HP);
		}

	if (Display_IDs || Display_HPs || Display_STs)
		for (int i = 0; i < Ships.size(); i++)
		{
			ALLEGRO_COLOR color = al_map_rgb(255,255,255);
			std::string Ship_ID, Ship_HP, Ship_ST;
			int S_x = Ships[i].x;
			int S_y = Ships[i].y;
			std::string S_ID = std::to_string(Ships[i].ID);
			std::string S_HP = std::to_string(Ships[i].HP);
			std::string S_ST = std::to_string(Ships[i].Storage);

			if (Ships[i].Player == 1)
				color = al_map_rgb(0,255,0);
			if (Ships[i].Player == 2)
				color = al_map_rgb(255,0,0);

			Ship_ID = "ID " + S_ID;
			Ship_HP = "HP " + S_HP;
			Ship_ST = "ST " + S_ST;
			char ID[Ship_ID.size()];
			char HP[Ship_HP.size()];
			char ST[Ship_ST.size()];

			memset(ID, ' ', Ship_ID.size());
			memset(HP, ' ', Ship_HP.size());
			memset(ST, ' ', Ship_ST.size());

			for (int j = 0; j < sizeof(Ship_ID); j++)
		  	ID[j] = Ship_ID[j];
			for (int j = 0; j < sizeof(Ship_HP); j++)
				HP[j] = Ship_HP[j];
			for (int j = 0; j < sizeof(Ship_ST); j++)
				ST[j] = Ship_ST[j];

			int position = 0;

			if (Display_IDs)
				al_draw_text(font, color, S_x*TILE_SIZE+TILE_SIZE/2, (++position)*FONT_SIZE+S_y*TILE_SIZE, ALLEGRO_ALIGN_CENTRE, ID);
			if (Display_HPs)
				al_draw_text(font, color, S_x*TILE_SIZE+TILE_SIZE/2, (++position)*FONT_SIZE+S_y*TILE_SIZE, ALLEGRO_ALIGN_CENTRE, HP);
			if (Display_STs)
				al_draw_text(font, color, S_x*TILE_SIZE+TILE_SIZE/2, (++position)*FONT_SIZE+S_y*TILE_SIZE, ALLEGRO_ALIGN_CENTRE, ST);
		}
}

void Display_Winner(int Player)
{
	al_clear_to_color(al_map_rgb(0,0,0));
	srand(seed);
	float Scale = TILE_SIZE/IMAGE_SIZE;
	float Center = IMAGE_SIZE/2;
	char Winner[20] = "WINNER IS PLAYER: ";
	char WIN;
	if (Player == 1)
		Winner[18] = '1';
	else
		Winner[18] = '2';

	if (Player == 1)
		al_draw_text(Winner_font, al_map_rgb(0,255,0), (MAP_SIZE*TILE_SIZE+TILE_SIZE*5)/2, MAP_SIZE*TILE_SIZE/2, ALLEGRO_ALIGN_CENTRE, Winner);
	if (Player == 2)
		al_draw_text(Winner_font, al_map_rgb(255,0,0), (MAP_SIZE*TILE_SIZE+TILE_SIZE*5)/2, MAP_SIZE*TILE_SIZE/2, ALLEGRO_ALIGN_CENTRE, Winner);
	al_flip_display();
	al_rest(animation_speed*100);
}

void Draw_Whole_MAP(std::vector<std::vector<char> > MAP, std::vector<Mine_Class> Mines, std::vector<Asteroid_Class> Asteroids, std::vector<Ship_Class> Ships)
{
	srand(seed);
	float Scale = TILE_SIZE/IMAGE_SIZE;
	float Center = IMAGE_SIZE/2;

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
	if (Display_IDs || Display_HPs || Display_STs)
		Display_Stats(Mines, Asteroids, Ships);

	al_draw_scaled_rotated_bitmap(Mine_1, Center, Center, (MAP_SIZE+1)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE + TILE_SIZE/2, Scale, Scale, rand(), 0);
	al_draw_text(font, al_map_rgb(255,255,255), (MAP_SIZE+1)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE + TILE_SIZE/2, ALLEGRO_ALIGN_CENTRE, "ID");

	al_draw_scaled_rotated_bitmap(Mine_2, Center, Center, (MAP_SIZE+2)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE + TILE_SIZE/2, Scale, Scale, rand(), 0);
	al_draw_text(font, al_map_rgb(255,255,255), (MAP_SIZE+2)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE + TILE_SIZE/2, ALLEGRO_ALIGN_CENTRE, "HP");

	al_draw_scaled_rotated_bitmap(Mine_3, Center, Center, (MAP_SIZE+3)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE + TILE_SIZE/2, Scale, Scale, rand(), 0);
	al_draw_text(font, al_map_rgb(255,255,255), (MAP_SIZE+3)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE + TILE_SIZE/2, ALLEGRO_ALIGN_CENTRE, "ST");

	al_draw_scaled_rotated_bitmap(Mine_4, Center, Center, (MAP_SIZE)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE*3 + TILE_SIZE/2, Scale, Scale, rand(), 0);
	al_draw_text(font, al_map_rgb(255,255,255), (MAP_SIZE)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE*3 + TILE_SIZE/2, ALLEGRO_ALIGN_CENTRE, "Speed x0.5");

	al_draw_scaled_rotated_bitmap(Mine_1, Center, Center, (MAP_SIZE+1)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE*3 + TILE_SIZE/2, Scale, Scale, rand(), 0);
	al_draw_text(font, al_map_rgb(255,255,255), (MAP_SIZE+1)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE*3 + TILE_SIZE/2, ALLEGRO_ALIGN_CENTRE, "Speed x1");

	al_draw_scaled_rotated_bitmap(Mine_2, Center, Center, (MAP_SIZE+2)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE*3 + TILE_SIZE/2, Scale, Scale, rand(), 0);
	al_draw_text(font, al_map_rgb(255,255,255), (MAP_SIZE+2)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE*3 + TILE_SIZE/2, ALLEGRO_ALIGN_CENTRE, "Speed x2");

	al_draw_scaled_rotated_bitmap(Mine_3, Center, Center, (MAP_SIZE+3)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE*3 + TILE_SIZE/2, Scale, Scale, rand(), 0);
	al_draw_text(font, al_map_rgb(255,255,255), (MAP_SIZE+3)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE*3 + TILE_SIZE/2, ALLEGRO_ALIGN_CENTRE, "Speed x4");

	al_draw_scaled_rotated_bitmap(Mine_4, Center, Center, (MAP_SIZE+4)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE*3 + TILE_SIZE/2, Scale, Scale, rand(), 0);
	al_draw_text(font, al_map_rgb(255,255,255), (MAP_SIZE+4)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE*3 + TILE_SIZE/2, ALLEGRO_ALIGN_CENTRE, "Speed MAX");

	al_draw_scaled_rotated_bitmap(Mine_4, Center, Center, (MAP_SIZE+4)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE*(MAP_SIZE-1) + TILE_SIZE/2, Scale, Scale, rand(), 0);
	al_draw_text(font, al_map_rgb(255,255,255), (MAP_SIZE+4)*TILE_SIZE + TILE_SIZE/2, TILE_SIZE*(MAP_SIZE-1) + TILE_SIZE/2, ALLEGRO_ALIGN_CENTRE, "Exit");

	al_flip_display();
	al_rest(animation_speed);
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

void Draw_Dig(int x, int y, int Rotation, int Player, int Type, char Mine)
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
	int x_1;
	int y_1;
	int Range = 1;

	x_1 = x;
	y_1 = y;

	if (Rotation == 1)
	{
		secound_x = ((x+1)*TILE_SIZE +TILE_SIZE/2);
		x_1 = x+1;
		if (x_1 > MAP_SIZE -1)
			Range = 0;
	}
	if (Rotation == 2)
	{
		secound_x = ((x-1)*TILE_SIZE +TILE_SIZE/2);
		x_1 = x-1;
		if (x_1 < 0)
			Range = 0;;
	}
	if (Rotation == 3)
	{
		secound_y = ((y+1)*TILE_SIZE +TILE_SIZE/2);
		y_1 = y+1;
		if (y_1 > MAP_SIZE -1)
			Range = 0;
	}
	if (Rotation == 4)
	{
		secound_y = ((y-1)*TILE_SIZE +TILE_SIZE/2);
		y_1 = y-1;	
		if (y_1 < 0)
			Range = 0;
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

	for (int i = (15.0*Range); i > 0; i--)
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

		//DRAW SPACE ON ANIMATED TILES

		Draw_Space(Graphical_Data_Matrix[y][x].Space_Data, x, y, Center, Scale, Graphical_Data_Matrix[y][x].Rotate_Data);
		if (Range >= 1)
			Draw_Space(Graphical_Data_Matrix[y_1][x_1].Space_Data, x_1, y_1, Center, Scale, Graphical_Data_Matrix[y_1][x_1].Rotate_Data);

		//DRAW MINES AND ASTEROIDS ON ANIMATED TILES
		if (Mine != '.')
		{
			Draw_Mine(Graphical_Data_Matrix[y_1][x_1].Mine_Data, x_1, y_1, Center, Scale, Graphical_Data_Matrix[y_1][x_1].Rotate_Data);
		}
		
		//DRAW Laser ON ANIMATED TILES
		if (Player_Type == 1)
			al_draw_scaled_rotated_bitmap(Dig_1, Center, Center, Position_x, Position_y, Scale, Scale, Rotate, 0);
		if (Player_Type == 2)
			al_draw_scaled_rotated_bitmap(Dig_2, Center, Center, Position_x, Position_y, Scale, Scale, Rotate, 0);
		if (Player_Type == 3)
			al_draw_scaled_rotated_bitmap(Dig_3, Center, Center, Position_x, Position_y, Scale, Scale, Rotate, 0);
		if (Player_Type == 4)
			al_draw_scaled_rotated_bitmap(Dig_4, Center, Center, Position_x, Position_y, Scale, Scale, Rotate, 0);

		al_draw_scaled_rotated_bitmap(Ship, Center, Center, first_x, first_y, Scale, Scale, Ship_Rotate, 0);
		al_flip_display();
		al_rest(animation_speed);
	}
		al_draw_scaled_rotated_bitmap(Black, Center, Center, first_x, first_y, Scale, Scale,  0, 0);
		if (Range >= 1)
			al_draw_scaled_rotated_bitmap(Black, Center, Center, secound_x, secound_y, Scale, Scale,  0, 0);

		//DRAW SPACE ON ANIMATED TILES

		Draw_Space(Graphical_Data_Matrix[y][x].Space_Data, x, y, Center, Scale, Graphical_Data_Matrix[y][x].Rotate_Data);
		if (Range >= 1)
			Draw_Space(Graphical_Data_Matrix[y_1][x_1].Space_Data, x_1, y_1, Center, Scale, Graphical_Data_Matrix[y_1][x_1].Rotate_Data);

		//DRAW MINES AND ASTEROIDS ON ANIMATED TILES
		if (Mine != '.')
		{
			Draw_Mine(Graphical_Data_Matrix[y_1][x_1].Mine_Data, x_1, y_1, Center, Scale, Graphical_Data_Matrix[y_1][x_1].Rotate_Data);
		}
		al_draw_scaled_rotated_bitmap(Ship, Center, Center, first_x, first_y, Scale, Scale, Ship_Rotate, 0);
		al_flip_display();
		al_rest(animation_speed);
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
