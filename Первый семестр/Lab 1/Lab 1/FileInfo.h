/**
	---, FileInfo.cpp
	Назначение: Объявления класса хранения информации о файлах

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
	// Вектор (хренит информацию о файлах)
	std::vector<File> files;
public:

	/**
		Добавить информацию о файле в vector.
		@param параметры файла.
	*/

	void addFile(std::string name, int size, std::string created, std::string mode, std::string type);

	/**
		Найти файл по имени.
		@param name. Имя файла.
		@return file. Объект типа File.
	*/

	File searchByName(std::string name);

	/**
		Найти файл по размеру.
		@param size. Размер файла.
		@return file. Объект типа File.
	*/

	File searchBySize(int size);

	/**
		Найти файл по типу (Файл/Папка).
		@param type. Тип (Файл/Папка).
		@return file. Объект типа File.
	*/

	File searchByType(std::string type);

	/**
		Найти файл по времени создания.
		@param created. Время создания.
		@return file. Объект типа File.
	*/

	File searchByTimeCreated(std::string created);

	/**
		Найти файл по времени изменения.
		@param mode. Время изменения.
		@return file. Объект типа File.
	*/

	File searchByTimeMode(std::string mode);

	/**
		Преобразовать файл в строку.
		@param file. Объект типа File.
		@return result. Строка содержащая все переменный объекта.
	*/

	std::string fileToString(File file);

	/**
		Преобразовать все файлы в строку
		@param нет
		@return result. Значение элемента.
	*/

	std::string allFilesToString();

	/**
		Сгенерировать случайный
		@param num. Количество создаваемых элементов.
	*/

	void genRandom(int num = 1);
};

