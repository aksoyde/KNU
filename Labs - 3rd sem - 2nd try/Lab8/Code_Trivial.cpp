#include <iostream>
#include <fstream>

using namespace std;

string a, b;

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
	// �������� ��� �������� ������� b �������� a.size() �� ������ � a
	for (int l = 0; l < b.size() - a.size() + 1; l++) {
		int r = l + a.size() - 1;
		if (trivialCheck(l, r)) {
			// ����� ����������� ���
			cout << "YES" << endl;
			return 0; 
		}
	}
	// �� ��������� ����� ����� �����������
	cout << "NO" << endl;
}
