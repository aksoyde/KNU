#include "Company.h"

void Company::obchyslennya(string spisokTechnology[4]) { //функція для обчислення часу та коштів
	int randTime = 0, randMoney = 0;
	int avTime = 0, avMoney = 0;

	for (int i = 0; i < 4; i++) {
		randTime = rand() % 24; //отримуємо випадкове значення часу
		randMoney = rand() % 1000 + 100; //отримуємо випадкове коштів

		avTime += randTime;
		avMoney += randMoney;
	}
	avMoney += priceLicense; //додаємо до суми ліцензію

	cout << "Назва: " << nameOfCompany << endl;
	cout << "Загальны вытраты компаныъ: " << avMoney << endl;
	cout << "Час: " << avTime << endl;

	cout << "Список технологый: " << endl;

	for (int j = 0; j < 4; j++) { //виводимо список технологій
		cout << j + 1 << " " << spisokTechnology[j] << endl;
	}
}
