#include <iostream>
#include <fstream>

using namespace std;

const int P = 31;
const int MAXN = 100000;
	
int pow[MAXN];
int ha[MAXN], hb[MAXN];
string a, b;

// ���������� ������ ����� P
void calculatePowers(int n) {
	pow[0] = 1;
	for (int i = 1; i < n; i++) {
		pow[i] = pow[i - 1] * P;
	}
}

// ���������� ���-������� ����� s � ���� �������� � ����� h
void makeHash(string s, int* h) {
	h[0] = s[0];
	for (int i = 1; i < s.size(); i++) {
		pow[i] = pow[i - 1] * P;
		h[i] = h[i - 1] + s[i] * pow[i];
	}
}

// ����������� �������� �� ������ a[l..r] � b
bool trivialCheck(int l, int r) {
	for (int i = l; i <= r; i++) {
		if (a[i] != b[i - l]) {
			return false;
		}
	}
	return true;
}

int main() {
	// ���������� ���� �������� �����
	cout << "Enter filename: ";
	string fileName;
	cin >> fileName;
	ifstream cin(fileName);
	
	//���������� ������� �����
	cin >> a;
	cin >> b;
	int n = a.size();
	// �������� ����� a
	a += a;
	//���������� ����� a �� b
	calculatePowers(2 * n);
	makeHash(a, ha);
	makeHash(b, hb);
	// �������� ��� �������� ������� a �������� n �� ������ � b
	for (int l = 0; l < n - 1; l++) {
		int r = l + n - 1;
		// ���� � �������� ����� a && b a = false,
		// �� ����� b �� ������������
		if (ha[r] - (l ? ha[l - 1] : 0) == hb[n - 1] * pow[l] &&
			trivialCheck(l, r)) {
			// ���� ��� �� ����� ����������� ���
			cout << "YES" << endl;
			return 0; 
		}
	}
	// �� ��������� ����� ����� �����������
	cout << "NO" << endl;
}
