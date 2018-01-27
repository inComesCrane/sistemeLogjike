
#pragma once
#include <string>

class Gjendje
{

private: 
	Gjendje * pas[2];
	char emer;
	int rezultat[2];
	std::string sek;

public:
	Gjendje(); // constructor
	~Gjendje(); // destructor

	Gjendje * getPasardhes(int i);
	void setPasardhes(int i, Gjendje &gj);

	int getRezultat(int i);
	void setRezultat(int i, int vlere);

	std::string getSekuence();
	void setSekuence(std::string s);
	void appendSekuence(std::string s);

	char getEmer();
	void setEmer(char c);

	void afishoGjendje();
};

