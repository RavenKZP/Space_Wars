#ifndef SPACE_GRAPHIC_H
#define SPACE_GRAPHIC_H

#include "Return_Types.h"
#include "Space_Classes.h"

void Create_Display(int MAP_SIZE);
void Draw_Bitmap(std::vector<std::vector<char> > MAP, std::vector<Ship_Class> Ships);
void Destroy_Display(void);

#endif

