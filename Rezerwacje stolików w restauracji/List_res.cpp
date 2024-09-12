#pragma once
#include "List_res.h"
#include <fstream>
#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>

//pobiera numer rezerwacji do usuniecia i zamienia w liczbe
int List_res::getIndexFromUser(){
	
	int chosenReservation = 0;

	string reserveChoice;

	getline(cin, reserveChoice);
	stringstream ss;
	char sign;
	ss << reserveChoice;
	while (ss >> sign)
	{
		if (!isdigit(sign))
		{
			return -1;
		}
		chosenReservation *= 10;
		chosenReservation += (sign - '0');

	}
	return chosenReservation;
}

int List_res::getReservationNumber() //elementy listy to reservation
{
	return this->reservation_number;
}

void List_res::load_from_file(const string& name) //sprawdza czy sa rezerwacje w pliku, zbiera je
{

	ifstream file(name);
	smart2 p = this->ptr; //ptr jest hedem i my do p przypisujemy heda czyli p staje sie hedem(jakby byl null)
	string place, table, seats, resdate, resname, comments;
	int day_, month_, year_, hour_, minute_, t_number, seats_;

	if (file.good())
	{

		while (!file.eof())
		{
			getline(file, place, ',');
			if (place.empty())
				break;
			getline(file, table, '#'); getline(file, table, ','); t_number = stoi(table);
			getline(file, seats, '-'); seats_ = stoi(seats); getline(file, seats, ',');
			getline(file, resdate, '.'); day_ = stoi(resdate);
			getline(file, resdate, '.'); month_ = stoi(resdate);
			getline(file, resdate, ','); year_ = stoi(resdate);
			getline(file, resdate, ':'); hour_ = stoi(resdate);
			getline(file, resdate, ','); minute_ = stoi(resdate);
			getline(file, resname, ',');
			getline(file, comments);
			//zgrywamy z pliku wszystkie dane
			this->reservation_number++;

			Date d(year_, month_, day_, hour_, minute_); //robimy obiekt typu data
			p = make_shared <Reservation>(place, t_number, seats_, resname, comments, d, this->ptr); //alokujemy pamiec na nowy element listy, dodajemy nowy element listy(make_shared), this->ptr to zawsze head
			this->ptr = p; //zmieniamy heada(kazdy najnowszy element), robimy liste od konca

		}
	}
	file.close();
}

List_res::List_res(smart2& resptr) //konstruktor licznika rezerwacji gdy jest cos na liscie
{
	ptr = resptr;
	this->reservation_number = 0;
}
List_res::List_res() //konstruktor licznika rezerwacji kiedy nic na niej nie ma
{
	List_res::ptr = nullptr;
	this->reservation_number = 0;

}

void List_res::getSeat(string& chosenSeat) //pobiera numery stolikow do zarezerwowania i zamienia na liczbe
{	

	getline(cin, chosenSeat);
	int seatsnumber;
	try
	{
		seatsnumber = stoi(chosenSeat);
	}
	catch (const std::exception&)
	{

	}

}


bool List_res::checkdate(string& city, string& stringdate) //sprawdza poprawnosc daty
{
	stringstream ss; 
	char sign;
	string year_; 
	string month_; 
	string day_; 
	string hour_; 
	string minute_;
	int resyear, resmonth, resday, reshour, resminute;
	ss << stringdate; int i = 1;
	
	while (ss >> sign)
	{
		
		if (!isdigit(sign) && (sign != '-' && sign != ':' && sign != ','))
		{
			cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << endl; 
			cin.get();
			return false;
		}
	
		if (i <= 2)
		{
			day_.push_back(sign);
		}
		if (i == 3 && (sign != '-' && sign != '.'))
		{
			cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << endl; 
			cin.get();
			return false;
		}
		
		if (i > 3 && i <= 5)
		{
			month_.push_back(sign);
		}
		
		
		if (i == 6 && (sign != '-' && sign != '.'))
		{
			cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << endl; 
			cin.get();
			return false;
		}
		if (i >= 7 && i < 11)
		{
			year_.push_back(sign);
		}
		
		
		if (i == 11 && sign != ',')
		{
			cout << "\nPo podaniu daty nalezy wpisac przecinek i wprowadzic po nim godzine\n" << endl; 
			cin.get();
			return false;
		}
		if (i > 11 && i <= 13)
		{
			hour_.push_back(sign);
		}
		
		if (i == 14 && sign != ':')
		{
			cout << "\nPodaj godzine rezerwacji w formacie (hh:min), np. 18:30\n" << endl; 
			cin.get();
			return false;
		}
		if (i > 14 && i <= 16)
		{
			minute_.push_back(sign);
		}
		
		i++;
	}
	if (i != 17)
	{
		cout << "\nNiepoprawne wprowadzone dane\n" <<endl; 
		cin.get();
		return false;
	}
	resday = stoi(day_);
	resmonth = stoi(month_);
	if (resmonth < 1 || resmonth > 12)
	{
		cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << endl; 
		cin.get();
		return false;
	}
	if ((resmonth == 1 || resmonth == 3 || resmonth == 5 || resmonth == 7 || resmonth == 8 || resmonth == 10 || resmonth == 12) && (resday < 1 || resday > 31))
	{
		cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << endl; 
		cin.get();
		return false;
	}
	if ((resmonth == 4 || resmonth == 6 || resmonth == 9 || resmonth == 11) && (resday < 1 || resday > 30))
	{
		cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << endl; 
		cin.get();
		return false;
	}
	if (resmonth == 2 && (resday < 1 || resday > 29))
	{
		cout << "\nNiepoprawne dane, wprowadz date jeszcze raz\n" << endl; 
		cin.get();
		return false;
	}
	resyear = stoi(year_);
	if (resyear < 2023 || resyear > 2030)
	{
		cout << "\nWprowadz poprawny rok\n" << endl; 
		cin.get();
		return false;
	}
	reshour = stoi(hour_);
	if (reshour < 14 || reshour > 22)
	{
		cout << "\nPrzyjmujemy rezerwacje miedzy godzina 14 a 22.\n" << endl; 
		cin.get();
		return false;
	}
	resminute = stoi(minute_);
	if (resminute < 0 || resminute > 59)
	{
		cout << "\nNiepoprawna minuta rezerwacji\n" << endl; 
		cin.get();
		return false;
	}
	if ((resyear == 2023 && resmonth < 9) || (resyear == 2023 && resmonth == 9 && resday < 1)) //zmienic na date obrony projektu
	{
		cout << "\nNiepoprawne dane rezerwacji\n" << endl; 
		cin.get();
		return false;
	}
	ss.str(""); 
	ss.clear();
	return true;

}

