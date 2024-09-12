/**@file*/
#pragma once
#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <memory>
#include "TableOrigin.h"

using namespace std;


class Table : public TableOrigin
{
public:
	string city; ///<Zmienna przechowujaca miasto w ktorym znajduje sie stolik
	int number; ///<Zmienna przechowujaca numer stolika 
	int seats; ///<Zmienna przechowujaca liczbe miejsc przy stoliku

	typedef shared_ptr <Table> smart; ///<Typydef dla wskaznika na kolejny obiekt typu Reservation
	
	/**Konstruktor czteroargumentowy
	@param c Miasto
	@param n Numer stolika
	@param s Liczba miejsc przy stoliku
	@param next Wskaznik na nastepny obiekt typu Table */
	Table(string& c, int& n, int& s, smart& next);

	/***Konstruktor trojargumentowy
	@param c Miasto
	@param n Numer stolika
	@param s Liczba miejsc przy stoliku */
	Table(string& c, int& n, int& s);

	/**Konstruktor bezargumentowy */
	Table();

	/**Metoda wyswietlajaca dane stolika */
	void display(); 
	
private:
	smart pointer; ///<Wskaznik na kolejny obiekt typu Table


	friend class List_table;

	/**Operator strumieniowy wyjscia 
	@param s Operator strumieniowy wyjscia
	@param list Lista stolikow wczytanych z pliku 
	@return Operator strumieniowy wyjscia */
	friend ostream& operator << (ostream& s, List_table& list);

	/**Operator strumieniowy wyjscia 
	@param s operator strumieniowy wyjscia 
	@param t Stolik ktorego dane zostana wypisane 
	@return Operator strumieniowy wyjscia */
	friend ostream& operator << (ostream& s, Table& t);
	
};

typedef shared_ptr <Table> smart;
#endif
