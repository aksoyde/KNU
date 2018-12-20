#include "K_Heap.h"

// Restores a given node up in the heap. This is used 
// in decreaseKey() and insert() 
void K_Heap::restoreUp(int index)
{
	// parent stores the index of the parent variable of the node 
	int parentIndex = parent(index);

	// Loop should only run till root node in case the 
	// element inserted is the maximum restore up will 
	// send it to the root node 
	while (parentIndex >= 0)
	{
		if (arr[index] > arr[parentIndex])
		{
			swap(arr[index], arr[parentIndex]);
			index = parentIndex;
			parentIndex = parent(index);
		}
		// node has been restored at the correct position 
		else
			break;
	}
}

//function to heapify (or restore the max- heap property). This is used to build a k-ary 
//heap and in extractMin(), index -- index of element to be restored (or heapified) 
void K_Heap::restoreDown(int index)
{
	// child array to store indexes of all 
	// the children of given node 
	vector<int> child(k + 1);

	while (1)
	{
		// child[i]=-1 if the node is a leaf 
		// children (no children) 
		for (int i = 1; i <= k; i++)
			child[i] = ((k*index + i) < n) ? (k*index + i) : -1;

		// max_child stores the maximum child and 
		// max_child_index holds its index 
		int max_child = -1, max_child_index;

		// loop to find the maximum of all 
		// the children of a given node 
		for (int i = 1; i <= k; i++)
		{
			if (child[i] != -1 && arr[child[i]] > max_child)
			{
				max_child_index = child[i];
				max_child = arr[child[i]];
			}
		}

		// leaf node 
		if (max_child == -1)
			break;

		// swap only if the key of max_child_index 
		// is greater than the key of node 
		if (arr[index] < arr[max_child_index])
			swap(arr[index], arr[max_child_index]);

		index = max_child_index;
	}
}

void K_Heap::increaseKey(int index, int newVal)
{
	if (arr[index] < newVal)
	{
		arr[index] = newVal;
		restoreUp(index);
	}
}

void K_Heap::Print()
{
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
}

// Function that returns the key of root node of 
// the heap and then restores the heap property 
// of the remaining nodes 
int K_Heap::extractMax()
{
	// Stores the key of root node to be returned 
	int max = arr[0];

	// Copy the last node's key to the root node 
	arr[0] = arr[n - 1];

	// Decrease heap size by 1 
	n = n - 1;

	// Call restoreDown on the root node to restore 
	// it to the correct position in the heap 
	restoreDown(0);

	return max;
}

// Function to insert a value in a heap. Parameters are 
// the array, size of heap, value k and the element to 
// be inserted 
void K_Heap::insert(int elem)
{
	// Put the new element in the last position 
	arr[n] = elem;

	// Increase heap size by 1 
	n = n + 1;

	// Call restoreUp on the last index 
	restoreUp(n - 1);
}

// Function to build a heap of arr[0..n-1] and children's value of k.
//with max size = capacity;
K_Heap::K_Heap(int * arr, int capacity, int n, int k)
{
	this->n = n;
	this->k = k;
	this->capacity = capacity;
	this->arr = new int[n];
	for (int i = 0; i < n; i++)
		this->arr[i] = arr[i];

	// Heapify all internal nodes starting from last 
	// non-leaf node all the way upto the root node 
	// and calling restore down on each 
	for (int i = (n - 1) / k; i >= 0; i--)
		restoreDown(i);
}

K_Heap::K_Heap()
{
}


K_Heap::~K_Heap()
{
	if(arr)
		delete[] arr;
}
