
#pragma once // includet e klases te perfshihen vtm 1 here kur therritet ne main
#include <string>

class Gjendje
{

private: 
	Gjendje * pas[2];		// gjendjet pasardhese te kalimeve me 0 dhe 1
	int rezultat[2];		// rezultatet e kalimeve
	char emer;				// emri i gjendjes, psh A, B, etj.
	std::string sekuence;	// sekuenca e inputeve qe na kane cuar te kjo gjendje 

public:
	Gjendje(std::string s, int r[], Gjendje *gjpas);
	Gjendje();
	~Gjendje();

	Gjendje * getPasardhes(int i);
	void setPasardhes(int i, Gjendje &gj);

	int getRezultat(int i);
	void setRezultat(int i, int vlere);

	std::string getSekuence();
	void setSekuence(std::string s);

	char getEmer();
	void setEmer(char c);

	void afishoGjendje();

	bool rriNeVend(int i);

	bool operator==(Gjendje gj1ju);
};

