#include <iostream>
#include <vector>
#include<fstream>
#include<queue>
#include<string>
using namespace std;
template <class T, class Other>
struct node {
	T data;
	Other other;
	node* left;
	node* right;
	node* parent;
	node(T data, Other other) : data(data), other(other), left(nullptr), right(nullptr), parent(nullptr) {}
};
template <class T, class Other>
struct splay_tree {
	node<T, Other>* root = nullptr;
	void splay(node<T, Other>*);
	void merge(splay_tree);
	pair <splay_tree, splay_tree> split(node<T, Other>*);
	void add_default(T, Other);
	void remove(T);
	bool search(T);
	node<T, Other>* find(T);
	void left_rotate(node<T, Other>*);
	void right_rotate(node<T, Other>*);
	void add(T, Other);
	Other search_elem(T);
};
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

template <class T, class Other>
void splay_tree<T, Other>::add_default(T x, Other other) {

	node<T, Other>* pointer = root;
	node<T, Other>* parent = nullptr;
	if (!pointer) {

		root = new node<T, Other>(x, other);
		return;
	}
	while (pointer) {
		parent = pointer;
		if (pointer->data > x) {
			pointer = pointer->left;
		}
		else {
			pointer = pointer->right;
		}
	}
	if (parent->data > x) {
		parent->left = new node<T, Other>(x, other);
		parent->left->parent = parent;//у левого сына отец это отец это отец
	}
	else {
		parent->right = new node<T, Other>(x, other);
		parent->right->parent = parent;
	}


}
template <class T, class Other>
bool splay_tree<T, Other>::search(T x) {
	node<T, Other>* pointer = root;
	while (pointer) {
		if (x == pointer->data) {
			return true;
		}
		if (pointer->data > x) {
			pointer = pointer->left;
		}
		else {
			pointer = pointer->right;
		}
	}
	return false;
}

template <class T, class Other>
Other splay_tree<T, Other>::search_elem(T x) {
	node<T, Other>* pointer = root;
	while (pointer) {
		if (x == pointer->data) {
			splay(pointer);
			return pointer->other;
		}
		if (pointer->data > x) {
			pointer = pointer->left;
		}
		else {
			pointer = pointer->right;
		}
	}
	return 0;
}


template <class T, class Other>
void splay_tree<T, Other>::add(T x, Other other) {
	add_default(x, other);
	node<T, Other>* x_pointer = find(x);
	// pair<splay_tree,splay_tree> s = split(x_pointer);
	splay(x_pointer);
}
template <class T, class Other>
void splay_tree<T, Other>::right_rotate(node<T, Other>* x) {
	node<T, Other>* tmp = x->left;
	x->left = tmp->right;
	if (tmp->right)tmp->right->parent = x;
	tmp->right = x;
	tmp->parent = x->parent;
	x->parent = tmp;
	if (tmp->parent) {
		if (tmp->parent->left == x) {
			tmp->parent->left = tmp;
		}
		else {
			tmp->parent->right = tmp;
		}
	}
}

template <class T, class Other>
void splay_tree<T, Other>::left_rotate(node<T, Other>* x) {
	node<T, Other>* tmp = x->right;
	x->right = tmp->left;
	if (tmp->left)tmp->left->parent = x;
	tmp->left = x;
	tmp->parent = x->parent;
	x->parent = tmp;
	if (tmp->parent) {
		if (tmp->parent->left == x) {
			tmp->parent->left = tmp;
		}
		else {
			tmp->parent->right = tmp;
		}
	}
}
template <class T, class Other>
void splay_tree<T, Other>::splay(node<T, Other>* x) {
	while (x != root) {
		if (x->parent == root) {

			if (x->parent->left == x) {//zig
				right_rotate(x->parent);
			}
			else {//zag
				left_rotate(x->parent);
			}
			root = x;
			return;
		}
		node<T, Other>* p = x->parent;
		node<T, Other>* g = p->parent;
		if (g == root) {
			root = x;
		}
		if (p->left == x && g->left == p) {//zig-zig
			right_rotate(p);
			right_rotate(g);
			continue;
		}
		if (p->right == x && g->right == p) {//zag-zag
			left_rotate(p);
			left_rotate(g);
			continue;
		}
		if (g->left == p && p->right == x) {//zig-zag
			left_rotate(p);
			right_rotate(g);
			continue;
		}
		if (g->right == p && p->left == x) {//zag-zig
			right_rotate(p);
			left_rotate(g);
			continue;
		}
	}
}
template <class T, class Other>
void splay_tree<T, Other>::merge(splay_tree b) {
	node<T, Other>* max = root;
	while (max->right) {
		max = max->right;
	}
	splay(max);
	root->right = b.root;
}

