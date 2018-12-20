#include"Matrix.h"
#include<fstream>
using std::ifstream;

int main()
{
	Matrix a, b;
	a.ReadFromFile("Matrix1.txt");
	b.ReadFromFile("Matrix2.txt");

	a.Print("MatrixA");
	b.Print("MatrixB");

	Matrix c = a + b;
	c.Print("MatrixA+B");

	Matrix d = a - b;
	d.Print("MatrixA-B");

	(a*b).Print("MatrixA*B");

	Matrix strass = Strassen::Multiply(a, b);
	strass.Print("A*B");
	system("pause");
	return 0;
}
