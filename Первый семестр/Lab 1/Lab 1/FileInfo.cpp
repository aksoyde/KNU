/**
	---, FileInfo.cpp
	����������: ���������� ��������� �������� ���������� � ������

	@author Denis Aksoy
	@version 1.0 24/11/2018
*/

#include "FileInfo.h"

/**
	��������� ���������� � ������ � vector.
*/

void FileInfo::addFile(std::string name, int size, std::string created, std::string mode, std::string type) {
	files.push_back({name, size, created, mode, type});
}

/**
	���� ���� �� �����.
*/

File FileInfo::searchByName(std::string name) {
	for (size_t i = 0; i < files.size(); i++) {
		if (files[i].name == name)
			return files[i];
	}
	return File();
}

/**
	���� ���� �� �������.
*/

File FileInfo::searchBySize(int size) {
	for (size_t  i = 0; i < files.size(); i++) {
		if (files[i].size == size)
			return files[i];
	}
	return File();
}

/**
	���� ���� �� ���� (����/�����).
*/

File FileInfo::searchByType(std::string type) {
	for (size_t  i = 0; i < files.size(); i++) {
		if (files[i].type == type)
			return files[i];
	}
	return File();
}

/**
	���� ���� �� ������� ��������.
*/

File FileInfo::searchByTimeCreated(std::string created) {
	for (size_t i = 0; i < files.size(); i++) {
		if (files[i].created == created)
			return files[i];
	}
	return File();
}

/**
	���� ���� �� ������� ���������.
*/

File FileInfo::searchByTimeMode(std::string  mode) {
	for (size_t  i = 0; i < files.size(); i++) {
		if (files[i].mode == mode)
			return files[i];
	}
	return File();
}

/**
	��������������� ���� � ������.
*/

std::string FileInfo::fileToString(File file) {
	return "Name: " + file.name + "\nSize: " + std::to_string(file.size) + " bytes\nTime ctreated: " + file.created + "\nTime modificated: " + file.mode + "\nType: " + file.type + "\n\n";
}

/**
	���������� ��� �������� � ����� ������
*/

std::string FileInfo::allFilesToString() {
	std::string result;
	for (size_t  i = 0; i < files.size(); i++) {
		result += fileToString(files[i]);
	}
	return result;
}

/**
	���������� ��������� ������
*/

std::string genString(int size) {
	std::string str = "";
	int i = 0;
	for (i = 0; i < size; i++)
	{
		int x = 65 + rand() % 25;
		char a;
		a = x;
		str += a;
	}
	return str;
}

/**
	���������� ����� �� ���������� �����������.
*/

void FileInfo::genRandom(int num)
{
	File file;
	for (int i = 0; i < num; i++) {
		file.name = genString(10);
		file.size = rand() % 10000000;
		file.created = genString(10);
		file.mode = genString(10);
		file.type = (rand() % 2 == 0) ? "FILE" : "FOLDER";
		files.push_back(file);
	}
}
