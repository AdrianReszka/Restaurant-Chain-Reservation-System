#pragma once
#include "List_table.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm>  

void List_table::load_from_file (const string& name)
{
	ifstream file(name);
	smart p = this->ptr; //wskaznik na tabla
	string city, line, t_number, seats;
	int seats_, table;
	stringstream ss; 
	char sign;

	//sposob w jaki rezerwacja ma byc zapisana do pliku
	if (file.good())
	{
		while (!file.eof())
		{
			getline(file, city); cities.insert(city);
			int i = 0;
			do 
			{
				i++;
				if (i % 2 == 1)
				{
					getline(file, line);
					if (line.empty())
					{
						break;
					}
					ss << line;
					while (ss >> sign)
					{
						if (isdigit(sign))
						{
							seats.push_back(sign);
						}
					}
					seats_ = stoi(seats);
					seats.clear(); ss.str(""); ss.clear();
				}
				else
				{
					getline(file, line); 
					ss << line; 
					while (ss >> sign)
					{
						if (isdigit(sign))
						{
							t_number = sign; table = stoi(t_number);
							p = make_shared <Table>(city, table, seats_, this->ptr);
							this->ptr = p;
						}
					}
					ss.str(""); ss.clear();
				}

			} while (!file.eof());
		}
	}
	file.close();
}


ostream& operator << (ostream& s, set<string> c) //przeciazenie operatora dla zbioru miast(bo set jako drugi argument), zbior miast to set(wylapuje rodzaje)
{
	for (auto iter = c.begin(); iter != c.end(); ++iter)
	{
		s << ">" << *iter << endl;
	}
	return s;
}

ostream& operator << (ostream& s, List_table& list) //przeciazenie operatorow dla listy stolikow
{
	smart p = list.ptr;
	while (p)
	{
		s << *p;
		p = p -> pointer;
	}
	return s;
}

void List_table::display_cities()
{
	system("cls");
	cout << "====DOSTEPNE MIASTA====";
	cout << endl << cities << endl;
	cout << "Aby zakonczyc, wprowadz '0'" << endl;
	cout << endl << "Wprowadz nazwe miasta, w ktorym chcesz dokonac rezerwacji lub nacisnij '1' aby zobaczyc liste aktualnych rezerwacji\n" << endl;
	cout << "Ilosc rezerwacji w pliku: " << Reservation::counter << endl;
	cout << "\n";
}

List_table::List_table(smart& tableptr) //stworzenie wskaznika na kolejnyt element listy stolikow
{
	List_table::ptr = tableptr;
}

bool List_table::check(string& city) //sprawdza miasto i literka po literce sprawdza czy nazwa ktora wprowadziles zgadza sie z ktoryms miastem(sprawdza kazde az do konca)
{
	string cityupper;
	char sign; 
	stringstream ss;
	ss << city;
	while (ss >> sign)
	{
		sign = toupper(sign);
		cityupper.push_back(sign);
	}

	ss.str(""); ss.clear();
	
	city[0] = toupper(city[0]);
	for(int i = 1; i<city.size(); i++){
		city[i] = tolower(city[i]);
	}

		int i = 0;
		for (auto iter = cities.begin(); iter != cities.end(); ++iter)
		{
			string place = *iter;
			string iterupper = ""; 
			ss << place;
			while (ss >> sign)
			{
				sign = toupper(sign);
				iterupper.push_back(sign);
			} ss.clear(); ss.str("");
			if (iterupper == cityupper)
				return true;
			else
				i++;
		}
		
		if (i == cities.size())
		{
			cout << endl << "Niepoprawnie wprowadzone dane, sprobuj ponownie!" << endl;
			cin.get();
			return false;
		}

		return true;
}

void List_table::display_seats(string& city) //dla konkretnego miasta, sprawdza liste wszystkich stolikow, jesli stolik zgadza sie z miastem to wypisze stolik, zlicza ich ilosc
{
	stringstream ss; 
	char sign;
	ss << city; 
	string cityupper = "";
	while (ss >> sign)
	{
		sign = toupper(sign);
		cityupper.push_back(sign);
	}
	ss.str(""); ss.clear();
	cout << "=====" << cityupper << "=====" << endl << "Dostepne stoliki:" << endl;
	
	smart p = this->ptr;
	int x=0;
	vector<pair<int, int>> tables;
	
	while (p)
	{
		string pcity = p->city;
		ss << pcity; 
		pcity = "";
		while (ss >> sign)
		{
			sign = toupper(sign);
			pcity.push_back(sign);
		} ss.str(""); ss.clear();
		
		if (pcity == cityupper)
		{
			bool alreadyExists = false;
			for (auto&t:tables) {
				if (t.first == p->seats)
				{
					t.second++;
					alreadyExists = true;
				}
			}
			if (!alreadyExists)
			{
				tables.push_back(make_pair(p->seats,1));
			}
			x = p->seats;
		}
		p = p->pointer;
	}

	for (auto t:tables) {
		cout << "Stoliki " << t.first<< "-osobowe, ilosc: " << t.second <<endl;
	}

	cout << "\nAby przejsc do rezerwacji godziny wybierz '1', aby wrocic do wyboru miasta wpisz '0'.";
	cout << " \nJezeli ilosc stolikow po wybraniu godziny bedzie sie roznila to oznacza ze nie sa juz dostepne.\n" << endl;
}

void List_table::display_tables(string& city) //wyswietla stoliki dla konkretnego miasta
{
	smart p = this->ptr;
	while (p)
	{
		
		if (p->city.compare(city)==0)
		{
			cout << *p;
		}
		p = p->pointer;

	}
}

