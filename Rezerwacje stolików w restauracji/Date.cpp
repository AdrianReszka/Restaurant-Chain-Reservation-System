#pragma once
#include "Date.h"
#include <iostream>

using namespace std;

Date::Date(int& y, int& m, int& d, int& h, int& min) : year(y), month(m), day(d), hour(h), minute(min) {} //tez ale argumentowy

bool Date::operator == (const Date& d) //przeciazony operator porownania dla daty (zabezpiecza zeby nie zarezerwowac jednego stolika nie szybciej niz 2h po wczesniejszej rezerwacji lub przed)
{
	int diff;
	if (this->hour > d.hour)
	{
		diff = (this->hour - d.hour) * 60 + (this->minute - d.minute);
	}
	else if (this->hour < d.hour)
	{
		diff = (d.hour - this->hour) * 60 + (d.hour - this->minute);
	}
	else
	{
		diff = abs(d.hour - this->minute);
	}
	if (this->day == d.day && this->month == d.month && this->year == d.year && diff < 120)
	{
		return true;
	}
	else
		return false;
}

Date::Date() {} //konstruktor domyslny

void Date::display() //wyswietlanie daty
{
	if (Date::day < 10)
	{
		cout << "0" << Date::day << ".";
	}
	else
	{
		cout << Date::day << ".";
	}

	if (Date::month < 10)
	{
		cout << "0" << Date::month << ".";
	}
	else
	{
		cout << Date::month << ".";
	}

	cout << Date::year << ", ";

	if (Date::hour < 10)
	{
		cout << "0" << Date::hour << ":";
	}
	else
	{
		cout << Date::hour << ":";
	}

	if (Date::minute < 10)
	{
		cout << "0" << Date::minute;
	}
	else
	{
		cout << Date::minute;
	}

}