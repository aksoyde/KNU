#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 100000;

int p[MAXN];

// ���������� �������-������� ����� s � ����� p
void findPrefixFunction(string s) {
	p[0] = 0;
	for (int i = 1; i < s.size(); i++) {
		if (s[i] == s[p[i - 1]]) {
			p[i] = p[i - 1] + 1;
		} else {
			int j = p[i - 1];
			while (j != 0 && s[j] != s[i]) {
				j = p[j - 1];
			}
			if (j == 0 && s[j] != s[i]) {
				p[i] = 0;
			} else {
				p[i] = j + 1;
			}
		}
	}
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
	// ����������� �������-������� ����� a#b
	findPrefixFunction(a + "#" + b); 
	// ���� �������-������� ��� ����� ������� ���� ���������� �������
	// ������� ������ ������, �� �� ������� ���������
	for (int i = a.size() + 1; i < a.size() + b.size() + 1; i++) {
		if (p[i] == a.size()) {
			cout << "YES" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;
}
