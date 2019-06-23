#ifndef redblack_h

#define redblack_h

#include <iostream>
#include <string>
	
using namespace std;

template <class T, class Other>//то по чем строимЁ+привязанные данные
struct Node {
	T key;
	Other other;
	Node* left;
	Node* right;
	Node* parent;
	int size = 0;
	Node* grandfather() {
		return parent->parent;
	};
	Node* uncle() {
		if (parent->parent->left == parent) {
			return parent->parent->right;
		}
		return parent->parent->left;
	};

	bool color;//true=red,false=black
	Node() :left(nullptr), right(nullptr), parent(nullptr) {}
	Node(T key, Other other, bool color = false, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr) :key(key), other(other), color(color), left(left), right(right), parent(parent), size(0) {}
};

template <class T, class Other>
struct redblack {
private:
	void left_rotate(Node<T, Other >* x);
	void right_rotate(Node<T, Other>* x);
	void insert_fix(Node<T, Other>* x);
	void delete_from_tree(Node<T, Other>* x);//
	void transplant(Node <T, Other>* x, Node <T, Other>* y);
	void fix_delete(Node<T, Other>* x);

	Node <T, Other>* nil;
	Node<T, Other>* search_key(T);

public:
	void fix(Node <T, Other>* x);
	Node <T, Other>* search_by_rank(int r, Node<T, Other>* x);
	Node <T, Other>* root;
	void print(Node<T, Other>* x);
	redblack() {
		nil = new Node<T, Other>();
		nil->color = false;
		root = nil;
	}
	void insert_to_tree(T, Other);
	void delete_from_tree(T);

	bool search(T);
	Other get_by_key(T);
	int size() {
		return root->size;
	}
};

template <class T, class Other>
void redblack<T, Other>::print(Node<T, Other>* x) {
	if (x == nil) return;
	if (x->left->key) {
		cout << "\"" << x->other->name << " | " << x->size << "\"" << " -> " << "\"" << x->left->other->name << " | " << x->left->size << "\"" << endl;
	}
	if (x->right->key) {
		cout << "\"" << x->other->name << " | " << x->size << "\"" << " -> " << "\"" << x->right->other->name << " | " << x->right->size << "\"" << endl;
	}
	print(x->left);
	print(x->right);
}

template <class T, class Other>

Node<T, Other>* redblack <T, Other>::search_by_rank(int r, Node<T, Other>* x) {
	if (r < 1 || x == nil)return 0;
	if (x->left->size + 1 == r) {
		return x;
	}
	if (r <= x->left->size) {
		return search_by_rank(r, x->left);
	}
	return search_by_rank(r - x->left->size - 1, x->right);
}

template <class T, class Other>

void redblack <T, Other>::insert_to_tree(T key, Other other) {
	if (root == nil) {
		root = new Node<T, Other>(key, other, false, nil, nil, nil);
		root->size = 1;
		return;
	}
	Node<T, Other>* pointer = root;
	Node<T, Other>* parent = nil;
	while (pointer != nil) {
		pointer->size++;
		parent = pointer;
		if (pointer->key > key) {
			pointer = pointer->left;

		}
		else {
			pointer = pointer->right;
		}


	}
	if (parent->key < key) {

		parent->right = new Node <T, Other>(key, other, true, nil, nil, parent);
		parent->right->size = 1;
		insert_fix(parent->right);
	}
	else {

		parent->left = new Node <T, Other>(key, other, true, nil, nil, parent);
		parent->left->size = 1;
		insert_fix(parent->left);
	}




}
template <class T, class Other>
void redblack <T, Other>::left_rotate(Node<T, Other>* x) {
	if (x == nil) return;
	Node<T, Other>* x_right = x->right;
	x_right->parent = x->parent;
	if (x_right->parent == nil) {
		root = x_right;
	}
	else {
		if (x_right->key > x_right->parent->key) {
			x_right->parent->right = x_right;//становлюсь правым ребенка своего отца
		}
		else {
			x_right->parent->left = x_right;//левым
		}
	}

	x->right = x_right->left;//перепривязываем левый дочерний узел нашего р и делаем его правым дочерним узлом м
	if (x->right != nil) {
		x->right->parent = x;//находим отца нашего с
	}
	x_right->left = x;
	x->parent = x_right;//закончили поворот сказали что м ребенок р

	x_right->size = x->size;
	x->size = x->left->size + x->right->size + 1;

}
template <class T, class Other>
void redblack <T, Other>::right_rotate(Node<T, Other>* x) {
	if (x == nil) return;
	Node<T, Other>* x_left = x->left;
	x_left->parent = x->parent;
	if (x_left->parent == nil) {
		root = x_left;
	}
	else {
		if (x_left->key > x_left->parent->key) {
			x_left->parent->right = x_left;//становлюсь правым ребенка своего отца
		}
		else {
			x_left->parent->left = x_left;//левым
		}
	}

	x->left = x_left->right;//перепривязываем левый дочерний узел нашего р и делаем его правым дочерним узлом м
	if (x->left != nil) {
		x->left->parent = x;//находим отца нашего с
	}
	x_left->right = x;
	x->parent = x_left;//закончили поворот сказали что м ребенок р

	x_left->size = x->size;
	x->size = x->left->size + x->right->size + 1;

}
template <class T, class Other>
void redblack <T, Other> ::insert_fix(Node <T, Other>* x) {
	while (x != nil && x != root && x->parent->color == true) {//1 sluchiy

		Node<T, Other>* parent = x->parent;
		Node<T, Other>* grandpa = x->parent->parent;

		if (x->grandfather() != nil && x->uncle()->color == true) {
			x->parent->color = false;
			x->grandfather()->color = true;
			x->uncle()->color = false;
			x = x->grandfather();//mu dedushka
		}
		else {
			if (x == x->parent->right) {

				if (parent == parent->parent->left) {
					left_rotate(parent);
					right_rotate(grandpa);
				}
				else {
					left_rotate(grandpa);
				}


				swap(grandpa->color, parent->color);
				x = parent;
			}
			else {// x==x->parent->left;

				if (parent == parent->parent->right) {
					right_rotate(parent);
					left_rotate(grandpa);
				}
				else {
					right_rotate(grandpa);
				}

				swap(grandpa->color, parent->color);
				x = parent;
			}

		}

	}
	root->color = false;

}

