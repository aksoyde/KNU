#pragma once
#include "Technology.h"

class Company : public Technology { //клас компанії, похідний від технологій
private:
	string nameOfCompany; //назва компанії
	string spisokTechnology[4]; //список технологій
	string history; //дати початку та кінця
	int priceLicense; //ціна на ліцензію

public:
	Company(string n, string h, int p) { //конструктор
		nameOfCompany = n;
		history = h;
		priceLicense = p;
	}

	void obchyslennya(string spisokTechnology[4]);//функція для обчислення часу та коштів


	~Company() { //деструктор
		cout << "Destroyed." << endl;
	}
};
