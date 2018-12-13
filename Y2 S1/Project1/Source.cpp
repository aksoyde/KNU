#include "Company.h"

int main()
{
	setlocale(0, ""); //для використання кирилиці в консолі

	string spisokTechnology[4] = { "Techno 1", "Techno 2","Techno 3","Techno 4"};

	Company * p[2]; //створити масив покажчиків
	Company obj1("BMW", "11/02/2016 - 14/05/2018", 240); //об'єкт класу
	Company obj2("IBM", "01/03/2017 - 12/06/2018", 520);
	Company obj3("DOC", "05/09/2015 - 01/12/2018", 1200);

	p[0] = &obj1; //запис показчиків до масиву
	p[1] = &obj2;
	p[2] = &obj3;


	for (int i = 0; i < 3; i++) { //за допомогою циклу викликаємо відповідні методи
		cout << "/--------------------------------------------/" << endl;
		p[i]->obchyslennya(spisokTechnology);
		cout << endl;
	}

	system("pause"); //затримати консоль
	return 0;
}