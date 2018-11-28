/**
	---
	CyclicalList.h
	Íàçíà÷åíèå: Îáúÿâëåíèå êëàññà öèêëè÷íîãî ñïèñêà
	Purpose: Declaring a cyclical list class
	@author Denis Aksoy
	@version 1.0 24/11/2018
*/

#pragma once
#include <string>

template <typename anyType>

/**
	Ñòðóêòóðà îïèñûâàþùàÿ ýëåìåíò ñïèñêà
	The structure describing the list element
*/

struct Note
{
	// Ññûëêà íà ñëóäóþùèé ýëåìåíò / Link to the next element
	Note *next;
	// Çíà÷åíèå ýëåìåíòà / Element value
	anyType value;
};

template <typename anyType>
class CyclicList
{
private:
	// Ññëûêà íà "ãîëîâó" ñïèñêà / Link to the "head" of the list
	Note<anyType> *head = NULL;

	// Ññëûêà íà "õâîñò" ñïèñêà / Link to the "tail" of the list
	Note<anyType> *tail = NULL;
public:

	/**
		Äîáàâèòü ýëåìåíò
		Add element
		@param value. Çíà÷åíèå ýëåìåíòà/Element value
	*/

	void addNote(anyType value);

	/**
		Ïðåîáðàçîâàòü â ñòðîêó
		Convert to string
		@param íåò/no
		@return result. Ñòðîêà èç ýëåìåíòîâ ñïèñêà/String of list items
	*/

	std::string toString();

	/**
		Íàéòè ïî çíà÷åíèþ
		Find by value
		@param value. Çíà÷åíèå/Value
		@return ññûëêó íà ýëåìåíò ñïèñêà/Link to list item
	*/

	Note<anyType> *searchByValue(anyType value);

	/**
		Íàéòè ïî èíäåêñó
		Find by index
		@param index. Èíäåêñ ýëåìåíòà/Element index
		@return result. Çíà÷åíèå ýëåìåíòà/Element value
	*/

	anyType searchByIndex(int index);

	/**
		Áîëüøå ÷åì
		More than
		@param value. Çíà÷åíèå/Value
		@return result. Çíà÷åíèå ýëåìåíòà/Element value
	*/

	anyType moreThan(anyType value);
};
