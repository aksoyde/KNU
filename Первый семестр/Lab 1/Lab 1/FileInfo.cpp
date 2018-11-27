/**
	---, FileInfo.cpp
	Íàçíà÷åíèå: Ðåàëèçàöèÿ ñòðóêòóðû õðàíåíèÿ èíôîðìàöèè î ôàéëàõ
	Purpose: Implementation of file information storage structures
	@author Denis Aksoy
	@version 1.0 24/11/2018
*/

#include "FileInfo.h"

/**
	Äîáàâëÿåò èíôîðìàöèþ î ôàéëàõ â vector.
	Adds information about files in vector
*/

void FileInfo::addFile(std::string name, int size, std::string created, std::string mode, std::string type) {
	files.push_back({name, size, created, mode, type});
}

/**
	Èùåò ôàéë ïî èìåíè.
	Searches file by name
*/

File FileInfo::searchByName(std::string name) {
	for (size_t i = 0; i < files.size(); i++) {
		if (files[i].name == name)
			return files[i];
	}
	return File();
}

/**
	Èùåò ôàéë ïî ðàçìåðó.
	Searches file by size
*/

File FileInfo::searchBySize(int size) {
	for (size_t  i = 0; i < files.size(); i++) {
		if (files[i].size == size)
			return files[i];
	}
	return File();
}

/**
	Èùåò ôàéë ïî òèïó (Ôàéë/Ïàïêà).
	Searches file by type (File/Folder)
*/

File FileInfo::searchByType(std::string type) {
	for (size_t  i = 0; i < files.size(); i++) {
		if (files[i].type == type)
			return files[i];
	}
	return File();
}

/**
	Èùåò ôàéë ïî âðåìåíè ñîçäàíèÿ.
	Searches file by time of creation
*/

File FileInfo::searchByTimeCreated(std::string created) {
	for (size_t i = 0; i < files.size(); i++) {
		if (files[i].created == created)
			return files[i];
	}
	return File();
}

/**
	Èùåò ôàéë ïî âðåìåíè èçìåíåíèÿ.
	Searches file by time of change time (not sure how to translate it correctly)
*/

File FileInfo::searchByTimeMode(std::string  mode) {
	for (size_t  i = 0; i < files.size(); i++) {
		if (files[i].mode == mode)
			return files[i];
	}
	return File();
}

/**
	Ïðåîáðàçîâûâàåò ôàéë â ñòðîêó.
	Converts a file to a string 
*/

std::string FileInfo::fileToString(File file) {
	return "Name: " + file.name + "\nSize: " + std::to_string(file.size) + " bytes\nTime ctreated: " + file.created + "\nTime modificated: " + file.mode + "\nType: " + file.type + "\n\n";
}

/**
	Âîçâðàùàåì âñå ýëåìåíòû â îäíîé ñòðîêå
	Returning all elements in one string
*/

std::string FileInfo::allFilesToString() {
	std::string result;
	for (size_t  i = 0; i < files.size(); i++) {
		result += fileToString(files[i]);
	}
	return result;
}

/**
	Ãåíåðèðóåò ñëó÷àéíóþ ñòðîêó
	Generates a random string
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
	Ãåíåðèðóåò ôàéëû ñî ñëó÷àéíûìè ïàðàìåòðàìè.
	Generates files with random parameters
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
