#ifndef SPACE_FUNCTIONS_H
#define SPACE_FUNCTIONS_H

#include <algorithm>
#include "Return_Types.h"
#include "Space_Classes.h"

int count_digits(const std::string& s);
int Build_Near_By(int y, int x, int Player, std::vector<std::vector<char> > MAP);
int Workshop_Near_By(int y, int x, int Player, std::vector<std::vector<char> > MAP);
int COLISION_DETECTOR(int x, int y, std::vector<Mine_Class> Mines, std::vector<Asteroid_Class> Asteroids, std::vector<Ship_Class> Ships, int Ship_ID, char* Obj_Type);  
void Perform_Actions(Output_type Output_Player, std::vector<Mine_Class>& Mines, std::vector<Asteroid_Class>& Asteroids, std::vector<Ship_Class>& Ships, std::vector<std::vector<char> >& MAP, int Player);
void Destroy_Ships(std::vector<Mine_Class>& Mines, std::vector<Asteroid_Class>& Asteroids, std::vector<Ship_Class>& Ships);

#endif

