#include "Gjendje.h"
#include <string>
#include <iostream>

Gjendje::Gjendje() {}

Gjendje::Gjendje(std::string s, int r[], Gjendje *gjpas) {
	this->sekuence = s;
	this->rezultat[0] = r[0];
	this->rezultat[1] = r[1];
	this->pas[0] = &gjpas[0];
	this->pas[0] = &gjpas[0];
}

Gjendje::~Gjendje()
{
}

Gjendje * Gjendje::getPasardhes(int i)
{
	return this->pas[i];
}

void Gjendje::setPasardhes(int i, Gjendje &gj)
{
	this->pas[i] = &gj;
}

int Gjendje::getRezultat(int i)
{
	return this->rezultat[i];
}

void Gjendje::setRezultat(int i, int vlere)
{
	this->rezultat[i] = vlere;
}

std::string Gjendje::getSekuence()
{
	return this->sekuence;
}

void Gjendje::setSekuence(std::string s)
{
	this->sekuence = s;
}

char Gjendje::getEmer()
{
	return this->emer;
}

void Gjendje::setEmer(char c)
{
	this->emer = c;
}

void Gjendje::afishoGjendje()
{
	std::cout << "Gjendja: " << this << "\n"; // adr e memorjes
	std::cout << "Emri: " << this->emer << "\n"; // A, B, C, e me rradhe
	std::cout << "Kalimi me 0: " << this->pas[0] << " me rezultat " << rezultat[0] << "\n";
	std::cout << "Kalimi me 1: " << this->pas[1] << " me rezultat " << rezultat[1] << "\n";
	std::cout << "Sekuenca: " << this->sekuence << "\n\n";
}

bool Gjendje::rriNeVend(int i)
{
	if (this->pas[i] == this)
		return true;
	else
		return false;
}

bool Gjendje::operator==(Gjendje gj1)
{
	bool njelloj = true;
	if (this->emer == gj1.getEmer())
		return true;
	else { // emri i gjendjeve nuk eshte njelloj

		if (this->pas[0] != gj1.getPasardhes(0))
			njelloj = false;

		if (this->pas[1] != gj1.getPasardhes(1))
			njelloj = false;

		if (this->rezultat[1] != gj1.getRezultat(1))
			njelloj = false;
		
		if (this->rezultat[0] != gj1.getRezultat(0))
			njelloj = false;
	}
	return njelloj;
}
