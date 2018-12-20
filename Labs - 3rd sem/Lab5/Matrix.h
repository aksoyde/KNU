#pragma once
#include"Strassen.h"
#include<cassert>
#include<fstream>
#include<cmath>
#include<iostream>
using std::ifstream;
using std::endl;
using std::cout;

class Strassen;
class Matrix
{
private:
	int n, m;
	int **grid;
	
public:
	int columns() const;
	int rows() const;
	int** values() const;

	Matrix operator +(const Matrix& b);
	Matrix operator -(const Matrix& b);
	Matrix operator =(const Matrix& b);
	Matrix operator *(const Matrix& b) const;
	int* operator[] (int i) const;

	void ReadFromFile(const char* input);
	void Print(const char *name);
	void Narrow(int x, int y, int newN, int newM, const Matrix &a);
	void Extent(int x, int y, int newN, int newM, const Matrix &a);
	void Resize(int n, int m);
	void Clear();

	Matrix(const Matrix& object);
	Matrix();
	~Matrix();
};
