#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "redblack.h"

struct subdivision;

struct worker {
	string name;
	double salary;
	subdivision* type;
};
struct subdivision {
	string name;
	vector<worker*> workers;
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

		subdivisions[i].workers.resize(n);
		for (int j = 0; j < n; j++) {

			subdivisions[i].workers[j] = new worker;
			getline(fin, subdivisions[i].workers[j]->name);
			subdivisions[i].workers[j]->type = &subdivisions[i];
			subdivisions[i].workers[j]->salary = (int)(rand() % 1000 + 1) / 100.;//salary

		}
	}

	fin.close();

}


int main(int argc, const char* argv[]) {
	// insert code here...

	vector<subdivision>  subdivisions;
	read_from_file("HR.txt", subdivisions);

	//building tree
	redblack<double, worker*> statistic_tree;
	for (auto subd : subdivisions) {
		for (int i = 0; i < subd.workers.size(); i++) {
			statistic_tree.insert_to_tree(subd.workers[i]->salary, subd.workers[i]);

		}
	}

	statistic_tree.fix(statistic_tree.root);
	int k;
	cout << "There are " << statistic_tree.size() << " different workers" << endl;
	statistic_tree.print(statistic_tree.root);

	while (true) {
		cin >> k;
		Node<double, worker*>* elem = statistic_tree.search_by_rank(k, statistic_tree.root);
		if (!elem) {
			cout << "There is no worker with such rating" << endl;
			continue;
		}
		cout << elem->other->name << " " << elem->other->salary << " " << elem->other->type->name << endl;
	}
	return 0;
}
