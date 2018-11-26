/**
	---, CyclicalList.cpp
	����������: ���������� ���������� ������

	@author Denis Aksoy
	@version 1.0 24/11/2018
*/

#include "CyclicList.h"

/**
	��������� ������� � ������.
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
	������� ������ �� ��������� ������ ���� ��� ��������.
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
	���� ������� �� ��������.
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
	���� ������� �� �������.
*/

template<typename anyType>
anyType CyclicList<anyType>::searchByIndex(int index)
{
	Note<anyType> *current = head;
	for (int i = 0; current->next != head; i++) {  // ���������� ��� �������� � ���� ������ ������
		if (i == index)
			return current->value;
		current = current->next;
	}
	return anyType();
}

/**
	���� ������� �� ������� (������ ���).
*/

template<typename anyType>
anyType CyclicList<anyType>::moreThan(anyType value)
{
	Note<anyType> *current = head;
	do {  // ���������� ��� �������� � ���� ������ ���...
		if (current->value > value)
			return current->value;
		current = current->next;
	} while (current->next != head);
	return anyType();
}