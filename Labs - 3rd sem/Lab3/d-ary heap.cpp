#include"K_Heap.h"

// Driver program 
int main()
{
	const int capacity = 100;
	int arr[capacity] = { 4, 5, 6, 7, 8, 9, 10 };
	int n = 7;
	int k = 3;

	K_Heap heap = K_Heap(arr, capacity, n, k);

	printf("Built Heap : \n");
	heap.Print();

	int element = 3;
	heap.insert(element);

	printf("\n\nHeap after insertion of %d: \n", element);
	heap.Print();

	printf("\n\nExtracted max is %d", heap.extractMax());

	printf("\n\nHeap after extract max: \n");
	heap.Print();

	printf("\n");
	system("pause");
	return 0;
}