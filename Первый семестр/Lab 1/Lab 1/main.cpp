/**
	---, main.cpp
	Íàçíà÷åíèå: Ãëàâíûé ôàéë (ôóíêöèÿ main)
	Purpose: Main file (function "main")
	@author Denis Aksoy
	@version 1.0 24/11/2018
*/

#include <iostream>
#include <locale>
#include "CyclicList.cpp"
#include "FileInfo.h"

int main() {
	setlocale(LC_ALL, "RUS");

	std::cout << "ÑÏÈÑÎÊ 1: ÇÀÄÀÍÈÅ 1\n\n";

	CyclicList<int> list;

	// Äîáàâëåíèå ýëåìåíòîâ â ñïèñîê
	// Adds elements to list
	list.addNote(432);
	list.addNote(754);
	list.addNote(15);
	list.addNote(534);
	list.addNote(6345);

	std::cout << "Âñå ýëåìåíòû ñïèñêà: " << list.toString() << std::endl;
	std::cout << "Ïîèñê ýëåìåíòà ïîä èíäåêñîì 3: "<< list.searchByIndex(3) << std::endl;
	std::cout << "Ïîèñê ýëåìåíòà ñî çíà÷åíèåì 15: " << list.searchByValue(15)->value << std::endl;
	std::cout << "Ïîèñê ýëåìåíòà ñî çíà÷åíèåì áîëüøå 500: " << list.moreThan(500) << std::endl;

	std::cout << "\nÑÏÈÑÎÊ 2: ÇÀÄÀÍÈÅ 6\n\n";

	FileInfo files;

	// Äîáàâëåíèå "ôàéëîâ"
	// Adds "files"
	files.addFile("Document.doc", 1026, "02/05/2018 09:23:07", "11/23/2018 07:36:39", "FILE");
	files.addFile("Video.avi", 1432432226, "07/09/2018 03:11:53", "08/27/2018 01:59:39", "FILE");
	files.addFile("Text.txt", 1026, "06/14/2018 08:59:34", "11/05/2018 09:33:33", "FILE");
	files.addFile("Tables.exl", 1026, "01/01/2018 11:19:01", "09/01/2018 09:24:06", "FILE");
	files.addFile("Files", 323902392, "01/01/2018 11:19:01", "09/01/2018 09:24:06", "FOLDER");
	// Ãåíåðèðóì 2 ôàéëà ñëó÷àéíî
	// Generating 2 files randomly
	files.genRandom(2);

	std::cout << "Âñå \"ôàéëû\":\n\n";
	std::cout << files.allFilesToString();

	std::cout << "Ïîèñê ôàéëà ñ èìåíåì \"Text.txt\":\n\n" << files.fileToString(files.searchByName("Text.txt"));
	std::cout << "Ïîèñê ïàïêè:\n\n" << files.fileToString(files.searchByType("FOLDER"));

	std::cin.get();
	std::cin.get();

	return 0;
}
