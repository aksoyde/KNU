#pragma once
#include"HeapHelper.h"
#include<iostream>
using std::swap;

// A class for Min Heap
class MinHeap
{
private:
	MinHeapNode* harr; // pointer to array of elements in heap 
	int heap_size;     // size of min heap 
public:
	// Constructor: creates a min heap of given size 
	MinHeap(MinHeapNode a[], int size);

	// to heapify a subtree with root at given index 
	void MinHeapify(int);

	// to get index of left child of node at index i 
	int left(int i) { return (2 * i + 1); }

	// to get index of right child of node at index i 
	int right(int i) { return (2 * i + 2); }

	// to get the root 
	MinHeapNode getMin() { return harr[0]; }

	// to replace root with new node x and heapify() new root 
	void replaceMin(MinHeapNode x);
	MinHeap();
	~MinHeap();
};