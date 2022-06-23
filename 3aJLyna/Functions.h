#pragma once
#include <conio.h>
#include <string>
#include <windows.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <exception>
#include "Ships.h"
using namespace std;


class Cursor
{
	int x;
	int y;
public:
	void setx(int X);
	void sety(int Y);
	int getx();
	int gety();
};

class Color
{
public:
	void setColor();
	void setColorSelected();
};

class Set_ships
{
public:
	void Set_all_ships_bot(vector<vector<char>>& obj, vector<Ship>&ships, int &queue, int size);
	bool Set_all_ships_player(int X, int Y, int dir, vector<vector<char>>& obj, vector<Ship>&ships, int &queue, int size);
};

class Cheat
{
public:
	bool Cheat_on(vector<vector<char>>& obj, int size, int &hp_enemy);
};

class Attack
{
public:
	int Attack_bot(vector<vector<char>>&obj,int size);
	bool Attack_player(vector<vector<char>>& dummy, vector<vector<char>>&enemy, int X, int Y, int &hp_enemy);
	
};



class Table
{
	Cursor cur;
	Color col;
	Set_ships set;
	Attack attack;
	Cheat chpik;

	vector<vector<char>> table;
	vector<vector<char>> enemy;
	vector<vector<char>> dummy;
	vector<Ship> ships_player;
	vector<Ship> ships_bot;

	int hp_player;
	int hp_enemy;
	int size;
	int queue = 0;

public:
	Table(int n);
	void Set_hp();
	int Get_hp_player() { return hp_player; };
	int Get_hp_enemy() { return hp_enemy; };
	vector<vector<char>> &Get_table();
	vector<vector<char>> &Get_enemy();
	vector<vector<char>> &Get_dummy();
	void Move_on_table(int which, int action);
	void Bot_set_ships();
	bool Game_process();

};





class Print
{
public:

	void View_table(vector<vector<char>> obj, int n);
	void View_table_cursor(vector<vector<char>> obj, int n, Cursor cu, Color co);

};



