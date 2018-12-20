#pragma once
#include<vector>
#include<iostream>
using std::vector;
using std::cout;

class Matrix_Search
{
private:
	static void ComputateColumnsHash(char** PATTERN, vector<int> &pattern, int pCols, int pRows,
		int NO_OF_CHARS, int q);
	static void ChangeRowHash(int row, char** TEXT, vector<int>& text, int pRows, int tCols,
		int NO_OF_CHARS, int dm, int q);
	static bool isSymbolEqual(int row, int column, char **PATTERN, int pRows, int pCols, 
		char **TEXT);
	static vector<int> BuildPrefixFunction(vector<int> &pat);
	static int KMP(vector<int>& pattern, vector<int> & text, bool& found);
public:
	static void Search(char **PATTERN, int pRows, int pCols, char **TEXT, int tRows, int tCols,
		int NO_OF_CHARS, int q);
};

