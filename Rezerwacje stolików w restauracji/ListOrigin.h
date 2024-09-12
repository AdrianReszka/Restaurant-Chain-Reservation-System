/**@file*/
#pragma once
#ifndef LIST_ORIGIN_H
#define LIST_ORIGIN_H

#pragma once
#include <string>

/**Klasa bazowa dla klasy List_res, zawierajaca wirtualna metode load_from_file sluzaca do wczytywania danych z pliku */
class ListOrigin
{
public:

	virtual void load_from_file(const std::string &name) = 0;
};

#endif