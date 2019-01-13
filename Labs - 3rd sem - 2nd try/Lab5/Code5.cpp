#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <ratio>
#include <thread>

using namespace std;
using namespace std::chrono;

const int MAXN = 256;
int MAXS = 2;

// ��� ��� ���������� �����
const int T = 5;
int tn[T] = {32, 64, 128, 128, 256};
int ts[T] = {16, 32, 32, 64, 128};

// ��������� ��� ������ � ����������� ���������
struct SquareMatrix {
	int n;
	int **x;
	
	SquareMatrix (int n) {
		x = new int*[n];
		for (int i = 0; i < n; i++) {
			x[i] = new int[n];
		}
		this->n = n;
	}
	
	SquareMatrix(int **a, int n, int m) {
		int k = max(m, n);
		int p = 1;
		while (p < k) {
			p *= 2;
		}
		this->n = p;
		x = new int*[this->n];
		for (int i = 0; i < this->n; i++) {
			x[i] = new int[this->n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				x[i][j] = a[i][j];
			}
		}
	}
	
	~SquareMatrix() {
		for (int i = 0; i < n; i++) {
			delete x[i];
		}
		delete x;
	}
	
	void print() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << x[i][j] << " ";
			}
			cout << endl;
		}
	}
};

// ���������� ���� �������
SquareMatrix operator + (SquareMatrix a, SquareMatrix b) {
	SquareMatrix c(a.n);
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			c.x[i][j] = a.x[i][j] + b.x[i][j];
		}
	}
	return c;
}

// ��������� ������ �������
SquareMatrix operator - (SquareMatrix a, SquareMatrix b) {
	SquareMatrix c(a.n);
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			c.x[i][j] = a.x[i][j] - b.x[i][j];
		}
	}
	return c;
}

// �������� ������� �� ������
bool operator == (SquareMatrix a, SquareMatrix b) {
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			if (a.x[i][j] != b.x[i][j]) {
				return false;
			}
		}
	}
	return true;
}

// ��������� n ������ ����� �� m ������ �������� ������� a
void print(int n, int m, SquareMatrix a) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << a.x[i][j] << " ";
		}
		cout << endl;
	}
}

// ��������� ������� �� 4 ����� ���������� ������
void divide(SquareMatrix a, SquareMatrix& a11, SquareMatrix& a12, SquareMatrix& a21, SquareMatrix& a22) {
	for (int i = 0; i < a.n / 2; i++) {
		for (int j = 0; j < a.n / 2; j++) {
			a11.x[i][j] = a.x[i][j];
		}
	}
	for (int i = 0; i < a.n / 2; i++) {
		for (int j = a.n / 2; j < a.n; j++) {
			a12.x[i][j - a.n / 2] = a.x[i][j];
		}
	}
	for (int i = a.n / 2; i < a.n; i++) {
		for (int j = 0; j < a.n / 2; j++) {
			a21.x[i - a.n / 2][j] = a.x[i][j];
		}
	}
	for (int i = a.n / 2; i < a.n; i++) {
		for (int j = a.n / 2; j < a.n; j++) {
			a22.x[i - a.n / 2][j - a.n / 2] = a.x[i][j];
		}
	}
}

// ��'������� ������� �������
void unite(SquareMatrix& a, SquareMatrix a11, SquareMatrix a12, SquareMatrix a21, SquareMatrix a22) {
	for (int i = 0; i < a.n / 2; i++) {
		for (int j = 0; j < a.n / 2; j++) {
			 a.x[i][j] = a11.x[i][j];
		}
	}
	for (int i = 0; i < a.n / 2; i++) {
		for (int j = a.n / 2; j < a.n; j++) {
			a.x[i][j] = a12.x[i][j - a.n / 2];
		}
	}
	for (int i = a.n / 2; i < a.n; i++) {
		for (int j = 0; j < a.n / 2; j++) {
			a.x[i][j] = a21.x[i - a.n / 2][j];
		}
	}
	for (int i = a.n / 2; i < a.n; i++) {
		for (int j = a.n / 2; j < a.n; j++) {
			a.x[i][j] = a22.x[i - a.n / 2][j - a.n / 2];
		}
	}
};

// ��������� �������� �������� ������� �� O(n^3)
SquareMatrix trivialProduct(SquareMatrix a, SquareMatrix b) {
	SquareMatrix c(a.n);
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < a.n; j++) {
			c.x[i][j] = 0;
			for (int s = 0; s < a.n; s++) {
				c.x[i][j] += a.x[i][s] * b.x[s][j];
			}
		}
	}
	return c;
}

