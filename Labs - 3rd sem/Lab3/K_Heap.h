#pragma once
#include<iostream>
#include<vector>
using std::vector;
using std::swap;
class K_Heap
{
private:
	int *arr;
	int capacity;
	int n;
	int k;
	void restoreUp(int index);
	void restoreDown(int index);
	int parent(int index) { return (index - 1) / k; }
public:
	void increaseKey(int index, int newVal);
	void Print();
	int extractMax();
	void insert(int elem);
	K_Heap(int *arr, int capacity, int n, int k);
	K_Heap();
	~K_Heap();
};

