/** @file */
#pragma once
#ifndef TABLE_ORIGIN_H
#define TABLE_ORIGIN_H

/**Klasa bazowa dla klasy Table, zawierajaca wirtualna metode display, sluzaca do wyswietlania na ekranie */
class TableOrigin
{
public:
	virtual void display() = 0;
};
#endif