#include "Matrix.h"

int Matrix::columns() const
{
	return m;
}

int Matrix::rows() const
{
	return n;
}

int** Matrix::values() const
{
	return grid;
}

Matrix Matrix::operator+(const Matrix & b)
{
	assert(n == b.n && m == b.m);

	Matrix c;
	c.Resize(n, m);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			c[i][j] = (*this)[i][j] + b[i][j];

	return c;
}

Matrix Matrix::operator-(const Matrix & b)
{
	assert(n == b.n && m == b.m);

	Matrix c;
	c.Resize(n, m);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			c[i][j] = (*this)[i][j] - b[i][j];

	return c;
}

Matrix Matrix::operator=(const Matrix & b)
{
	Narrow(0, 0, b.n, b.m, b);
	return *this;
}

Matrix Matrix::operator*(const Matrix &b) const
{
	assert(n == b.m);

	Matrix c;
	c.Resize(n, b.m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < b.m; j++)
			for (int k = 0; k < m; k++)
				c[i][j] += (*this)[i][k] * b[k][j];
	return c;
}


int* Matrix::operator[] (int i) const
{
	return grid[i];
}

void Matrix::ReadFromFile(const char * input)
{
	ifstream fin(input);
	fin >> n >> m;
	Resize(n, m);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			fin >> grid[i][j];
}

void Matrix::Narrow(int x, int y, int newN, int newM, const Matrix & a)
{
	Resize(newN, newM);
	for (int i = 0; i < newN; i++)
		for (int j = 0; j < newM; j++)
			grid[i][j] = a[i + x][j + y];
}
void Matrix::Extent(int x, int y, int newN, int newM, const Matrix & a)
{
	Resize(newN, newM);
	for (int i = 0; i < a.n; i++)
		for (int j = 0; j < a.m; j++)
			grid[i][j] = a[i + x][j + y];
}
void Matrix::Resize(int n, int m)
{
	Clear();

	this->n = n;
	this->m = m;
	grid = new int*[n];
	for (size_t i = 0; i < n; i++)
		grid[i] = new int[m];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			grid[i][j] = 0;
}
void Matrix::Clear()
{
	if (grid)
	{
		for (size_t i = 0; i < n; i++)
			delete[] grid[i];
		delete[] grid;
	}
}

void Matrix::Print(const char *name)
{
	cout << "-----" << name << "------" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << grid[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

Matrix::Matrix(const Matrix & object) : Matrix()
{
	Narrow(0, 0, object.n, object.m, object);
}

Matrix::Matrix()
{
	grid = nullptr;
}

Matrix::~Matrix()
{
	Clear();
}