/**
	---
	CyclicalList.h
	Назначение: Объявление класса цикличного списка

	@author Denis Aksoy
	@version 1.0 24/11/2018
*/

#pragma once
#include <string>

template <typename anyType>

/**
	Структура описывающая элемент списка
*/

struct Note
{
	// Ссылка на слудующий элемент
	Note *next;
	// Значение элемента
	anyType value;
};

template <typename anyType>
class CyclicList
{
private:
	// Сслыка на "голову" списка
	Note<anyType> *head = NULL;

	// Сслыка на "хвост" списка
	Note<anyType> *tail = NULL;
public:

	/**
		Добавить элемент
		@param value. Значение элемента.
	*/

	void addNote(anyType value);

	/**
		Преобразовать в строку
		@param нет.
		@return result. Строка из элементов списка.
	*/

	std::string toString();

	/**
		Найти по значению
		@param value. Значение.
		@return ссылку на элемент списка
	*/

	Note<anyType> *searchByValue(anyType value);

	/**
		Найти по индексу
		@param index. Индекс элемента.
		@return result. Значение элемента.
	*/

	anyType searchByIndex(int index);

	/**
		Больше чем
		@param value. Значение.
		@return result. Значение элемента.
	*/

	anyType moreThan(anyType value);
};