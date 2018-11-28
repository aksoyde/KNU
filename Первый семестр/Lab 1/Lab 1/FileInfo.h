/**
	---, FileInfo.cpp
	Íàçíà÷åíèå: Îáúÿâëåíèÿ êëàññà õðàíåíèÿ èíôîðìàöèè î ôàéëàõ
	Purpose: File storage class declarations
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
	// Âåêòîð (õðåíèò èíôîðìàöèþ î ôàéëàõ) / Vector (stores information about files)
	std::vector<File> files;
public:

	/**
		Äîáàâèòü èíôîðìàöèþ î ôàéëå â vector.
		Add file information to vector.
		@param ïàðàìåòðû ôàéëà/file parameters
	*/

	void addFile(std::string name, int size, std::string created, std::string mode, std::string type);

	/**
		Íàéòè ôàéë ïî èìåíè
		Find file by name
		@param name. Èìÿ ôàéëà/Name of the file
		@return file. Îáúåêò òèïà File/File object
	*/

	File searchByName(std::string name);

	/**
		Íàéòè ôàéë ïî ðàçìåðó
		Find file by size
		@param size. Ðàçìåð ôàéëà/Size of file
		@return file. Îáúåêò òèïà File/File object
	*/

	File searchBySize(int size);

	/**
		Íàéòè ôàéë ïî òèïó (Ôàéë/Ïàïêà)
		Find file by type (File / Folder)
		@param type. Òèï (Ôàéë/Ïàïêà)/Type (File folder)
		@return file. Îáúåêò òèïà File/File object
	*/

	File searchByType(std::string type);

	/**
		Íàéòè ôàéë ïî âðåìåíè ñîçäàíèÿ.
		Find file by creation time
		@param created. Âðåìÿ ñîçäàíèÿ/Time of creaction
		@return file. Îáúåêò òèïà File/File object
	*/

	File searchByTimeCreated(std::string created);

	/**
		Íàéòè ôàéë ïî âðåìåíè èçìåíåíèÿ
		Find file by change time
		@param mode. Âðåìÿ èçìåíåíèÿ/Change time
		@return file. Îáúåêò òèïà File/File object
	*/

	File searchByTimeMode(std::string mode);

	/**
		Ïðåîáðàçîâàòü ôàéë â ñòðîêó
		Convert file to string
		@param file. Îáúåêò òèïà File/File object
		@return result. Ñòðîêà ñîäåðæàùàÿ âñå ïåðåìåííûé îáúåêòà/A string containing all object variables
	*/

	std::string fileToString(File file);

	/**
		Ïðåîáðàçîâàòü âñå ôàéëû â ñòðîêó
		Convert all files to string
		@param íåò/no
		@return result. Çíà÷åíèå ýëåìåíòà/Element value
	*/

	std::string allFilesToString();

	/**
		Ñãåíåðèðîâàòü ñëó÷àéíûé
		Generate random
		@param num. Êîëè÷åñòâî ñîçäàâàåìûõ ýëåìåíòîâ/Amount of created elements
	*/

	void genRandom(int num = 1);
};

