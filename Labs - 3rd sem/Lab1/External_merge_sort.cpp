// C++ program to implement external sorting using  
// merge sort
#define _CRT_SECURE_NO_WARNINGS
#include"MinHeap.h"
#include<cstdio>
#include<vector>
#include<ctime>
#include<algorithm>
using std::vector;
using std::sort;


// Merges k sorted files.  Names of files are assumed 
// to be 1, 2, 3, ... k 
void mergeFiles(char *output_file, int n, int k);

// Using a sort algorithm, create the initial runs 
// and divide them evenly among the output files 
void createInitialRuns(char *input_file, int run_size, int num_ways);

// Function for sorting data stored on disk(union of Merge K Sorted Arrays and dividing into runs
void externalSort(char* input_file, char *output_file, int num_ways, int run_size);

// Driver program to test above 
int main()
{
	srand(time(NULL));
	char input_file[] = "input.txt";
	char output_file[] = "output.txt";

	// The size of each partition 
	int run_size = 300;

	// No. of Partitions of input file. 
	int num_ways = 10;

	FILE* in = fopen(input_file, "w");
	// generate input 
	for (int i = 0; i < run_size*num_ways; i++)
		fprintf(in, "%d ", rand());
	fclose(in);

	externalSort(input_file, output_file, num_ways, run_size);

	system("pause");
	return 0;
}

void mergeFiles(char *output_file, int n, int k)
{
	vector<FILE*> in(k);
	for (int i = 0; i < k; i++)
	{
		char fileName[2];

		// convert i to string 
		snprintf(fileName, sizeof(fileName), "%d", i);

		// Open output files in read mode. 
		in[i] = fopen(fileName, "r");
	}

	// FINAL OUTPUT FILE 
	FILE *out = fopen(output_file, "w");

	// Create a min heap with k heap nodes.  Every heap node 
	// has first element of scratch output file 
	MinHeapNode* harr = new MinHeapNode[k];
	int i;
	for (i = 0; i < k; i++)
	{
		// break if no output file is empty and 
		// index i will be no. of input files 
		if (fscanf(in[i], "%d ", &harr[i].element) != 1)
			break;

		harr[i].i = i; // Index of scratch output file 
	}
	MinHeap hp(harr, i); // Create the heap 

	int count = 0;

	// Now one by one get the minimum element from min 
	// heap and replace it with next element. 
	// run till all filled input files reach EOF 
	while (count != i)
	{
		// Get the minimum element and store it in output file 
		MinHeapNode root = hp.getMin();
		fprintf(out, "%d ", root.element);

		// Find the next element that will replace current 
		// root of heap. The next element belongs to same 
		// input file as the current min element. 
		if (fscanf(in[root.i], "%d ", &root.element) != 1)
		{
			root.element = INT_MAX;
			count++;
		}

		// Replace root with next element of input file 
		hp.replaceMin(root);
	}

	// close input and output files 
	for (int i = 0; i < k; i++)
		fclose(in[i]);

	fclose(out);
}

void createInitialRuns(char *input_file, int run_size, int num_ways)
{
	// For big input file 
	FILE *in = fopen(input_file, "r");

	// output scratch files 
	vector<FILE*> out(num_ways);
	char fileName[2];
	for (int i = 0; i < num_ways; i++)
	{
		// convert i to string 
		snprintf(fileName, sizeof(fileName), "%d", i);
		
		// Open output files in write mode. 
		out[i] = fopen(fileName, "w");
	}

	// allocate a dynamic array large enough 
	// to accommodate runs of size run_size 
	int* arr = new int[run_size];

	bool more_input = true;
	int next_output_file = 0;

	int i;
	while (more_input)
	{
		// write run_size elements into arr from input file 
		for (i = 0; i < run_size; i++)
		{
			if (fscanf(in, "%d ", &arr[i]) != 1)
			{
				more_input = false;
				break;
			}
		}

		// sort array
		sort(arr, arr + i);

		// write the records to the appropriate scratch output file 
		// can't assume that the loop runs to run_size 
		// since the last run's length may be less than run_size 
		for (int j = 0; j < i; j++)
			fprintf(out[next_output_file], "%d ", arr[j]);

		next_output_file++;
	}

	// close input and output files 
	for (int i = 0; i < num_ways; i++)
		fclose(out[i]);

	fclose(in);
}

void externalSort(char* input_file, char *output_file, int num_ways, int run_size)
{
	// read the input file, create the initial runs, 
	// and assign the runs to the scratch output files 
	createInitialRuns(input_file, run_size, num_ways);

	// Merge the runs using the K-way merging 
	mergeFiles(output_file, run_size, num_ways);
}