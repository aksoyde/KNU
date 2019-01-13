#include <iostream>
#include <fstream>

using namespace std;

// ����� ������ �����, �� ���������
// ������ ������� ������� � ������
const int P = 31;
const int MAXN = 100000;
	
int pow[MAXN];
int ha[MAXN], hb[MAXN];
string a, b;

// ��������� ���������� ������ ����� P
void calculatePowers(int n) {
	pow[0] = 1;
	for (int i = 1; i < n; i++) {
		pow[i] = pow[i - 1] * P;
	}
}

// ���������� ���-������� ��� ��� �������� 
// ����� s � �� �������� � ����� h
void makeHash(string s, int* h) {
	h[0] = s[0];
	for (int i = 1; i < s.size(); i++) {
		pow[i] = pow[i - 1] * P;
		h[i] = h[i - 1] + s[i] * pow[i];
	}
}

// ����������� �������� �� ������ b[l..r] � a
bool trivialCheck(int l, int r) {
	for (int i = l; i <= r; i++) {
		if (b[i] != a[i - l]) {
			return false;
		}
	}
	return true;
}

int main() {
	// ���������� ����� �������� �����
	cout << "Enter filename: ";
	string fileName;
	cin >> fileName;
	ifstream cin(fileName);
	
	//���������� ������� �����
	cin >> a;
	cin >> b;
	//���������� ����� a �� b
	calculatePowers(b.size());
	makeHash(a, ha);
	makeHash(b, hb);
	// �������� ��� �������� ������� b �������� a.size() �� ������ � a
	for (int l = 0; l < b.size() - a.size() + 1; l++) {
	int r = l + a.size() - 1;
		if (hb[r] - (l ? hb[l - 1] : 0) == ha[a.size() - 1] * pow[l] &&
			trivialCheck(l, r)) {
			// ���� ��� �� ����� ����������� ���
			cout << "YES" << endl;
			return 0; 
		}
	}
	// �� ��������� ����� ����� �����������
	cout << "NO" << endl;
}
