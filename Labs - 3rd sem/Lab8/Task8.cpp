#include"StringSearch.h"
#include<iostream>
#include <chrono>
using std::chrono::high_resolution_clock;
using std::cout;
/* Driver program to test above function */
int main()
{
	char txt[] = "AABAACAADAABAAABAA";
	char pat[] = "AABA";


	cout << "Executing NaiveSearch Algorithm\n";
	auto time = high_resolution_clock::now();
	StringSearch::NaiveSearch(pat, txt);
	cout << "time= " << (high_resolution_clock::now() - time).count() << "ns\n";

	cout << "\nExecuting RabinKarpSearch Algorithm\n";
	time = high_resolution_clock::now();
	StringSearch::RabinKarpSearch(pat, txt, 101);
	cout << "time= " << (high_resolution_clock::now() - time).count() << "ns\n";

	cout << "\nExecuting BoerMurHarspul Algorithm\n";
	time = high_resolution_clock::now();
	StringSearch::BoerMurHorspulSearch(pat, txt);
	cout << "time= " << (high_resolution_clock::now() - time).count() << "ns\n";

	cout << "\nExecuting BoerMur Algorithm\n";
	time = high_resolution_clock::now();
	StringSearch::BoerMurSearch(pat, txt);
	cout << "time= " << (high_resolution_clock::now() - time).count() << "ns\n";

	cout << "\nExecuting KMP Algorithm\n";
	time = high_resolution_clock::now();
	StringSearch::KMPSearch(pat, txt);
	cout << "time= " << (high_resolution_clock::now() - time).count() << "ns\n";

	system("pause");
	return 0;
}