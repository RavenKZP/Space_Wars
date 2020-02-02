#include "Space_Functions.h"

int count_digits(const std::string& s)
{
	int ret_val;
	ret_val = std::count_if(s.begin(), s.end(),[](unsigned char c){ return std::isdigit(c); } );
	//std::cout << ret_val << std::endl;
	if (ret_val > 5)
	{
		ret_val = 0;
	}
	return ret_val;
}

int Build_Near_By(int x, int y, int Player, std::vector<std::vector<char> > MAP)
{
	char HQ;
	char Workshop;
	int ret_val = 0;
	if (Player == 1)
	{
		HQ = 'H';
		Workshop = 'W';
	}
	else
	{
		HQ = 'h';
		Workshop = 'w';
	}
	int size = MAP[0].size() - 1;
	if (x == 0 && y == 0)
	{
		if ( MAP[x+1][y] == HQ || MAP[x+1][y] == Workshop || MAP[x][y+1] == HQ || MAP[x][y+1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (x == 0 && y == size)
	{
		if ( MAP[x+1][y] == HQ || MAP[x+1][y] == Workshop || MAP[x][y-1] == HQ || MAP[x][y-1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (x == size && y == 0)
	{
		if ( MAP[x-1][y] == HQ || MAP[x-1][y] == Workshop || MAP[x][y+1] == HQ || MAP[x][y+1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (x == size && y == size)
	{
		if ( MAP[x-1][y] == HQ || MAP[x-1][y] == Workshop || MAP[x][y-1] == HQ || MAP[x][y-1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (x == 0)
	{
		if ( MAP[x+1][y] == HQ || MAP[x+1][y] == Workshop || MAP[x][y+1] == HQ || MAP[x][y+1] == Workshop || MAP[x][y-1] == HQ || MAP[x][y-1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (x == size)
	{
		if ( MAP[x-1][y] == HQ || MAP[x-1][y] == Workshop || MAP[x][y+1] == HQ || MAP[x][y+1] == Workshop || MAP[x][y-1] == HQ || MAP[x][y-1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (y == 0)
	{
		if ( MAP[x+1][y] == HQ || MAP[x+1][y] == Workshop || MAP[x-1][y] == HQ || MAP[x-1][y] == Workshop || MAP[x][y+1] == HQ || MAP[x][y+1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else if (y == size)
	{
		if ( MAP[x+1][y] == HQ || MAP[x+1][y] == Workshop || MAP[x-1][y] == HQ || MAP[x-1][y] == Workshop || MAP[x][y-1] == HQ || MAP[x][y-1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	else // x > 0 && x < size && y > 0 && y < size
	{
		if ( MAP[x+1][y] == HQ || MAP[x+1][y] == Workshop || MAP[x-1][y] == HQ || MAP[x-1][y] == Workshop || MAP[x][y+1] == HQ || MAP[x][y+1] == Workshop || MAP[x][y-1] == HQ || MAP[x][y-1] == Workshop)
		{
			ret_val = 1; 
		}
	}
	return ret_val;
}
