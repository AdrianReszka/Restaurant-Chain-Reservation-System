#pragma once
#include "Table.h"
#include <iostream>
using namespace std;

Table::Table(string& c, int& n, int& s, smart& next) : city(c), number(n), seats(s), pointer (next) {} //argumentowy ze wskaznikiem

Table::Table(string& c, int& n, int& s): city (c), number (n), seats (s) {} //argumentowy

void Table::display()
{
	cout  << *this;
	//przeciazam operator (nie moge wypisac obiekt wiec wyswietlam go przez referencje)
	//gwiazdka to stolik a this to wskaznik

}
ostream& operator << (ostream& s, Table& t) //operator strumieniowy przeciazony dla stolika
{
	s << t.city << "; " << "Stolik " << t.seats << "-osobowy nr #" << t.number << endl;
	return s;
}

Table::Table() {} //konstruktor domyslny