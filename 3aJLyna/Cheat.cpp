#include "Functions.h"

bool Cheat::Cheat_on(vector<vector<char>>& obj, int size, int &hp_enemy)
{
	for (int i = 0; i < size;i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (obj[i][j] == static_cast<char>(254))
				obj[i][j] = 'x';
		}
	}
	hp_enemy = 0;
	return false;
}