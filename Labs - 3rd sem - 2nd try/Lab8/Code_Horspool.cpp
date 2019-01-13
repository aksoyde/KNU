#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 100000;

int shift[MAXN];

// ������� ����� a �� b �����������
// ���������  � ���������������
bool equalH(string a, string b) {
	int i = a.size() - 2;
	while (i >= 0 && a[i] == b[i]) {
		i--;
	}
	return i == -1;
}

// �������� ��������
// ����-������ - ������ ��� ������� �������� �������
bool horspool(string a, string b) {
	// ��� ������� ������� ������� ������
	// ����������� ������� �������, �� �� �������� ����-������
	for (int i = 'a'; i <= 'z'; i++) {
		shift[i] = a.size();
	}
	for (int i = 0; i < a.size() - 1; i++) {
		shift[a[i]] = a.size() - i - 1;
	}
	// ������ ������ �� ��������� ���������� ������
	int i = a.size() - 1;
	while (i < b.size()) {
		if (a[a.size() - 1] != b[i]) {
			i += 1;
		} else if (!equalH(a, b.substr(i - a.size() + 1, a.size()))) {
			i += shift[b[i]];	
		} else {
			break;
		}
	}
	return i < b.size();
}

int main() {
	// ���������� ����� �������� �����
	cout << "Enter filename: ";
	string fileName;
	cin >> fileName;
	ifstream cin(fileName);
	
	// ���������� ������� �����
	string a, b;
	cin >> a >> b;
	// �������� ��������� a � b �� ��������� ��������� ��������
	if (horspool(a, b)) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}
