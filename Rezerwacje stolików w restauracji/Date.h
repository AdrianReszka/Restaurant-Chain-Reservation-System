/** @file */
#pragma once
#ifndef DATE_H
#define DATE_H

#include "TableOrigin.h"

/**Klasa Date zawierajaca dane dotyczace daty zarerwacji */
class Date : public TableOrigin {
public:
	int year; ///<Zmienna przechowujaca rok rezerwacji stolika

	int month; ///<Zmienna przechowuajca miesiac rezerwacji stolika

	int day; ///<Zmienna przechowujaca dzien rezerwacji stolika

	int hour; ///<Zmienna przechowujaca godzine rezerwacji stolika

	int minute; ///<Zmienna przechowujaca minute rezerwacji stolika

public:

	/**Metoda sluzaca do wyswietlania daty */
	void display();

	/**Przeciazony operator porownania 
	@param d Obiekt porownywany 
	@return Wartosc True gdy obiekty maja taki sam dzien, miesiac i rok oraz roznica miedzy godzinami wynosi mniej niz 120 minut, w innym wypadku False */
	bool operator == (const Date& d);

	/**Konstruktor piecioargumentowy
	@param y Rok rezerwacji stolika
	@param d Dzien rezerwacji stolika
	@param h Godzina rezerwacji stolika
	@param min Minuta rezerwacji stolika */
	Date(int& y, int& m, int& d, int& h, int& min);

	/**Konstruktor bezargumentowy */
	Date();
	
	friend class List_res;

	friend class Reservation;

};

#endif