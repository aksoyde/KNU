#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class Technology { //базовий клас (абстрактний)
public: //оголошення віртуальних функцій, які будуть використовуватись в похідному класі
	string title[10]; //назва технологій.
	int time;
	int money;
	int price;

	virtual void obchyslennya(string spisokTechnology[]) = 0; //віртуальна функція для обчислення часу та коштів
	Technology();
	~Technology();
};
