#include <iostream>
#include<vector>
#include <fstream>
#include <iomanip>
#include <queue>
#include<string>

using namespace std;
double max = 1e9;

template <class T, class Other>
struct node {
	Other other;
	node* left;
	node* right;
	T data;
	node(T data, Other other) : data(data), other(other), left(nullptr), right(nullptr) {}
};
template <class T, class Other>
struct optimal_tree {
	node<T, Other>* root;
	void add(T data, Other other);
	bool search(T data);
	Other  find(T data);
	void save_to_file();
	optimal_tree() : root(nullptr) {}
};



template <class T, class Other>
void optimal_tree<T, Other>::add(T data, Other other) {//function that add ellement to tree
	if (!root) {
		root = new node<T, Other>(data);
		return;
	}
	node <T, Other>* pointer = root;
	node <T, Other>* parent = nullptr;
	while (pointer) {
		parent = pointer;
		if (pointer->data > data) {
			pointer = pointer->left;
		}
		else {
			pointer = pointer->right;
		}
	}
	if (parent->data > data) {
		parent->left = new node<T, Other>(data, other);
	}
	else {
		parent->right = new node<T, Other>(data, other);
	}
}
template <class T, class Other>
bool optimal_tree <T, Other>::search(T data) {//function which finds  element
	if (!root) {
		return false;
	}
	node <T, Other>* pointer = root;
	while (pointer) {
		if (pointer->data == data) {
			return true;
		}
		if (pointer->data < data) {
			pointer = pointer->right;
		}
		else {
			pointer = pointer->left;
		}
	}
	return false;
}


template <class T, class Other>
Other optimal_tree <T, Other>::find(T data) {//function which finds  element
	if (!root) {
		return 0;
	}
	node <T, Other>* pointer = root;
	while (pointer) {
		if (pointer->data == data) {
			return pointer->other;
		}
		if (pointer->data < data) {
			pointer = pointer->right;
		}
		else {
			pointer = pointer->left;
		}
	}
	return 0;

}


template <class T, class Other>
// utility function which adds elements to the tree by root array
node <T, Other>* add_optimal(int l, int r, vector<pair<T, Other> >& keys, vector<vector<int> >& root) {
	if (l > r) return nullptr;

	int m = root[l][r];

	if (l == r) return new node<T, Other>(keys[m].first, keys[m].second);

	node <T, Other>* tmp = new node<T, Other>(keys[m].first, keys[m].second);
	tmp->left = add_optimal(l, m - 1, keys, root);
	tmp->right = add_optimal(m + 1, r, keys, root);
	return tmp;
}


template <class T, class Other>
optimal_tree<T, Other> optimal_binary_tree(vector <pair<T, Other> >& keys, vector <double >& p, vector <double>& q, int n) {  //p-probbility of real keys ,q-probability of dummy keys
	double e[n + 2][n + 1];//array for calculating mathematical expectation
	vector<vector<int> > root(n + 1, vector<int>(n + 1));
	double w[n + 2][n + 1];//aray for calculating
	cout << fixed << setprecision(2);
	for (int i = 1; i <= n + 1; i++) {
		e[i][i - 1] = q[i - 1];
		w[i][i - 1] = q[i - 1];

	}
	for (int l = 1; l <= n; l++) {
		for (int i = 1; i <= n - l + 1; i++) {
			int j = i + l - 1;
			e[i][j] = 100000;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for (int r = i; r <= j; r++) {
				double k = e[i][r - 1] + e[r + 1][j] + w[i][j];//formula which help us calculating math expactation

				if (k < e[i][j]) {
					e[i][j] = k;
					root[i][j] = r;
				}
			}
		}

	}
	cout << "root array:" << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << root[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "mathematical expectation array:" << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << e[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << p[i] << " ";
	}
	cout << endl;
	optimal_tree<T, Other> result;
	result.root = add_optimal(1, n, keys, root);
	return result;
}
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

	vector<subdivision>  subdivisions;
	read_from_file("HR.txt", subdivisions);



	vector<pair<string, worker*> > keys;


	vector<double> p, q;
	vector<int> freq;
	int n = 10;

	for (int i = 0; i <= n; i++) {
		keys.push_back({ subdivisions[0].workers[i]->name, subdivisions[0].workers[i] });
		p.push_back(1. / n);
		q.push_back(0);
		freq.push_back(1);
	}

	sort(keys.begin(), keys.end());
	for (auto el : keys) {
		cout << el.first << endl;
	}

	cout << endl;
	optimal_tree<string, worker*> bst;
	string name;
	int k = 0, f = n;
	int r = 6;
	while (true) {
		if (k == 0) {
			for (int i = 0; i <= n; i++) {
				p[i] = (double)freq[i] / f;
			}

			bst = optimal_binary_tree(keys, p, q, n);

			ofstream fout("file.txt");
			queue<node<string, worker*>* > q;
			q.push(bst.root);
			while (!q.empty()) {
				node<string, worker*>* tmp = q.front();
				q.pop();

				if (tmp->left) {
					int p_1 = 0, p_2 = 0;
					for (int i = 0; i <= n; ++i) {
						if (tmp->data == keys[i].first)p_1 = freq[i];
						if (tmp->left->data == keys[i].first)p_2 = freq[i];
					}
					fout << "\"" << tmp->data << " | " << p_1 - 1 << "\"-> \"" << tmp->left->data << " | " << p_2 - 1 << "\"" << endl;
					q.push(tmp->left);
				}
				if (tmp->right) {
					int p_1 = 0, p_2 = 0;
					for (int i = 0; i <= n; ++i) {
						if (tmp->data == keys[i].first)p_1 = freq[i];
						if (tmp->right->data == keys[i].first)p_2 = freq[i];
					}
					fout << "\"" << tmp->data << " | " << p_1 - 1 << "\"-> \"" << tmp->right->data << " | " << p_2 - 1 << "\"" << endl;

					q.push(tmp->right);
				}
			}


		}

		cin >> name;
		if (!bst.search(name)) {
			cout << "not found" << endl;
		}
		else {
			worker* pr = bst.find(name);
			cout << pr->name << " " << pr->salary << endl;
			for (int i = 0; i <= n; ++i) {
				if (name == keys[i].first)freq[i] ++;
			}
			f++;
		}
		k++;

		k %= r;
	}

	return 0;
}
