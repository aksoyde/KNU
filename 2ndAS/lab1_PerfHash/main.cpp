#include <iostream>
#include <algorithm>
#include <time.h>
#include <vector>
#include <list>
#include <fstream>
#include <cstring>

using namespace std;

template<class T>
int hash_function(int a, int b, int p, int m, T x) {//first level

	std::hash<T> hash_fn;
	size_t tmp = hash_fn(x) % p;

	int hash = ((a * tmp + b) % p) % m;
	return hash;
}

template<class T, class Other>
struct perfect_hash_table {
public:
	vector < vector< vector < pair<T, Other> > >  >ideal_table;//create ideal table
	vector<int>prmtr1;//parametr a for the second level fo rthe ideal table
	vector<int>prmtr2;//parametr b for the second level fo rthe ideal table

	int a, b, p = 107, m;

	vector <vector <  pair<T, Other> >  >hash_table;

	void first_level_hash(vector<pair<T, Other> >& value, int cnt) {//function that calculate elements hash on the first level

		a = rand() % (p - 1) + 1;
		b = rand() % p;
		m = cnt;

		for (int i = 0; i < m; i++) {
			int hsh = hash_function(a, b, p, m, value[i].first);//find hash of initial values
			hash_table[hsh].push_back(value[i]);

		}
	}

	void second_level_hash() {//function that calculate elements hash on the second level
		for (int i = 0; i < m; i++) {

			prmtr1[i] = rand() % (p - 1) + 1;
			prmtr2[i] = rand() % p;

			int size = (int)hash_table[i].size();
			ideal_table[i].resize(size * size);

		}

		for (int i = 0; i < m; i++) {
			for (auto value : hash_table[i]) {
				int second_level_hash = hash_function(prmtr1[i], prmtr2[i], p, ideal_table[i].size(), value.first);
				ideal_table[i][second_level_hash].push_back(value);
			}
			hash_table[i].clear();
		}
	}

	perfect_hash_table(vector<pair<T, Other> >& value) {

		int m = (int)value.size();//counts of  elements in vector

		ideal_table.resize(m);
		prmtr1.resize(m);
		prmtr2.resize(m);
		hash_table.resize(m);

		first_level_hash(value, m);
		second_level_hash();
	}

	bool search(T key) {
		int first_level = hash_function(a, b, p, m, key);
		int second_level = hash_function(prmtr1[first_level], prmtr2[first_level], p, ideal_table.size(), key);
		return (ideal_table[first_level].size() && ideal_table[first_level][second_level] == key);

	}


};

struct subdivision;

struct worker {
	string name;
	int salary;
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
		cout << subdivisions[i].name << " " << n << endl;
		subdivisions[i].workers.resize(n);
		for (int j = 0; j < n; j++) {

			subdivisions[i].workers[j] = new worker;
			cin.getline (fin, subdivisions[i].workers[j]->name);
			subdivisions[i].workers[j]->type = &subdivisions[i];
			subdivisions[i].workers[j]->salary = rand() % 10 + 1;//salary

		}
	}

	fin.close();

}

int main(int argc, const char* argv[]) {

	int a, b, p = 107, m = 100;
	srand((int)time(0));

	vector<subdivision>  subdivisions;
	read_from_file("HR.txt", subdivisions);

	vector<pair<string, subdivision*> > tmp1;
	for (int i = 0; i < subdivisions.size(); i++) {
		tmp1.push_back({ subdivisions[i].name, &subdivisions[i] });
	}


	perfect_hash_table<string, subdivision*> table1(tmp1); // hash data by name of subdivisions

	vector<pair<int, worker* > >tmp2;//hash data by salary
	for (int i = 0; i < subdivisions.size(); i++) {
		for (int j = 0; j < subdivisions[i].workers.size(); j++) {
			tmp2.push_back({ subdivisions[i].workers[j]->salary,subdivisions[i].workers[j] });
		}
	}

	perfect_hash_table<int, worker*> table2(tmp2); // hash data by name of subdivisions

	vector<pair<string, worker* > >tmp3;//hash data by salary
	for (int i = 0; i < subdivisions.size(); i++) {
		for (int j = 0; j < subdivisions[i].workers.size(); j++) {
			tmp3.push_back({ subdivisions[i].workers[j]->name,subdivisions[i].workers[j] });
		}
	}

	perfect_hash_table<string, worker*> table3(tmp3); // hash data by name of subdivisions

	while (true) {

		cout << "1) - Search by subdivision" << endl;
		cout << "2) - Search by salary" << endl;
		cout << "3) - Search by worker" << endl;
		cout << "4) - Exit" << endl;
		int t;
		cin >> t;
		if (t == 1) {
			string name;
			cin >> name;

			int first_level = hash_function(table1.a, table1.b, table1.p, table1.m, name);
			if (table1.ideal_table[first_level].size() == 0) {
				cout << "No workers with such subdivision" << endl;
				continue;
			}
			int second_level = hash_function(table1.prmtr1[first_level], table1.prmtr2[first_level], table1.p, table1.ideal_table[first_level].size(), name);

			if (table1.ideal_table[first_level][second_level].size() == 0) {
				cout << "No workers in such subdivision" << endl;
			}
			else {
				for (auto subd : table1.ideal_table[first_level][second_level]) {
					if (subd.first == name) {
						cout << subd.second->workers.size() << endl;
						for (int i = 0; i < subd.second->workers.size(); i++) {
							cout << subd.second->workers[i]->name << " " << subd.second->workers[i]->salary << endl;
						}
					}
				}
			}
		}
		if (t == 2) {
			int salary;
			cin >> salary;

			int first_level = hash_function(table2.a, table2.b, table2.p, table2.m, salary);
			if (table2.ideal_table[first_level].size() == 0) {
				cout << "No workers with such salary" << endl;
				continue;
			}
			int second_level = hash_function(table2.prmtr1[first_level], table2.prmtr2[first_level], table2.p, table2.ideal_table[first_level].size(), salary);

			if (table2.ideal_table[first_level][second_level].size() == 0) {
				cout << "No workers with such salary" << endl;
			}
			else {
				for (auto workr : table2.ideal_table[first_level][second_level]) {
					if (workr.second->salary == salary) {
						cout << workr.second->name << ' ' << workr.second->type->name << endl;
					}

				}
			}
		}
		if (t == 3) {
			string name;
			cin >> name;

			int first_level = hash_function(table3.a, table3.b, table3.p, table3.m, name);
			if (table3.ideal_table[first_level].size() == 0) {
				cout << "No such worker" << endl;
				continue;
			}
			int second_level = hash_function(table3.prmtr1[first_level], table3.prmtr2[first_level], table3.p, table3.ideal_table[first_level].size(), name);

			if (table3.ideal_table[first_level][second_level].size() == 0) {
				cout << "No such worker" << endl;
			}
			else {
				for (auto prod : table3.ideal_table[first_level][second_level]) {
					if (prod.first == name) {
						cout << prod.second->name << " " << prod.second->type->name << " " << prod.second->salary << endl;

					}
				}
			}
		}
		if (t == 4) { return 0; }
	}


}