// �������� ���������
SquareMatrix operator * (SquareMatrix a, SquareMatrix b) {
	// ���� ������� ����� ���, ����������� �� ���������
	if (a.n <= MAXS) {
		return trivialProduct(a, b);
	}
	// ���� ����� ������� a � b �� 4 ����� �������
	SquareMatrix a11(a.n / 2), a12(a.n / 2), a21(a.n / 2), a22(a.n / 2);
	SquareMatrix b11(a.n / 2), b12(a.n / 2), b21(a.n / 2), b22(a.n / 2);
	divide(a, a11, a12, a21, a22);
	divide(b, b11, b12, b21, b22);
	// ���������� �������� ������� pk
	SquareMatrix p1 = (a11 + a22)  * (b11 + b22);
	SquareMatrix p2 = (a21 + a22) * b11;
	SquareMatrix p3 = a11 * (b12 - b22);
	SquareMatrix p4 = a22 * (b21 - b11);
	SquareMatrix p5 = (a11 + a12) * b22;
	SquareMatrix p6 = (a21 - a11) * (b11 + b12);
	SquareMatrix p7 = (a12 - a22) * (b21 + b22);
	// ���������� ��������� ������� cij
	SquareMatrix c11 = p1 + p4 - p5 + p7;
	SquareMatrix c12 = p3 + p5;
	SquareMatrix c21 = p2 + p4;
	SquareMatrix c22 = p1 - p2 + p3 + p6;
	// ��'������� ������� ������� � ����� ������� c
	SquareMatrix c(a.n);
	unite(c, c11, c12, c21, c22);
	return c;
}

int **a, **b;

// ���� ��� �����������
void userTest() {
	// ���������� ����� �������� �����
	cout << "Enter filename: ";
	string fileName;
	cin >> fileName;
	ifstream cin(fileName);
	
	// ���������� ������� �����
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			cin >> b[i][j];
		}
	}
	// ��������� ���������� �������
	// � ������� ������ ����� �� ������� �������
	SquareMatrix sa(a, n, m);
	SquareMatrix sb(b, m, k);
	// ���������� ������� a � b �� ���������� ���������
	SquareMatrix sc = sa * sb;
	cout << endl;
	cout << "Strassen algorithm:" << endl;
	print(n, k, sc);
	cout << endl;
	// ���������� ������� a � b �� ���������� ����������
	SquareMatrix sct = trivialProduct(sa, sb);
	cout << "Trivial algorithm:" << endl;
	print(n, k, sct);
	cout << endl;
	// �������� ���������� ��������
	if (sc == sct) {
		cout << "Correct" << endl;
	} else {
		cout << "Incorrect" << endl;
	}
}

// ��������� ����������� ������ ��������� n x n
void generate(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = rand() - RAND_MAX / 2;
			b[i][j] = rand() - RAND_MAX / 2;
		}
	}
}

// ��������� ����� �� ��������
// ��������� ���������� � ���� comparing.txt
void complexityTest() {
	ofstream fout("comparing.txt");
	fout << "N L Time(sec): Strassen, Trivial Ts / Tt" << endl;
	srand(time(NULL));
	fout.setf(ios_base::fixed);
	fout.precision(4);
	for (int i = 0; i < T; i++) {
		MAXS = ts[i];
		fout << tn[i] << " " << ts[i] << " ";
		generate(tn[i]);
		SquareMatrix sa(a, tn[i], tn[i]);
		SquareMatrix sb(b, tn[i], tn[i]);
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		SquareMatrix sc = sa * sb;
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		double dt1 = duration_cast<duration<double>>(t2 - t1).count();
		t1 = high_resolution_clock::now();
		SquareMatrix sct = trivialProduct(sa, sb);
		t2 = high_resolution_clock::now();
		double dt2 = duration_cast<duration<double>>(t2 - t1).count();
		if (!(sc == sct)) {
			cout << "Strassen failed!" << endl;
			exit(0);
		}
		fout << dt1 << " " << dt2 << " " << dt1 / dt2 << endl;
	}
}

int main() {
	// �������� ���'�� �� ������� a �� b
	a = new int*[MAXN];
	b = new int*[MAXN];
	for (int i = 0; i < MAXN; i++) {
		a[i] = new int[MAXN];
		b[i] = new int[MAXN];
	}
	// ��������� ����� �����������
	userTest(); 
	//complexityTest();
}