template <class T, class Other>
pair<splay_tree<T, Other>, splay_tree<T, Other> > splay_tree <T, Other>::split(node<T, Other>* x) {
	splay(x);
	splay_tree a;
	splay_tree b;

	b.root = x->right;
	b.root->parent = nullptr;
	a.root = x;
	x->right = nullptr;

	return { a,b };
}
template <class T, class Other>
node<T, Other>* splay_tree<T, Other>::find(T x) {
	node<T, Other>* pointer = root;
	while (pointer) {
		if (x == pointer->data) {
			return pointer;
		}
		if (pointer->data > x) {
			pointer = pointer->left;
		}
		else {
			pointer = pointer->right;
		}
	}
	return nullptr;
}
template <class T, class Other>
void splay_tree<T, Other>::remove(T x) {

	node<T, Other>* pointer = find(x);
	if (!pointer) {
		return;
	}
	if (!pointer->left && !pointer->right) {
		if (pointer == root) {
			delete pointer;
			root = nullptr;
			return;
		}
		if (pointer == pointer->parent->left) {
			pointer->parent->left = nullptr;
		}
		else {
			pointer->parent->right = nullptr;
		}
		delete pointer;
		return;
	}

	if (!pointer->right && pointer->left) {
		if (pointer == root) {
			root = pointer->left;
			delete pointer;
			return;
		}

		if (pointer == pointer->parent->left) {

			pointer->parent->left = pointer->left;
		}
		else {
			pointer->parent->left = pointer->right;
		}
		pointer->left->parent = pointer->parent;
		delete pointer;
		return;
	}
	if (!pointer->left && pointer->right) {
		if (pointer == root) {
			root = pointer->right;
			delete pointer;
			return;
		}
		if (pointer == pointer->parent->left) {
			pointer->parent->left = pointer->right;
		}
		else {
			pointer->parent->right = pointer->right;
		}
		pointer->right->parent = pointer->parent;
		delete pointer;
		return;
	}

	node<T, Other>* theleftest = pointer->right;
	while (theleftest->left) {
		theleftest = theleftest->left;

	}
	int new_data = theleftest->data;
	remove(new_data);
	pointer->data = new_data;
}
void read_from_file(string name, vector<subdivision>& subdivisions) {
	ifstream fin(name);

	int cnt_subdivision;
	fin >> cnt_subdivision;

	subdivisions.resize(cnt_subdivision);//вектр в котором хранятся категории
	for (int i = 0; i < cnt_subdivision; i++) {
		int n; // n - numer of workers in current subdivision
		fin >> subdivisions[i].name >> n;//считываем название категорие и количество элементов в ней
		subdivisions[i].workers.resize(n);
		for (int j = 0; j < n; j++) {

			subdivisions[i].workers[j] = new worker;
			getline(fin, subdivisions[i].workers[j]->name);
			subdivisions[i].workers[j]->type = &subdivisions[i];
			subdivisions[i].workers[j]->salary = (int)(rand() % 1000 + 1) / 100.;//salary
			cout << subdivisions[i].workers[j]->name << endl;
		}
	}

	fin.close();

}
int main(int argc, const char* argv[]) {
	vector<subdivision>  subdivisions;
	read_from_file("HR.txt", subdivisions);

	//building tree
	splay_tree<string, worker*> sp_tree;
	for (auto subd : subdivisions) {
		for (int i = 1; i < subd.workers.size(); i++) {
			sp_tree.add(subd.workers[i]->name, subd.workers[i]);

		}
	}


	while (true) {
		string name;
		cin >> name;
		if (sp_tree.search(name)) {
			worker* result = sp_tree.search_elem(name);

			cout << result->name << ' ' << result->type->name << ' ' << result->salary << endl;
			cout << sp_tree.root->other->name << endl;
			ofstream fout("file.txt");
			queue<node<string, worker*>* > q;
			q.push(sp_tree.root);
			while (!q.empty()) {
				node<string, worker*>* tmp = q.front();
				q.pop();

				if (tmp->left) {
					fout << "\"" << tmp->data << "\"-> \"" << tmp->left->data << "\"" << endl;
					q.push(tmp->left);
				}
				if (tmp->right) {
					fout << "\"" << tmp->data << "\"-> \"" << tmp->right->data << "\"" << endl;
					q.push(tmp->right);
				}
			}


		}
		else {
			cout << "No worker with such name" << endl;
		}

	}
	return 0;
}
