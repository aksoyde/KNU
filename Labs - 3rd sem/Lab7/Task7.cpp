#include"Matrix_Search.h"
#include<vector>
#include<iostream>
#include<fstream>
using std::ifstream;
using std::cout;
using std::vector;

char** ReadFromFile(const char* inputFile, int &n, int &m);
void Print(char** text, int n, int m, const char* Title);
int main()
{
	int tRows, tCols;
	char **Text = ReadFromFile("Text.txt", tRows, tCols);
	Print(Text, tRows, tCols, "Input text: ");

	int pRows, pCols;
	char **Pattern = ReadFromFile("Pattern.txt", pRows, pCols);
	Print(Pattern, pRows, pCols, "Pattern is: ");

	Matrix_Search::Search(Pattern, pRows, pCols, Text, tRows, tCols, 32, 393);

	system("pause");
	return 0;
}

char** ReadFromFile(const char* inputFile, int &n, int &m)
{
	char **matrix;
	ifstream fin(inputFile);
	fin >> n >> m;

	matrix = new char*[n];
	for (int i = 0; i < n; i++)
		matrix[i] = new char[m];


	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < m; j++)
			fin >> matrix[i][j];

	return matrix;
}
void Print(char ** text, int n, int m, const char * Title)
{
	cout << Title << "\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << text[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
}
