#include "MinHeap.h"

// Constructor: Builds a heap from a given array a[] 
// of given size 
MinHeap::MinHeap(MinHeapNode a[], int size)
{
	heap_size = size;
	harr = a; // store address of array 
	int i = (heap_size - 1) / 2;
	while (i >= 0)
	{
		MinHeapify(i);
		i--;
	}
}
// A recursive method to heapify a subtree with root at given index 
// This method assumes that the subtrees are already heapified 
void MinHeap::MinHeapify(int i)
{
	int l = left(i), r = right(i);
	int smallest = i;

	if (l < heap_size && harr[l].element < harr[i].element)
		smallest = l;
	if (r < heap_size && harr[r].element < harr[smallest].element)
		smallest = r;
	if (smallest != i)
	{
		swap(harr[i], harr[smallest]);
		MinHeapify(smallest);
	}
}

void MinHeap::replaceMin(MinHeapNode x)
{
	harr[0] = x;
	MinHeapify(0);
}

MinHeap::MinHeap()
{
}
MinHeap::~MinHeap()
{

}

