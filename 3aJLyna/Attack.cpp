#include "Functions.h"

int Attack::Attack_bot(vector<vector<char>>& obj, int size)
{
	int hp_decrease = 0;
	bool attack = true;
	bool dir = true;
	while (attack)
	{
		int X = rand() % size;
		int Y = rand() % size;

		if (obj[Y][X] == static_cast<char>(254))
		{
			obj[Y][X] = 'x';
			hp_decrease++;

			while (dir)
			{
				int rot = rand() % 4;
				if (rot == 0)
				{
					if (Y - 1 >= 0)
					{
						if (obj[Y - 1][X] == static_cast<char>(254))
						{
							obj[Y - 1][X] = 'x';
							hp_decrease++;
							dir = true;
							continue;
						}
						else
						{
							obj[Y - 1][X] = '~';
							dir = false;
							attack = false;
							continue;
						}
					}
					else
						continue;
				}
				else if (rot == 1)
				{
					if (X + 1 < size)
					{
						if (obj[Y][X + 1] == static_cast<char>(254))
						{
							obj[Y][X + 1] = 'x';
							hp_decrease++;
							dir = true;
							continue;
						}
						else
						{
							obj[Y][X + 1] = '~';
							dir = false;
							attack = false;
							continue;
						}
					}
					else
						continue;
				}
				else if (rot == 2)
				{
					if (Y + 1 < size)
					{
						if (obj[Y + 1][X] == static_cast<char>(254))
						{
							obj[Y + 1][X] = 'x';
							hp_decrease++;
							dir = true;
							continue;
						}
						else
						{
							obj[Y + 1][X] = '~';
							dir = false;
							attack = false;
							continue;
						}
					}
					else
						continue;
				}
				else if (rot == 3)
				{
					if (X - 1 >= 0)
					{
						if (obj[Y][X - 1] == static_cast<char>(254))
						{
							obj[Y][X - 1] = 'x';
							hp_decrease++;
							dir = true;
							continue;
						}
						else
						{
							obj[Y][X - 1] = '~';
							dir = false;
							attack = false;
							continue;
						}
					}
					else
						continue;
				}
			}
		}

		else if (obj[Y][X] == 'x' || obj[Y][X] == '~')
			continue;
		else
		{
			attack = false;
			obj[Y][X] = '~';
		}
	}

	return hp_decrease;
}

bool Attack::Attack_player(vector<vector<char>>& dummy, vector<vector<char>>& enemy, int X, int Y, int &hp_enemy)
{
	if (enemy[Y][X] == static_cast<char>(254))
	{
		hp_enemy--;
		dummy[Y][X] = 'x';
		enemy[Y][X] = 'x';
		return true;
	}
	else if (enemy[Y][X] == '~' || enemy[Y][X] == 'x')
	{
		return true;
	}
	else
	{
		enemy[Y][X] = '~';
		dummy[Y][X] = '~';
		return false;
	}
}


