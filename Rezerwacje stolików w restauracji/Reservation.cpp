#pragma once
#include "Reservation.h"
#include <iostream>
using namespace std;

int Reservation::counter = 0;

Reservation::Reservation(string& c, int& n, int& s, string& resname, string& com, Date& dat, smart2 next2) : Table(c, n, s), //konstruktor
name(resname), comments(com), reservdate(dat), pointer2(next2) {

	counter++;

}

void Reservation::display() //wypisanie
{
	cout << *this;
}

Reservation::Reservation(string& c, int& n, int& s, string& resname, string& com, Date& dat) : Table(c, n, s), //stworzenie rezerwacji bez przekazania pointera, nie ma przekazania to zerujemy
name(resname), comments(com), reservdate(dat) 
{
	Reservation::pointer2 = nullptr;
	counter++;
}

Reservation::~Reservation() {

	counter--;
}

Reservation::Reservation(const Reservation& r) //konstruktor kopiujacy dla rezerwacji
{
	Reservation::city = r.city;
	Reservation::number = r.number;
	Reservation::seats = r.seats;
	Reservation::name = r.name;
	Reservation::comments = r.comments;
	Reservation::reservdate = r.reservdate;
	Reservation::pointer2 = r.pointer2;
	counter++;
}

ostream& operator << (ostream& s, Reservation& res) //przeciazenie operatora strumieniowego dla rezerwacji
{
	s << "Miasto: " << res.city << "; Stolik nr #" << res.number << "(" << res.seats << "-osobowy) ";
	
	
	if (res.reservdate.day < 10)
	{
		s << "0" << res.reservdate.day << ".";
	}
	else
	{
		s << res.reservdate.day << ".";
	}

	if (res.reservdate.month < 10)
	{
		s << "0" << res.reservdate.month << ".";
	}
	else
	{
		s << res.reservdate.month << ".";     
	}

	s << res.reservdate.year << ", ";

	if (res.reservdate.hour < 10)
	{
		s << "0" << res.reservdate.hour << ":";
	}
	else
	{
		s << res.reservdate.hour << ":";
	}

	if (res.reservdate.minute < 10)
	{
		s << "0" << res.reservdate.minute;
	}
	else
	{
		s << res.reservdate.minute;
	}
	

	s << '\n' << "Nazwisko: " << res.name << '\n';
	if (!res.comments.empty())
	{
		s << "Dodatkowe uwagi: " << res.comments << endl;
	}
	return s;
}

