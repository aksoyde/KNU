
#include <iostream>
#include <algorithm>
#include "Header.h"
using namespace std;

struct subdivision;

struct workers {
	string name;
	double salary;
	subdivision* type;
};
struct subdivision {
	string name;
	vector<workers*> workers;
	subdivision(string name) :name(name) {}
	subdivision() {}
};


void read_from_file(string name, vector<subdivision>& subdivisions) {
	ifstream fin(name);

	int cnt_subdivisions;
	fin >> cnt_subdivisions;


	subdivisions.resize(cnt_subdivisions);//вектр в котором хранятся категории
	for (int i = 0; i < cnt_subdivisions; i++) {
		int n; // n - numer of workers in current subdivision
		fin >> subdivisions[i].name >> n;//считываем название категорие и количество элементов в ней
		cout << subdivisions[i].name << " " << n << endl;
		subdivisions[i].workers.resize(n);
		for (int j = 0; j < n; j++) {

			subdivisions[i].workers[j] = new workers;
			getline(fin, subdivisions[i].workers[j]->name);
			subdivisions[i].workers[j]->type = &subdivisions[i];
			subdivisions[i].workers[j]->salary = (int)(rand() % 1000 + 1) / 100.;//salary
			cout << subdivisions[i].workers[j]->name << endl;
		}
	}

	fin.close();

}

int main() {
	BPlusTree<double, string> tree(2);

	vector<subdivision>  subdivisions;
	read_from_file("HR.txt", subdivisions);

	//building tree

	random_shuffle(subdivisions[0].workers.begin(), subdivisions[0].workers.end());
	for (int i = 1; i < 15; i++) {
		tree.insert(subdivisions[0].workers[i]->salary, subdivisions[0].workers[i]->name);

	}
	tree.insert(5.15, "ss");
	tree.insert(7.15, "kk");
	tree.writeToFile("file4.txt");

	return 0;
}


