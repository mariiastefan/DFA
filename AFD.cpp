#include "AFD.h"
#include <sstream>
#include <fstream>
#include <iostream>
std::istream& operator>>(std::istream& in, AFD& afd)
{
	std::string buffer, stare, sig, buff;
	std::getline(in, buffer);
	std::istringstream iss(buffer);
	while (iss >> stare)
	{
		afd.stari.push_back(stare);
	}
	buffer.clear();
	sig.clear();
	stare.clear();
	std::getline(in, buffer);
	std::istringstream is(buffer);
	while (is >> sig)
	{
		afd.sigma += sig;
	}
	buffer.clear();
	sig.clear();
	std::getline(in, buffer);
	std::istringstream isss(buffer);
	while (isss >> sig)
	{
		afd.finale.push_back(sig);
	}
	buffer.clear();
	sig.clear();
	char lit;
	in >> afd.StareInit;
	in >> afd.nr_tranzitii;
	for (int index = 0; index < afd.nr_tranzitii; index++)
	{
		in >> buffer >> lit >> stare;
		afd.delta[std::make_pair(buffer, lit)] = stare;
		//afd.delta.push_back(std::make_tuple(buffer, lit, stare));
		
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, AFD afd)
{
	out << "Acestea sunt starile: ";
	for (int index = 0; index < afd.stari.size(); index++)
	{
		out << afd.stari[index] << " ";
	}
	out << '\n';
	out << "Alfabetul de intrare este urmatorul: ";
	for (int index = 0; index < afd.sigma.size(); index++)
	{
		out << afd.sigma[index] << " ";
	}
	out << '\n';
	out << "Starea initiala este: " << afd.StareInit;
	out << '\n';
	out << "Multimea starilor finale este urmatoarea: ";
	for (int index = 0; index < afd.finale.size(); index++)
	{
		out << afd.finale[index] << " ";
	}
	out << '\n';
	out << "AFD-ul are urmatoarele tranzitii: ";
	out << '\n';
	//for (int index = 0; index < afd.delta.size(); index++)
	for(auto ind:afd.delta)
	{
		//out << std::get<0>(afd.delta[index]) << " " << std::get<1>(afd.delta[index]) << " " << std::get<2>(afd.delta[index]);
		out << (ind.first).first << " "
			<< (ind.first).second << " " << ind.second;
		out << '\n';
	}
	return out;
}

AFD::AFD()
{
	sigma = "";
	StareInit = "";
	nr_tranzitii = 0;
}

AFD::AFD(std::vector<std::string> stari1, std::string sigma1, std::vector<std::string> finale1, std::string StareInit1, int nr_tranzitii1, std::unordered_map<std::pair<std::string, char>, std::string, hash_pair> delta1) :stari{ stari1 }, sigma{ sigma1 }, finale{ finale1 }, StareInit{ StareInit1 }, nr_tranzitii{ nr_tranzitii1 }, delta{ delta1 }
{
}
bool AFD::regula1()
{
	if (find(stari.begin(), stari.end(), StareInit) == stari.end())
		return false;
	return true;
}

bool AFD::regula2()
{
	for (auto ind : stari)
	{
		if (find(stari.begin(), stari.end(), ind) == stari.end())
			return false;
	}
	return true;
}


bool AFD::regula3()
{
	for (auto ind : delta)
	{
		if (find(stari.begin(), stari.end(), ind.first.first) == stari.end() || find(stari.begin(), stari.end(), ind.second) == stari.end() || sigma.find(ind.first.second) == std::string::npos)
			return false;
	}
	return true;

}
std::string AFD::apply_transition(std::string stare, char character)
{
	for (auto index : delta)
	{
		//if (std::get<0>(index) == stare && std::get<1>(index) == character)
		if(index.first.first==stare && index.first.second==character )
		{
			//return std::get<2>(index);
			return index.second;
		}
	}
	return "none";
}
bool AFD::word_accepted(std::string word)
{
	std::string stare = StareInit;
	for (auto character : word)
	{
		if (word.size() == 1 && apply_transition(stare, word[0]) == "none")
		{
			std::cout << "BLOCAJ";
			return false;
		}

		if (stare != "none")
		{
			stare = apply_transition(stare, character);
		}
		if (stare == "none")
		{
			std::cout << "BLOCAJ";
			return false;
		}

	}
	if (find(finale.begin(), finale.end(), stare) == finale.end())
	{
		std::cout << "Cuvantul ales nu este acceptat";
		return false;
	}
	std::cout << "Cuvantul ales apartine automatului";
	return true;
}
void AFD::verificare()
{
	if (regula1() == false)
	{
		std::cout << "Starea initiala nu se gaseste in automat\n";
	}
	if (regula2() == false)
	{
		std::cout << "Starile finale nu se gasesc in automat\n";
	}
	if (regula3() == false)
	{
		std::cout << "Tranzitiile nu contin doar elemente ale automatului\n";
	}
	if (regula1() == true && regula2() == true && regula3() == true)
	{
		std::cout << "Automatul este ok";
	}
}


