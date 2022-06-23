#include "Functions.h"

void main()
{
	srand(time(0));
	const int n = 10;
	string player_name;
	cout << "Input your name: ";
	getline(cin, player_name);
	system("cls");
	Table game(n);
	Print show;
	bool status;
	game.Set_hp();
	game.Bot_set_ships();
	game.Move_on_table(0, 0);
	status = game.Game_process();
	system("cls");
	if (status == false)
	{
		show.View_table(game.Get_enemy(), n);
		cout << "\n\n";
		show.View_table(game.Get_table(), n);
		cout << "\n\n" << "COMPUTER WINS!!!\n";
	}
	else
	{
		show.View_table(game.Get_enemy(), n);
		cout << "\n\n";
		show.View_table(game.Get_table(), n);
		cout<<"\n\n" << player_name<<" WINS!!!\n\n";
	}
	system("pause");

}