
#include "List_table.h"
#include "List_res.h"
#include <iostream>
#include <sstream> 
#include <vector>

using namespace std;

int main()
{
	const string base = "baza.txt";
	const string base2 = "rezerwacje.txt";
	smart start; //wskaznik na table 
	smart2 res_start; //wskaznik na rezerwacje
	List_table tables(start); //head listy stolikow
	List_res reserved(res_start); //head(pierwszy) listy rezerwacji
	tables.load_from_file(base); 
	reserved.load_from_file(base2);
	bool next = true; 
	bool next2 = false; 
	bool next3 = false;

	do
	{
		cin.clear(); tables.display_cities();

		string choice_city ;
		getline(cin, choice_city);

		if (choice_city == "0") { break; }
		
		if (choice_city == "1") 
		{
			while (true)
			{

				system("cls");
				reserved.display();
				cout << "\nWybierz numer zamowienia z ktorego chcesz zrezygnowac (jesli chcesz wrocic do poprzedniego menu wpisz 0): \n" << endl;
				int chosenReservation = reserved.getIndexFromUser();
			
			
				while (chosenReservation < 0 || chosenReservation>reserved.getReservationNumber()) {
					cout << "\nNiepoprawny wybor, wprowadz liczbe!\n" << endl;
					
					chosenReservation = reserved.getIndexFromUser();
				}

				if (chosenReservation == 0) break;

				reserved.removeFromList(chosenReservation);

			}
			
		}

		else if (next2 = tables.check(choice_city))
		{
			system("cls");
			tables.display_seats(choice_city);

			do 
			{
				string seats_choice;
				getline(cin, seats_choice);
				if (seats_choice == "0") { break; }
				else if (seats_choice == "1") {}
				else { cout << "\nPodana opcja nie istnieje\n" << endl; 
				next2 = false;  
				continue; };

				
				do 
				{
					system("cls");
					
					string datechoice;
					cout << "Podaj date i godzine rezerwacji (dd-mm-rrrr, hh:min) (jesli chcesz wrocic, wybierz '0'):\n" << endl;
					
					getline(cin, datechoice);  
					
					if (datechoice == "0") { next2 = false; ; system("cls"); tables.display_seats(choice_city);  break;  }


					if (next3 = reserved.checkdate(choice_city, datechoice))
					{
						system("cls");

						string reservename; 
						string comments = ""; 
						string choicenext;
						
						Date dateofreserv = reserved.getdate(datechoice);
						vector<Table>* ptr = tables.choose_table(dateofreserv, choice_city, seats_choice, reserved);
						vector<Table> chosentables;
						
						if(ptr == nullptr)
						{
							next3 = false;
							continue;
						}
						else {
							chosentables = *ptr;
							delete ptr;

						}

						cout << "\nWprowadz nazwisko na jakie ma zostac zapisana rezerwacja: "; getline(cin, reservename); 
						cout << endl << "Dodatkowe uwagi do zamowienia (jesli brak, wcisnij enter): "; getline (cin, comments);

        				for (auto chosentable:chosentables)
						{
							Reservation newreservation(chosentable.city, chosentable.number, chosentable.seats, reservename, comments, dateofreserv);
							reserved.addtolist(newreservation);
							
							cout << endl;
							newreservation.display();
						}

						cin.get();
						do
						{
							system("cls");
							cout << "Czy chcesz dokonac kolejnej rezerwacji? Wpisz 't' lub 'n': \n" << endl; 
							
							getline(cin, choicenext);
							
							if (choicenext == "n")
							{
								next = false;
							}
							else if (choicenext != "t" && choicenext != "n")
							{
								cout << "Wpisz 't' lub 'n'!"; cin.get();
							}
						} while (choicenext != "t" && choicenext != "n");
					}	
				} while (!next3);
				
			} while (!next2);
		}

	} while (next);
	reserved.savetofile(base2);











}