#pragma once
#include"Matrix.h"
#include<cmath>
#include<vector>
using std::fmax;
using std::vector;

class Matrix;
class Strassen
{
private:
	static int log2(int x);
	static int getNewDimension(const Matrix& a, const Matrix& b);
	static Matrix multiStrassen(const Matrix &a, const Matrix &b, int n);
	static Matrix collectMatrix(const Matrix& a11, const Matrix&a12, const Matrix& a21, const Matrix& a22);
	static void Split(const Matrix& a, Matrix& a11, Matrix& a12, Matrix& a21, Matrix& a22);
public:
	static Matrix Multiply(Matrix& a, Matrix& b);
};

