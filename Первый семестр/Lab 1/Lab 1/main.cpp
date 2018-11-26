/**
	---, main.cpp
	����������: ������� ���� (������� main)

	@author Denis Aksoy
	@version 1.0 24/11/2018
*/

#include <iostream>
#include <locale>
#include "CyclicList.cpp"
#include "FileInfo.h"

int main() {
	setlocale(LC_ALL, "RUS");

	std::cout << "������ 1: ������� 1\n\n";

	CyclicList<int> list;

	// ���������� ��������� � ������
	list.addNote(432);
	list.addNote(754);
	list.addNote(15);
	list.addNote(534);
	list.addNote(6345);

	std::cout << "��� �������� ������: " << list.toString() << std::endl;
	std::cout << "����� �������� ��� �������� 3: "<< list.searchByIndex(3) << std::endl;
	std::cout << "����� �������� �� ��������� 15: " << list.searchByValue(15)->value << std::endl;
	std::cout << "����� �������� �� ��������� ������ 500: " << list.moreThan(500) << std::endl;

	std::cout << "\n������ 2: ������� 6\n\n";

	FileInfo files;

	// ���������� "������"
	files.addFile("Document.doc", 1026, "02/05/2018 09:23:07", "11/23/2018 07:36:39", "FILE");
	files.addFile("Video.avi", 1432432226, "07/09/2018 03:11:53", "08/27/2018 01:59:39", "FILE");
	files.addFile("Text.txt", 1026, "06/14/2018 08:59:34", "11/05/2018 09:33:33", "FILE");
	files.addFile("Tables.exl", 1026, "01/01/2018 11:19:01", "09/01/2018 09:24:06", "FILE");
	files.addFile("Files", 323902392, "01/01/2018 11:19:01", "09/01/2018 09:24:06", "FOLDER");
	// ��������� 2 ����� ��������
	files.genRandom(2);

	std::cout << "��� \"�����\":\n\n";
	std::cout << files.allFilesToString();

	std::cout << "����� ����� � ������ \"Text.txt\":\n\n" << files.fileToString(files.searchByName("Text.txt"));
	std::cout << "����� �����:\n\n" << files.fileToString(files.searchByType("FOLDER"));

	std::cin.get();
	std::cin.get();

	return 0;
}