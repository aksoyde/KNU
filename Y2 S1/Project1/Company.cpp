#include "Company.h"

void Company::obchyslennya(string spisokTechnology[4]) { //������� ��� ���������� ���� �� �����
	int randTime = 0, randMoney = 0;
	int avTime = 0, avMoney = 0;

	for (int i = 0; i < 4; i++) {
		randTime = rand() % 24; //�������� ��������� �������� ����
		randMoney = rand() % 1000 + 100; //�������� ��������� �����

		avTime += randTime;
		avMoney += randMoney;
	}
	avMoney += priceLicense; //������ �� ���� ������

	cout << "�����: " << nameOfCompany << endl;
	cout << "�������� ������� ��������: " << avMoney << endl;
	cout << "���: " << avTime << endl;

	cout << "������ ����������: " << endl;

	for (int j = 0; j < 4; j++) { //�������� ������ ���������
		cout << j + 1 << " " << spisokTechnology[j] << endl;
	}
}
