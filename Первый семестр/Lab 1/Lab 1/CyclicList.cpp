/**
	---, CyclicalList.cpp
	Íàçíà÷åíèå: Ðåàëèçàöèÿ öèêëè÷íîãî ñïèñêà
	Purpose: Implementation of cyclical list
	@author Denis Aksoy
	@version 1.0 24/11/2018
*/

#include "CyclicList.h"

/**
	Äîáàâëÿåò ýëåìåíò â ñïèñîê.
	Adds element in list
*/

template <typename anyType>
void CyclicList<anyType>::addNote(anyType value)
{
	if (tail == NULL) {
		tail = new Note<anyType>;
		tail->value = value;
		tail->next = head;
		head = tail;
	} else {
		tail->next = new Note<anyType>;
		tail = tail->next;
		tail->next = head;
		tail->value = value;
	}
}

/**
	Ñîçäàåò ñòðîêó èç ýëåìåíòîâ ñïèñêà åñëè ýòî âîçìîæíî.
	Creates string out of elements of list if possible
*/

template <typename anyType>
std::string CyclicList<anyType>::toString() {
	std::string result="";
	Note<anyType> *current = head;
	do {
		result += std::to_string(current->value);
		result += " ";
		current = current-> next;
	} while (current->next != head);
	return result;
}

/**
	Èùåò ýëåìåíò ïî çíà÷åíèþ.
	Searches an element by value
*/

template<typename anyType>
Note<anyType>* CyclicList<anyType>::searchByValue(anyType value)
{
	Note<anyType> *current = head;
	do {
		if (current->value == value) 
			return current;
		current = current->next;
	} while (current->next != head);
	return new Note<anyType>();
}

/**
	Èùåò ýëåìåíò ïî èíäåêñó.
	Searches element by index
*/

template<typename anyType>
anyType CyclicList<anyType>::searchByIndex(int index)
{
	Note<anyType> *current = head;
	for (int i = 0; current->next != head; i++) {  // Ïåðåáåðàåì âñå ýëåìåíòû è èùåì íóæíûé èíäåêñ/ Iterate through all the elements and looks for the needed index.
		if (i == index)
			return current->value;
		current = current->next;
	}
	return anyType();
}

/**
	Èùåò ýëåìåíò ïî óñëîâèþ (áîëüøå ÷åì).
	Seaches element by... (not sure how to translate)
*/

template<typename anyType>
anyType CyclicList<anyType>::moreThan(anyType value)
{
	Note<anyType> *current = head;
	do {  // Ïåðåáåðàåì âñå ýëåìåíòû è èùåì áîëüøå ÷åì.../ Going through all the elements and looking for more than...
		if (current->value > value)
			return current->value;
		current = current->next;
	} while (current->next != head);
	return anyType();
}
