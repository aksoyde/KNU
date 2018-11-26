/**
	---, FileInfo.cpp
	����������: ���������� ������ �������� ���������� � ������

	@author Denis Aksoy
	@version 1.0 24/11/2018
*/

#pragma once
#include <string>
#include <vector>

struct File {
	std::string name;
	int size;
	std::string created;
	std::string mode;
	std::string type;
};

class FileInfo
{
private:
	// ������ (������ ���������� � ������)
	std::vector<File> files;
public:

	/**
		�������� ���������� � ����� � vector.
		@param ��������� �����.
	*/

	void addFile(std::string name, int size, std::string created, std::string mode, std::string type);

	/**
		����� ���� �� �����.
		@param name. ��� �����.
		@return file. ������ ���� File.
	*/

	File searchByName(std::string name);

	/**
		����� ���� �� �������.
		@param size. ������ �����.
		@return file. ������ ���� File.
	*/

	File searchBySize(int size);

	/**
		����� ���� �� ���� (����/�����).
		@param type. ��� (����/�����).
		@return file. ������ ���� File.
	*/

	File searchByType(std::string type);

	/**
		����� ���� �� ������� ��������.
		@param created. ����� ��������.
		@return file. ������ ���� File.
	*/

	File searchByTimeCreated(std::string created);

	/**
		����� ���� �� ������� ���������.
		@param mode. ����� ���������.
		@return file. ������ ���� File.
	*/

	File searchByTimeMode(std::string mode);

	/**
		������������� ���� � ������.
		@param file. ������ ���� File.
		@return result. ������ ���������� ��� ���������� �������.
	*/

	std::string fileToString(File file);

	/**
		������������� ��� ����� � ������
		@param ���
		@return result. �������� ��������.
	*/

	std::string allFilesToString();

	/**
		������������� ���������
		@param num. ���������� ����������� ���������.
	*/

	void genRandom(int num = 1);
};

