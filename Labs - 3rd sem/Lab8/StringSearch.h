#pragma once
#include<string>
#include<vector>
using std::vector;
using std::string;
class StringSearch
{
private:
	static const int NO_OF_CHARS = 256; //the number of characters in the input alphabet
	static void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS]);
	static void preprocess_strong_suffix(int *shift, int *bpos, char *pat, int m);
public:
	static void NaiveSearch(char* pat, char* txt);
	static void RabinKarpSearch(char pat[], char txt[], int q);
	static void BoerMurHorspulSearch(char* pat, char* txt);
	static void BoerMurSearch(char* pat, char* txt);
	static void KMPSearch(char* pat, char* txt);

};
	