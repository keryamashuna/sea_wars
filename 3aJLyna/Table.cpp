#include "Functions.h"
#include "Ships.h"

Table::Table(int n)
{
	table.resize(n);
	enemy.resize(n);
	dummy.resize(n);
	for (int i = 0; i < n; i++)
	{
		table[i].resize(n);
		enemy[i].resize(n);
		dummy[i].resize(n);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			table[i][j] = static_cast<char>(249);
			enemy[i][j] = static_cast<char>(249);
			dummy[i][j] = static_cast<char>(249);
		}
	}

	cur.setx(5);
	cur.sety(5);

	ships_player.resize(4);
	ships_player[0] = One_deck();
	ships_player[1] = Two_deck();
	ships_player[2] = Three_deck();
	ships_player[3] = Four_deck();

	ships_bot.resize(4);
	ships_bot[0] = One_deck();
	ships_bot[1] = Two_deck();
	ships_bot[2] = Three_deck();
	ships_bot[3] = Four_deck();

	size = n;
}

void Table::Set_hp()
{
	int count = 0;
	for (int i = 0; i < ships_player.size(); i++)
	{
		count += ships_player[i].get_amount() * ships_player[i].get_size();
	}
	hp_enemy = count;
	hp_player = count;
}




vector<vector<char>>& Table::Get_table()
{
	return table;
}

vector<vector<char>>& Table::Get_enemy()
{
	return enemy;
}

vector<vector<char>>& Table::Get_dummy()
{
	return dummy;
}


void Table::Move_on_table(int which, int action)
{
	bool check = true;
	Print print;
	while (check)
	{
		system("cls");
		if (which == 0)
		{
			print.View_table_cursor(table, size, cur, col);
		}
		else
		{
			print.View_table(table, size);
			cout << "\n";
			print.View_table_cursor(dummy, size, cur, col);
		}
		int code = _getch();
		switch (code)
		{

		case 72:
		{
			if ((cur.gety() - 1) < 0)
			{
				break;
			}
			else
			{
				cur.sety(cur.gety() - 1);
				break;
			}
		}

		case 80:
		{
			if ((cur.gety() + 1) > (size - 1))
			{
				break;
			}
			else
			{
				cur.sety(cur.gety() + 1);
				break;
			}

		}

		case 75:
		{
			if ((cur.getx() - 1) < 0)
			{
				break;
			}
			else
			{
				cur.setx(cur.getx() - 1);
				break;
			}
		}

		case 77:
		{
			if ((cur.getx() + 1) > (size - 1))
			{
				break;
			}
			else
			{
				cur.setx(cur.getx() + 1);
				break;
			}
		}

		case 13:
		{
			if (action == 0)
			{
				cout << "choose a direction>> ";
				int dir;
				cin >> dir;
				check = set.Set_all_ships_player(cur.getx(), cur.gety(), dir, table, ships_player, queue, size);
				break;
			}
			else if (action == 1)
			{
				check = attack.Attack_player(dummy, enemy, cur.getx(), cur.gety(), hp_enemy);
				break;
			}
			break;
		}
		case 119:
		{
			if (action == 1)
			{
				check = chpik.Cheat_on(enemy, size, hp_enemy);
			}
			else
				break;
		}

		}
	}
	if (which == 0)
	{
		system("cls");
		print.View_table(table, size);
	}
}

void Table::Bot_set_ships()
{
	set.Set_all_ships_bot(enemy, ships_bot, queue, size);
	queue = 0;
}

bool Table::Game_process()
{
	system("cls");
	while(true)
	{
		int decrease_by;
		Move_on_table(1, 1);
		decrease_by = attack.Attack_bot(table, size);
		hp_player -= decrease_by;
		if (hp_player == 0)
		{
			return false;
		}
		if (hp_enemy == 0)
		{
			return true;
		}
	}
}

void Set_ships::Set_all_ships_bot(vector<vector<char>>& obj, vector<Ship>&ships, int &queue, int size)
{
	bool check = true;
	while (check)
	{
		int dir = rand() % 2;
		int X = rand() % 10;
		int Y = rand() % 10;
		check = Set_all_ships_player(X, Y, dir, obj, ships, queue, size);
	}
}

