#pragma once

class Ship
{
protected:
	int size;
	int amount;
	
	int count = 1;
public:
	int get_size() { return size; };
	int get_amount() { return amount; };
	int get_count() { return count;  };
	void set_count_plus() { count++; };
};

class One_deck : public Ship
{
public:
	One_deck();
	
};

class Two_deck : public Ship
{
public:
	Two_deck();
	
};

class Three_deck : public Ship
{
public:
	Three_deck();
};

class Four_deck : public Ship
{
public:
	Four_deck();
	
};