Date List_res::getdate(string& stringdate) //zamienia wprowadzonego stringa na inty i tworzy z nich obiekt typu date
{

	stringstream ss; char sign;
	string year_; string month_; string day_; string hour_; string minute_;
	int resyear, resmonth, resday, reshour, resminute;
	ss << stringdate; int i = 1;
	while (ss >> sign)
	{

		if (i <= 2)
		{
			day_.push_back(sign);
		}

		if (i > 3 && i <= 5)
		{
			month_.push_back(sign);
		}

		if (i >= 7 && i < 11)
		{
			year_.push_back(sign);
		}

		if (i > 11 && i <= 13)
		{
			hour_.push_back(sign);
		}

		if (i > 14 && i <= 16)
		{
			minute_.push_back(sign);
		}
		i++;
	}
	resday = stoi(day_);
	resmonth = stoi(month_);
	resyear = stoi(year_);
	reshour = stoi(hour_);
	resminute = stoi(minute_);

	Date newdate(resyear, resmonth, resday, reshour, resminute);
	return newdate;
}

void List_res::addtolist(Reservation& res)
{
	//taka sama zasada jak powyzej tylko ze wsadzamy do listy rezerwacje
	smart2 R = make_shared <Reservation>(res);
	R->pointer2 = this->ptr; //ustawiamy wskaznik na rezerwacje
	this->ptr = R; //R zostaje pierwszym elementem listy
	this->reservation_number++;


}

bool List_res::removeFromList(int primaryKey) //usuwa rezerwacje z listy
{

	smart2 p = this->ptr;
	smart2 temp;
	
	if (primaryKey!=1) {

		while ((primaryKey--) > 2) //tak dlugo az podany numer zmniejszony o jeden bedzie wiekszy od 2
		{
			p = p->pointer2; //przechodzimy po liscie 
			
		}

		temp = p->pointer2; //wskaznik przechodzi na kolejny element
		p->pointer2 = nullptr; //w miejsce elementu umieszczamu nullptr, usuwamy element z danego miejsca na liscie
		this->reservation_number--; //zmniejszamy ilosc rezerwacji 
		
		if (temp->pointer2)
		{
			p->pointer2 = temp->pointer2; //przestawiamy wskaznik na kolejny niepusty element czyli podmieniamy miejsca na liscie
		}
	}
	else
	{
		this->reservation_number--;
		this->ptr = this->ptr->pointer2; //usuwamy pierwszy element
	}

	cin.get();

	this->display(); //wyswietlamy stan rezerwacji po usunieciu
	
	return true;
	
}

void List_res::display()
{
	cout << *this; 
}

ostream& operator << (ostream& s, List_res& list) //przeciazenie operatora 
{
	smart2 p = list.ptr;
	int index = 1;
	while (p)
	{
		cout << index++ <<". ";

		s << *p; //przeciazenie operatora dla listy korzysta z przeciazenia operatora dla rezerwacji 
		p = p->pointer2;
		cout << '\n';
	}
	return s;
}

void List_res::savetofile(const string&name) //przy pomocy przeciazenie operatora 
{
	ofstream file;
	file.open(name);
	smart2 p = this->ptr;
	while (p)
	{
		file << p->city << ", " << "Stolik nr #" << p->number << ", " << p->seats << "-osobowy, ";
		
		if (p->reservdate.day < 10)
		{
			file << "0" << p->reservdate.day << ".";
		}
		else
		{
			file << p->reservdate.day << ".";
		}

		if (p->reservdate.month < 10)
		{
			file << "0" << p->reservdate.month << ".";
		}
		else
		{
			file << p->reservdate.month << ".";
		}

		file << p->reservdate.year << ", ";

		if (p->reservdate.hour < 10)
		{
			file << "0" << p->reservdate.hour << ":";
		}
		else
		{
			file << p->reservdate.hour << ":";
		}

		if (p->reservdate.minute < 10)
		{
			file << "0" << p->reservdate.minute;
		}
		else
		{
			file << p->reservdate.minute;
		}
		file<< ", " << p->name << ", " << p->comments << endl;
		
		p = p->pointer2;

	}
	file.close();
}