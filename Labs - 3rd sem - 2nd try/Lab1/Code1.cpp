#include <iostream>
#include <fstream>

using namespace std;

ifstream fin;
string outFilename;

int n;
int counter;

// ������ ���������� ���������� �������, ���
// �� ������� ���'��
string mergeSort(int l, int r) {
	// ��������� �� ���� � n ���������� �����
	if (l == r) {
		return to_string(l) + ".txt";
	}
	// ������� ����� �������� ������
	int mid = (l + r) / 2;
	string lName = mergeSort(l, mid);
	string rName = mergeSort(mid + 1, r);
	// ��������� ������ ��� ����������
	ifstream lin(lName), rin(rName);
	// ��������� ����� ���� � ������ counter.txt
	string mergedName = to_string(counter++) + ".txt";
	ofstream mout(mergedName);
	// ������� ������, �������� ��
	// ���������� ����������
	int ls, rs;
	lin >> ls;
	rin >> rs;
	mout << ls + rs << endl;
	bool readL = false, readR = false;
	int la, ra;
	while (ls != 0 || rs != 0) {
		if (rs == 0) {
			if (!readL) {
				lin >> la;
			}
			mout << la << " ";
			ls--;
			readL = false;
		} else if (ls == 0) {
			if (!readR) {
				rin >> ra;
			}
			mout << ra << " ";
			rs--;
			readR = false;
		} else {
			if (!readL) {
				lin >> la;
				readL = true;
			}
			if (!readR) {
				rin >> ra;
				readR = true;
			}
			if (la <= ra) {
				mout << la << " ";
				ls--;
				readL = false;
			} else {
				mout << ra << " ";
				rs--;
				readR = false;
			}
		}
	}
	// ��������� �������� �����
	lin.close();
	rin.close();
	string delName = "erase " + lName;
	system(delName.c_str());
	delName = "erase " + rName;
	system(delName.c_str());
	// ��������� ���� � ������������ ������� l..r
	// �� ��������� ���� �����
	mout.close();
	return mergedName;
}

// ����������� ���������� �������
void polyPhaseMergeSort() {
	// ��������� ����� a �� n ������ �
	// �������� ����� ������� � ������� ����
	counter = 0;
	fin >> n;
	for (int i = 0; i < n; i++) {
		int a;
		fin >> a;
		ofstream curout(to_string(counter++) + ".txt");
		curout << 1 << endl << a << endl;
		curout.close();
	}
	// �������� ������� ������ ���������� �����
	string sortedFilename = mergeSort(0, n - 1);
	// ����������� ���� � ������������ ������� a ���,
	// �� ��� �����
	string renameName = "rename " + sortedFilename + " " + outFilename;
	system(renameName.c_str());
}
 
int main() {
	// ���������� ���� �������� � ��������� �����
	cout << "Enter name of input file: ";
	string inFilename;
	cin >> inFilename;
	fin.open(inFilename);
	cout << "Enter name of output file: ";
	cin >> outFilename;
	
	// ����������� ����������
	polyPhaseMergeSort();
}