bool List_table::check2(string& city, string& seats) //sprawdza czy liczba osob jest prawidlowa z pojemnoscia stolika 
{
	stringstream ss; 
	char sign;
	ss << seats; 
	while (ss >> sign)
	{
		if (!isdigit(sign))
		{
			cout << "Niepoprawny wybor, wprowadz liczbe!" << endl;
			cin.get();
			return false;
		}
	}
	int seatsnr = stoi(seats);
	ss.str(""); ss.clear();
	smart p = this->ptr;
	string cityupper; string pcity;
	ss << city;
	while (ss >> sign)
	{
		sign = toupper(sign);
		cityupper.push_back(sign);
	}
	ss.str(""); ss.clear();
	while (p)
	{
		pcity = p->city;
		ss << pcity; 
		pcity = "";
		while (ss >> sign)
		{
			sign = toupper(sign);
			pcity.push_back(sign);
		}
		ss.str(""); ss.clear();
		if (pcity == cityupper && p->seats == seatsnr)
		{
			return true;
		}
		p = p->pointer;
	}
	cout << "Nie posiadamy wolnych stolikow dla podanej liczby osob!" << endl;
	cin.get();
	return false;

}

vector<Table>* List_table::choose_table(Date& dat, string& city, string& seats, List_res& thelist) //faktyczna rezerwacja stoikow z podanej listy(jest tutaj system rezerwacji wielokrotnej)
{
	vector<int> chosenTableNumbers; 
	string tableNumbersString;
	smart p = this->ptr;
	smart2 thelistp = thelist.ptr;
	stringstream ss; 
	char sign;
	string pcity;
	vector <int> notfree;
	int selectedTableSeatsCount;
	vector<Table> *returnedTables = new vector<Table>();
	
	
	while (thelistp)
	{
		string thelistpcity = thelistp->city;


		if (thelistpcity.compare(city)==0  && dat == thelistp->reservdate) //jezeli data i wprowadzone miasto sa poprawne, dodawanie zarezerwowanego stolika do wektora 
		{
			int reserved = thelistp->number;
			notfree.push_back(reserved);
		}
		thelistp = thelistp->pointer2;
	}
	int x = 0; 
	int freenr;
	bool goodinput = false;
	do {
		p = this->ptr;
		system("cls");
		cout << "Dostepne stoliki: " << endl;
		vector <int> freetables; //przechowuje stolik
		vector <int> freetablesSeats; //przechowuje pojemnosc stolika
		while (p)
		{
			bool free = true; 
			pcity = p->city; 


			for (auto iter = notfree.begin(); iter != notfree.end(); iter++) //sprawdzanie czy stolik jest zarezerwowany 
			{
				if (*iter == p->number)
					free = false;
			}

			
			if (pcity.compare(city) == 0 &&  free == true) //jesli stolik jest wolny to zostanie wyswietlony
			{
				p->display();
				x++;
				freenr = p->number; 
				freetables.push_back(freenr);
				freetablesSeats.push_back(p->seats);

			}
			p = p->pointer;
		}
		if (x != 0)
		{
			
			bool digit = true;
			cout << "\nWybierz numery stolikow aby je zarezerwowac, aby wrocic do wyboru daty wpisz '0'\n";
			cout << "Sekwencja musi byc zakonczona przecinkiem (poprawny format '4,22,1,'): \n" << endl;
			getline(cin, tableNumbersString);
			if (tableNumbersString.empty())
			{
				cout << "\nZly wybor, wprowadz liczby jeszcze raz"; cin.get(); digit = false; 
			}
			else if (tableNumbersString.compare("0")==0)
			{
				return nullptr;
			}
			else 
			{
				
				int subStrStart = 0;
				int subInt;
				string substr;
				for (int i = 0; i< tableNumbersString.size(); i++)
				{
					if (tableNumbersString[i] == ',') //przecinek do oddzielenia numerow stolikow
					{
						substr = tableNumbersString.substr(subStrStart, i-subStrStart); //wyluskanie numeru przed przecinkiem

						try
						{
							subInt = stoi(substr); //zmieniamy na liczbe
							if (find(chosenTableNumbers.begin(),chosenTableNumbers.end(),subInt)==chosenTableNumbers.end()) //sprawdza czy numer sie nie powtarza, jezeli nie to dodaje do wektora 
							{
								chosenTableNumbers.push_back(subInt);
								subStrStart = i + 1; //przechodzimy na kolejny numer 
							}
							else
							{

								cout << "\nZle sformatowane wejscie, nie mozna zarezerwowac tego samego stolika dwukrotnie";
								cin.get(); digit = false; break;
							}

							
						}
						catch (const std::exception&)
						{
							cout << "\nZle sformatowane wejscie, wprowadz liczby jeszcze raz";
							cin.get(); digit = false; break;
						}

					}
				}

				if (digit) //jesli wprowadzone dane byly poprawne
				{
					goodinput = true;
					for (auto table:chosenTableNumbers) //dla kazdego wybranego wczesniej stolika
					{
						auto it = find(freetables.begin(), freetables.end(), table); //szukamy wprowadzonego numeru w wektorze z wolnymi stolikami
						if (it==freetables.end()) {
							goodinput = false;
							break;
						}

						Table t(city, table, freetablesSeats.at(std::distance(freetables.begin(),it))); //jezeli wybrane stoliki sa wolne tworzymy obiekt typu table  
						returnedTables->push_back(t); //dodajemy go do wektora

					}
					if (!goodinput)
					{

						cout << "\nTaki stolik jest niedostepny lub nie istnieje, sprobuj ponownie"; cin.get();
					}
				}
			}
		}
	} while (!goodinput);
	

	
	return returnedTables;
}