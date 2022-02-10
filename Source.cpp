#include <iostream>
#include <fstream>
#include "AFD.h"

std::ifstream f("AFD.txt");

int main()
{
	AFD afd;
	f >> afd;
	std::cout << afd;
	afd.verificare();
	std::string word;
	std::cout << '\n';
	std::cout << "Introduceti cuvantul: ";
	bool flag = true;
	std::cout << "Daca doriti sa va opriti scrieti: stop\n";
	do
	{
		std::cin >> word;
		if (word == "stop")
		{
			break;
		}
		afd.word_accepted(word);
		std::cout << '\n';
		

	} while (word!="stop");
	return 0;
}