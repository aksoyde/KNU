/**
	---
	CyclicalList.h
	����������: ���������� ������ ���������� ������

	@author Denis Aksoy
	@version 1.0 24/11/2018
*/

#pragma once
#include <string>

template <typename anyType>

/**
	��������� ����������� ������� ������
*/

struct Note
{
	// ������ �� ��������� �������
	Note *next;
	// �������� ��������
	anyType value;
};

template <typename anyType>
class CyclicList
{
private:
	// ������ �� "������" ������
	Note<anyType> *head = NULL;

	// ������ �� "�����" ������
	Note<anyType> *tail = NULL;
public:

	/**
		�������� �������
		@param value. �������� ��������.
	*/

	void addNote(anyType value);

	/**
		������������� � ������
		@param ���.
		@return result. ������ �� ��������� ������.
	*/

	std::string toString();

	/**
		����� �� ��������
		@param value. ��������.
		@return ������ �� ������� ������
	*/

	Note<anyType> *searchByValue(anyType value);

	/**
		����� �� �������
		@param index. ������ ��������.
		@return result. �������� ��������.
	*/

	anyType searchByIndex(int index);

	/**
		������ ���
		@param value. ��������.
		@return result. �������� ��������.
	*/

	anyType moreThan(anyType value);
};