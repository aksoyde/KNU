#include <iostream>
#include <fstream>

using namespace std;

// ��������� ��� ��������� ���������� ��� ������
struct Detail {
	float size;
	int id;
};

// ���������� ������� ������ �������� Detail �� ����� size
void mergeSort(int l, int r, Detail* d) {
	// ����� � ������ �������� ������������� �� ����������
	if (l == r) {
		return;
	}
	// ������� ��� �� ����� �������� ������
	int mid = (l + r) / 2;
	mergeSort(l, mid, d);
	mergeSort(mid + 1, r, d);
	// ������� �� �������� � ���������� ����� temp
	int size = r - l + 1;
	Detail *temp = new Detail[size];
	int p1 = l, p2 = mid + 1, pt = 0;
	while (pt != size) {
		if (p1 == mid + 1 || d[p2].size < d[p1].size) {
			temp[pt] = d[p2];
			p2++; 
		} else {
			temp[pt] = d[p1];
			p1++;
		}
		pt++;
	}
	// ���������� ������������ ����� � d �� ��������� ���������� �����
	for (int i = 0; i < size; i++) {
		d[l + i] = temp[i];
	}
	delete temp;
}

int main() {
	// ���������� ����� �������� �����
	cout << "Enter filename: ";
	string fileName;
	cin >> fileName;
	ifstream cin(fileName);
	
	// ����������� �������� ��� ��������� �������
	// �� ���������� ���������� ��� ���
	int n;
	cin >> n;
	Detail* b = new Detail[n];
	Detail* g = new Detail[n];
	for (int i = 0; i < n; i++) {
		cin >> b[i].size;
		b[i].id = i;
	}
	for (int i = 0; i < n; i++) {
		cin >> g[i].size;
		g[i].id = i;
	}
	// ���������� ����� �� ����� ��������
	mergeSort(0, n - 1, b);
	mergeSort(0, n - 1, g);
	// ����������� ��� ��������:
	// ����� ��������� 2 ������� � ���������� �������
	// ����� �� �����, �� ������� �� �������
	int pb = 0, pg = 0;
	while (pb < n && pg < n) {
		if (b[pb].size == g[pg].size) {
			cout << b[pb].id << " - " << g[pg].id << endl;
			pb++;
			pg++;
		} else if (b[pb].size < g[pg].size) {
			pb++;
		} else {
			pg++;
		}
	}
}
