#pragma once
#include "Technology.h"

class Company : public Technology { //���� ������, �������� �� ���������
private:
	string nameOfCompany; //����� ������
	string spisokTechnology[4]; //������ ���������
	string history; //���� ������� �� ����
	int priceLicense; //���� �� ������

public:
	Company(string n, string h, int p) { //�����������
		nameOfCompany = n;
		history = h;
		priceLicense = p;
	}

	void obchyslennya(string spisokTechnology[4]);//������� ��� ���������� ���� �� �����


	~Company() { //����������
		cout << "Destroyed." << endl;
	}
};
