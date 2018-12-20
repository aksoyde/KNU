#include "Strassen.h"

int Strassen::log2(int x)
{
	int result = 1;
	while ((x >>= 1) != 0) result++;
	return result;
}
int Strassen::getNewDimension(const Matrix & a, const Matrix & b)
{
	int maxi = fmax(fmax(a.rows(), a.columns()), fmax(b.rows(), b.columns()));
	return 1 << log2(maxi);
}

void Strassen::Split(const Matrix& a, Matrix& a11, Matrix& a12, Matrix& a21, Matrix& a22)
{
	int n = a.rows() >> 1;

	a11.Narrow(0, 0, n,n, a);
	a12.Narrow(0, n, n,n, a);
	a21.Narrow(n, 0, n,n, a);
	a22.Narrow(n, n, n,n, a);
}
Matrix Strassen::collectMatrix(const Matrix& a11, const Matrix&a12, const Matrix& a21, const Matrix& a22)
{
	int n = a11.rows();
	Matrix a;
	a.Resize(n << 1, n << 1);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = a11[i][j];
			a[i][j + n] = a12[i][j];
			a[i + n][j] = a21[i][j];
			a[i+ n][j + n] = a22[i][j];
		}
	}
	return a;
}

Matrix Strassen::multiStrassen(const Matrix &a, const Matrix &b, int n)
{
	if (n <= 1)
		return a * b;
	Matrix a11, a12, a21, a22, b11, b12, b21, b22;
	
	Split(a, a11, a12, a21, a22);
	Split(b, b11, b12, b21, b22);
	n = n >> 1;

	Matrix p1 = multiStrassen(a11+a22, b11+b22, n);
	Matrix p2 = multiStrassen(a21+a22, b11, n);
	Matrix p3 = multiStrassen(a11, b12-b22, n);
	Matrix p4 = multiStrassen(a22, b21-b11, n);
	Matrix p5 = multiStrassen(a11+a12, b22, n);
	Matrix p6 = multiStrassen(a21-a11, b11+b12, n);
	Matrix p7 = multiStrassen(a12-a22, b21+b22, n);

	Matrix c11 = (p1+p4) + (p7-p5);
	Matrix c12 = p3 + p5;
	Matrix c21 = p2 + p4;
	Matrix c22 = (p1-p2) + (p3+p6);

	return collectMatrix(c11, c12, c21, c22);
}

Matrix Strassen::Multiply(Matrix & a, Matrix & b)
{
	int newSize = getNewDimension(a, b);

	Matrix A,B;
	A.Extent(0, 0, newSize, newSize, a);
	B.Extent(0, 0, newSize, newSize, b);

	Matrix C = multiStrassen(A, B, newSize);
	return C;
}