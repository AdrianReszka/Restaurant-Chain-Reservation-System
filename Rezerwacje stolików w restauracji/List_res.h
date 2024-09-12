/** @file */
#pragma once
#ifndef LIST_RES_H
#define LIST_RES_H

#include "ListOrigin.h"
#include "Reservation.h"
using namespace std;

/**Klasa bedaca lista rezerwacji wczytanych z pliku i wprowadzonych przez uzytkownika*/
class List_res : public ListOrigin
{
private:
	smart2 ptr;	///<Wskaznik na kolejny obiekt typu Reservation
	int reservation_number; ///<Zmienna liczaca rezerwacje znajdujace sie w pliku, potrzebna do algorytmu usuwania rezerwacji
public:

	/**Metoda pobierajaca liczbe rezerwacji 
	@return Liczbe rezerwacji */
	int  getReservationNumber(); //

	/** Metoda wczytujaca z pliku dokonane rezerwacje
	@param name Nazwa pliku z ktorego maja byc wczytane rezerwacje */
	void load_from_file(const string& name);

	/** Metoda sprawdzajaca poprawnosc wprowadzonej przez uzytkownika daty
	@param city Wybor miasta wprowadzony przez uzytkownika
	@param seats Liczba siedzen przy stoliku wprowadzona przez uzytkownika
	@param stringdate Wybor daty wprowadzony przez uzytkownika
	return True jesli data jest poprawna, w przeciwnym wypadku wartosc false */
	bool checkdate(string& city, string& stringdate);

	/**Metoda pobierajaca numery stolikow do rezerwacji od uzytkownika a nastepnie zamienia je w liczbe 
	@param chosenSeat Numer stolika wprowadzony przez uzytkownika */
	void getSeat(string& chosenSeat);

	/** Metoda dodajaca rezerwacje do listy
	@param res Rezerwacja ktora ma zostac dodana do listy */
	void addtolist(Reservation& res);

	/**Metoda usuwajaca rezerwacje z listy 
	@param primaryKey Numer rezerwacji do usuniecia wprowadzony przez uzytkownika
	@return True gdy rezerwacja zostanie poprawnie usunieta, przeciwnym wypadku False */
	bool removeFromList(int primaryKey);

	/** Metoda wypisujaca zawartosc listy*/
	void display();

	/** Metoda zapisujaca liste rezerwacji do pliku
	@param name Nazwa pliku do ktorego maja zostac zapisane rezerwacje */
	void savetofile(const string &name);

	/** Metoda pobierajaca wartosc daty ze znakow wprowadzonych przez uzytkownika
	@param stringdate Wybor daty wprowadzony przez uzytkownika
	@return Obiekt typu Date bedacy data o danych wprowadzonych przez uzytkownika */
	Date getdate(string& stringdate);

	/** Konstruktor jednoargumentowy
	@param resptr Wskaznik na obiekt typu Reservation */
	List_res(smart2& resptr);

	/** Konstruktor bezargumentowy */
	List_res();

	friend class List_table;

	/** Operator strumieniowy wyjscia wypisujacy zawartosc listy
	@param s Operator strumieniowy wyjscia
	@param list Lista do wypisania
	@return Operator strumieniowy wyjscia */
	friend ostream& operator << (ostream& s, List_res& list);

	/**Metoda pobierajaca numer rezerwacji do usuniecia i zamieniajaca go z liczbe 
	@return Wybrany numer rezerwacji */
	int getIndexFromUser();
};
#endif