bool Set_ships::Set_all_ships_player(int X, int Y, int dir, vector<vector<char>>& obj, vector<Ship>&ships, int &queue, int size)
{
	{
		int decks = ships[queue].get_size();

		switch (dir)
		{
		case 0:
		{
			if (size - X >= decks)
			{
				for (int i = 0; i < decks; i++)
				{
					for (int j = i; j < decks; j++)
					{
						if (!(obj[Y][X + j] == static_cast<char>(249)))
						{
							return true;
						}

						if (X + decks < size)
						{
							if (!(obj[Y][X + decks] == static_cast<char>(249)))
							{
								return true;
							}
						}

						if (X - 1 >= 0)
						{
							if (!(obj[Y][X - 1] == static_cast<char>(249)))
								return true;
							if (Y - 1 >= 0)
							{
								if (!(obj[Y - 1][X - 1] == static_cast<char>(249)))
									return true;
							}

							if (Y + 1 < size)
							{
								if (!(obj[Y + 1][X - 1] == static_cast<char>(249)))
									return true;
							}
						}




						if (X + (j+1) < size && Y - 1 >= 0)
						{
							if(!(obj[Y-1][X+(j+1)]==static_cast<char>(249)))
								return true;
						}

						if (X + (j + 1) < size && Y + 1 < size)
						{
							if (!(obj[Y + 1][X + (j + 1)] == static_cast<char>(249)))
								return true;
						}


						if (Y + 1 < size)
						{
							if (!(obj[Y + 1][X + j] == static_cast<char>(249)))
								return true;
						}

						if (Y - 1 >= 0)
						{
							if (!(obj[Y - 1][X + j] == static_cast<char>(249)))
								return true;
						}
					}
					

					obj[Y][X + i] = static_cast<char>(254);

				}
			}

			else
			{
				for (int i = 0; i < decks; i++)
				{
					for (int j = i; j < decks; j++)
					{
						if (X - (j + 1) >=0 && Y - 1 >= 0)
						{
							if (!(obj[Y - 1][X - (j + 1)] == static_cast<char>(249)))
								return true;
						}

						if (X - (j + 1)>=0 && Y + 1 < size)
						{
							if (!(obj[Y + 1][X - (j + 1)] == static_cast<char>(249)))
								return true;
						}

						if (!(obj[Y][X - j] == static_cast<char>(249)))
							return true;

						if (X - decks >= 0)
						{
							if (!(obj[Y][X - decks] == static_cast<char>(249)))
							{
								return true;
							}
						}

						if (Y + 1 < size)
						{
							if (!(obj[Y + 1][X - j] == static_cast<char>(249)))
								return true;

						}
						if (Y - 1 >= 0)
						{
							if (!(obj[Y - 1][X - j] == static_cast<char>(249)))
								return true;
						}


					}
					obj[Y][X - i] = static_cast<char>(254);
				}
			}
			ships[queue].set_count_plus();
			if (ships[queue].get_amount() == (ships[queue].get_count() - 1))
			{
				queue++;
			}
			break;
		}

		case 1:
		{
			if (size - Y >= decks)
			{
				for (int i = 0; i < decks; i++)
				{
					for (int j = i; j < decks; j++)
					{
						if (!(obj[Y + j][X] == static_cast<char>(249)))
						{
							return true;
						}

						if (Y + (j + 1) < size && X - 1 >= 0)
						{
							if (!(obj[Y + (j+1)][X - 1] == static_cast<char>(249)))
								return true;
						}

						if (Y + (j + 1) < size && X + 1 < size)
						{
							if (!(obj[Y + (j + 1)][X + 1] == static_cast<char>(249)))
								return true;
						}


						if (Y + decks < size)
						{
							if (!(obj[Y + decks][X] == static_cast<char>(249)))
							{
								return true;
							}
						}

						if (X + 1 < size)
						{
							if (!(obj[Y + j][X + 1] == static_cast<char>(249)))
								return true;
						}

						if (X - 1 >= 0)
						{
							if (!(obj[Y + j][X - 1] == static_cast<char>(249)))
								return true;
						}

						if (Y - 1 >= 0)
						{
							if (!(obj[Y - 1][X] == static_cast<char>(249)))
								return true;

							if (X - 1 >= 0)
							{
								if (!(obj[Y - 1][X - 1] == static_cast<char>(249)))
									return true;
							}

							if (X + 1 < size)
							{
								if (!(obj[Y - 1][X + 1] == static_cast<char>(249)))
									return true;
							}
						}
					}

					obj[Y + i][X] = static_cast<char>(254);

				}
			}

			else
			{
				for (int i = 0; i < decks; i++)
				{
					for (int j = i; j < decks; j++)
					{
						if (!(obj[Y - j][X] == static_cast<char>(249)))
							return true;

						if (Y - (j + 1) >= 0 && X - 1 >= 0)
						{
							if (!(obj[Y - (j + 1)][X - 1] == static_cast<char>(249)))
								return true;
						}

						if (Y - (j + 1) >= 0 && X + 1 < size)
						{
							if (!(obj[Y - (j + 1)][X + 1] == static_cast<char>(249)))
								return true;
						}

						if (Y - decks >= 0)
						{
							if (!(obj[Y - decks][X] == static_cast<char>(249)))
							{
								return true;
							}
						}

						if (X + 1 < size)
						{
							if (!(obj[Y - j][X + 1] == static_cast<char>(249)))
								return true;

						}
						if (X - 1 >= 0)
						{
							if (!(obj[Y - j][X - 1] == static_cast<char>(249)))
								return true;
						}
					}
					obj[Y - i][X] = static_cast<char>(254);
				}
			}
			ships[queue].set_count_plus();
			if (ships[queue].get_amount() == (ships[queue].get_count() - 1))
			{
				queue++;
			}
			break;
		}

		}

		if (queue == 4)
			return false;
		else
			return true;
	}
}


void Print::View_table(vector<vector<char>> obj, int n)
{

	int count = 0;
	cout << "  ";
	for (char i = 'A'; i <= 'J'; i++)
	{

		cout << i << " ";
	}
	cout << "\n";
	for (int i = 0; i < n; i++)
	{
		cout << count << " ";
		for (int j = 0; j < n; j++)
		{
			cout << obj[i][j] << " ";
		}
		cout << "\n";
		count++;
	}
}

void Print::View_table_cursor(vector<vector<char>> obj, int n, Cursor cu, Color co)
{


	int x = cu.getx();
	int y = cu.gety();
	int count = 0;
	cout << "  ";
	for (char i = 'A'; i <= 'J'; i++)
	{

		cout << i << " ";
	}
	cout << "\n";
	for (int i = 0; i < n; i++)
	{

		cout << count << " ";
		for (int j = 0; j < n; j++)
		{
			if (y == i && x == j)
			{
				co.setColorSelected();
				cout << obj[i][j];
				co.setColor();
				cout << " ";

			}
			else
				cout << obj[i][j] << " ";

		}
		cout << "\n";
		count++;
	}
}






void Color::setColor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
}

void Color::setColorSelected()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 55);
}



void Cursor::setx(int X)
{
	x = X;
}

void Cursor::sety(int Y)
{
	y = Y;
}

int Cursor::getx()
{
	return x;
}

int Cursor::gety()
{
	return y;
}