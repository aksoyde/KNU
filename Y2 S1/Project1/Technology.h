#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class Technology { //������� ���� (�����������)
public: //���������� ���������� �������, �� ������ ����������������� � ��������� ����
	string title[10]; //����� ���������.
	int time;
	int money;
	int price;

	virtual void obchyslennya(string spisokTechnology[]) = 0; //��������� ������� ��� ���������� ���� �� �����
	Technology();
	~Technology();
};