template <class T, class Other>
Node<T, Other>* redblack <T, Other>::search_key(T key) {
	Node <T, Other>* x = root;
	while (x != nil) {
		if (x->key == key) {
			return x;
		}
		if (x->key > key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	return nil;
}
template <class T, class Other>
bool redblack <T, Other> ::search(T key) {//public
	Node <T, Other>* x = search_key(key);
	if (x == nil) {
		return false;
	}
	else {
		return true;
	}

}
template <class T, class Other>
void redblack <T, Other >::transplant(Node <T, Other>* x, Node <T, Other>* y) {//замещение одной вершины другой
	if (x == root) {
		root = y;
	}
	else {
		if (x == x->parent->left) {
			x->parent->left == y;
		}
		else {
			x->parent->right = y;
		}
	}
	if (y != nil)y->parent = x->parent;//y mozhet but' pustota

}
template <class T, class Other>
void redblack <T, Other> ::delete_from_tree(Node <T, Other>* x) {//private delete
	Node <T, Other>* tmp = x;
	Node <T, Other>* newone;//запоминаем на что мы заменяем старую вершину
	bool color = x->color;//zapominaem izna4al'nui color
	if (x->left == nil) {
		newone = x->right;
		transplant(x, x->right);
	}
	else if (x->right == nil) {
		newone = x->left;
		transplant(x, x->left);//{1-3 clu4iy}
	}
	else {
		tmp = x->right;
		while (tmp->left != nil) {
			tmp = tmp->left;//poka est left son go left
		}
		color = tmp->color;
		newone = tmp->right;
		if (tmp->parent == x) {
			newone->parent = tmp;
		}
		else {
			transplant(tmp, tmp->right);
			tmp->right = x->right;
			tmp->right->parent = tmp;
		}
		transplant(x, tmp);
		tmp->left = x->left;
		tmp->left->parent = tmp;
		tmp->color = x->color;
	}
	if (color == false) {
		fix_delete(newone);
	}

}

template <class T, class Other>
void redblack <T, Other> ::fix(Node <T, Other>* x) {
	if (!x || x == nil) return;
	if (x->left == nil && x->right == nil) {
		x->size = 1;
		return;
	}
	fix(x->left);
	fix(x->right);
	x->size = x->left->size + x->right->size + 1;


}


template <class T, class Other>
void redblack <T, Other> ::fix_delete(Node <T, Other>* x) {
	Node <T, Other>* tmp;
	while (x != root && x->color == false) {
		if (x == x->parent->left) {
			tmp = x->parent->right;
			if (tmp->color == true) {
				tmp->color = false;
				x->parent->color = true;
				left_rotate(x->parent);
				tmp = x->parent->right;
			}
			if (tmp->left->color == false && tmp->right->color == false) {
				tmp->color = true;
				x = x->parent;
			}
			else if (tmp->right->color == false) {
				tmp->left->color = false;
				tmp->color = true;
				right_rotate(tmp);
				tmp = x->parent->right;
			}
			tmp->color = x->parent->color;
			x->parent->color = false;
			tmp->right->color = false;
			x = root;
		}
		else {
			tmp = x->parent->left;
			if (tmp->color == true) {
				tmp->color = false;
				x->parent->color = true;
				right_rotate(x->parent);
				tmp = x->parent->left;
			}
			if (tmp->right->color == false && tmp->left->color == false) {
				tmp->color = true;
				x = x->parent;
			}
			else if (tmp->left->color == false) {
				tmp->right->color = false;
				tmp->color = true;
				left_rotate(tmp);
				tmp = x->parent->left;
			}
			tmp->color = x->parent->color;
			x->parent->color = false;
			tmp->left->color = false;
			right_rotate(x->parent);
			x = root;
		}
	}
}
template<class T, class Other>
void redblack<T, Other>::delete_from_tree(T key) {
	delete_from_tree(search_key(key));
}
#endif /* redblack_h */
#pragma once
